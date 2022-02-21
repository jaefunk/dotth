#pragma once

#include "AssetBase.h"
#include "Bone.h"
#include "SkeletalMesh.h"

enum class ANIMATION_STATUS {
	RUNNING, PAUSE, INVALID
};

class Animation
{
public:
	std::shared_ptr<dotth2::model> ModelRaw;
	dotth2::node* root;
	std::map<std::string, Bone> mapBones;
public:
	bool Load(const std::string& key, std::shared_ptr<SkeletalMesh> mesh = nullptr)
	{
		ModelRaw = mesh->Raw;
		root = mesh->Raw->root;
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(key, aiProcess_Triangulate);
		if (scene->HasAnimations())
		{
			aiAnimation* Anim = scene->mAnimations[0];
			tickPerSecond = Anim->mTicksPerSecond;
			duration = Anim->mDuration;

			for (int i = 0; i < Anim->mNumChannels; ++i)
			{
				aiNodeAnim* channel = Anim->mChannels[i];
				std::string nodeName = channel->mNodeName.C_Str();
				mapBones.insert({ nodeName , Bone(ModelRaw->mapBones[nodeName].id, channel) });
			}
		}

		return true;
	}

public:
	ANIMATION_STATUS status = ANIMATION_STATUS::RUNNING;
	bool loop = true;
	float current = 0.f;
	float duration = 0.f;
	float tickPerSecond = 0.f;
	dotth2::matrix finalMatrixes[128];

	void CalculateBoneTransform(dotth2::node* target, dotth2::matrix parentTransform)
	{
		auto finalMatrix = target->local;
		auto iter = mapBones.find(target->name);
		if (iter != mapBones.end())
		{
			iter->second.Update(current);
			finalMatrix = iter->second.localTransform;
		}
		dotth2::matrix global;
		dotth2::matrix::multiply(finalMatrix, parentTransform, global);

		auto iter2 = ModelRaw->mapBones.find(target->name);
		if (iter2 != ModelRaw->mapBones.end())
		{
			int index = iter2->second.id;
			dotth2::matrix offset = iter2->second.offset;
			dotth2::matrix& result = finalMatrixes[index];
			dotth2::matrix::multiply(offset, global, result);
		}
		
		for (auto child : target->children)
		{
			CalculateBoneTransform(child, global);
		}
	}

	void Update(float delta)
	{
		if (status == ANIMATION_STATUS::RUNNING)
			current += tickPerSecond;
		
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

		dotth2::matrix m;
		m.set_identity();
		CalculateBoneTransform(root, m);
	}
};

//struct AnimationNode {
//	std::string name;
//	unsigned int numFrames = 0;
//	dotth::keyframe* frames = nullptr;
//	XMMATRIX result;
//};
//
//struct NodeInfo {
//	unsigned int depth = 0;
//	std::string name;
//	NodeInfo* parent;
//	XMMATRIX local = XMMatrixIdentity();
//	XMMATRIX world = XMMatrixIdentity();
//};
//
//struct BoneInfo {
//	NodeInfo* node = nullptr;
//	XMMATRIX offset = XMMatrixIdentity();
//};
//
//struct BoneInfo2 {
//	unsigned int id;
//	XMMATRIX offset;
//};
//
//enum class ANIMATION_STATUS {
//	RUNNING, PAUSE, INVALID
//};
//
//class Animation2
//{
//public:
//	std::vector<Bone> bones;
//	std::vector<dotth::node*> nodes;
//	void InitNodeInfos(dotth::node* node, dotth::node* parent)
//	{
//		nodes.push_back(node);
//		for (unsigned int i = 0; i < node->numChildren; ++i)
//		{
//			InitNodeInfos(node->children[i], node);
//		}
//	}
//public:
//	void Load(std::shared_ptr<dotth::model> model)
//	{
//		InitNodeInfos(model->root, nullptr);
//		std::sort(nodes.begin(), nodes.end(), [](const dotth::node* l, const dotth::node* r) { return l->depth < r->depth; });
//
//		auto animation = model->animations[0];
//		duration = animation->duration;
//		tickPerSecond = animation->tickPerSecond;
//		numAnimationNodes = animation->numNodeChannels;
//		animationNodes = new AnimationNode[animation->numNodeChannels];
//		for (unsigned int i = 0; i < numAnimationNodes; ++i)
//		{
//			dotth::anim::node* animnode = animation->nodeChannels[i];
//			animationNodes[i].name = animnode->name;
//			animationNodes[i].numFrames = animnode->numKeys;
//			animationNodes[i].frames = animnode->keyframes;
//		}
//	}
//public:
//	ANIMATION_STATUS status = ANIMATION_STATUS::RUNNING;
//	unsigned int numAnimationNodes = 0;
//	AnimationNode* animationNodes = nullptr;
//
//
//public:
//	void GetNodeTransform(const std::string name, XMMATRIX& outTransform)
//	{
//		for (unsigned int i = 0; i < numAnimationNodes; ++i)
//		{
//			if (animationNodes[i].name == name)
//			{
//				outTransform = animationNodes[i].result;
//				break;
//			}
//		}
//	}
//	void Update(float delta)
//	{
//		if (status == ANIMATION_STATUS::RUNNING)
//			current += tickPerSecond;
//		
//		if (current >= duration)
//		{
//			if (loop == true)
//			{
//				current = fmod(current, duration);
//			}
//			else
//			{
//				current = duration;
//				status = ANIMATION_STATUS::PAUSE;
//			}
//		}
//	}
//
//	void CalculateBoneTransform(dotth::node* node, dotth::matrix parentWorld)
//	{
//		std::string name = node->name;
//		dotth::matrix world = parentWorld;
//		//for (auto bone : bones)
//		//{
//		//	bone.
//		//}
//	}
//
//	void Play(void)
//	{
//		status = ANIMATION_STATUS::RUNNING;
//	}
//	void Pause(void)
//	{
//		status = ANIMATION_STATUS::PAUSE;
//	}
//	void Rewind(void)
//	{
//		current = 0.f;
//	}
//	void SetLoop(bool isLoop)
//	{
//		loop = isLoop;
//	}
//
//private:
//	bool loop = true;
//	float current = 0.f;
//	float duration = 0.f;
//	float tickPerSecond = 0.f;
//};