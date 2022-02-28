
#include "Animation.h"

bool Animation::Load(const std::string& key, std::shared_ptr<SkeletalMesh> mesh)
{
	ModelRaw = mesh->Raw;
	root = mesh->Raw->root;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(key, aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_PopulateArmatureData | aiProcess_LimitBoneWeights);
	if (scene == nullptr)
		return false;
	if (scene && scene->HasAnimations())
	{
		aiAnimation* Anim = scene->mAnimations[0];
		tickPerSecond = static_cast<float>(Anim->mTicksPerSecond);
		duration = static_cast<float>(Anim->mDuration);

		for (unsigned int i = 0; i < Anim->mNumChannels; ++i)
		{
			aiNodeAnim* channel = Anim->mChannels[i];
			std::string nodeName = channel->mNodeName.C_Str();
			mapBones.insert({ nodeName , Bone(ModelRaw->mapBones[nodeName].id, channel) });
		}
		
		finalMatrixes.resize(mapBones.size());
		for (auto& matrix : finalMatrixes)
			matrix.set_identity();
	}

	return true;
}

void Animation::CalculateBoneTransform(dotth::node* target, const dotth::matrix& parentTransform)
{
	dotth::matrix boneMatrix, modelOffset;
	boneMatrix.set_identity();
	modelOffset.set_identity();

	int boneID = -1;

	auto boneIter = mapBones.find(target->name);
	if (boneIter != mapBones.end())
	{
		boneMatrix = boneIter->second.localTransform;
		boneID = boneIter->second.id;
	}

	auto offsetIter = ModelRaw->mapBones.find(target->name);
	if (offsetIter != ModelRaw->mapBones.end())
	{
		modelOffset = offsetIter->second.offset;
		boneID = offsetIter->second.id;
	}

	dotth::matrix finalMatrix = boneMatrix * parentTransform;

	if (boneID != -1)
	{
		finalMatrixes[boneID] = (modelOffset * finalMatrix).transpose();		
	}

	for (auto child : target->children)
	{
		CalculateBoneTransform(child, finalMatrix);
	}
}

void Animation::Update(float delta)
{
	if (status == ANIMATION_STATUS::RUNNING)
		current += delta * tickPerSecond;

	if (current >= duration)
	{
		if (loop == true)
		{
			current = fmod(current, duration);
		}
		else
		{
			current = duration;
			status = ANIMATION_STATUS::PAUSE;
		}
	}

	for (auto& bone : mapBones)
	{
		bone.second.Update(current);
	}

	dotth::matrix m;
	m.set_identity();
	CalculateBoneTransform(root, m);
}
