
#include "ResourceManager.h"
#include "json/json.hpp"
#include "Utility.h"

#include "Texture2D.h"
#include "StaticMesh.h"

bool ResourceManager2::Load(void)
{
	for (auto& iterator : std::filesystem::recursive_directory_iterator("Resource/"))
	{
		if (!iterator.is_directory())
		{
			auto path = iterator.path();
			auto pathString = path.u8string();
			pathString = Utility::Str::Replace(pathString, "\\", "/");
			auto filesystem = std::filesystem::path(pathString);
			auto filename = filesystem.filename().u8string();
			auto extension = filesystem.extension().u8string();
			auto key = Utility::Str::Replace(filename, extension, "");
			auto loaded = LoadAsset(pathString);
			if (loaded == nullptr)
			{
				std::cout << " ### " << path << " load failed!" << std::endl;
				continue;
			}
			decltype(resources)::iterator find = resources.find(key);
			if (find != resources.end())
			{
				std::cout << " ### " << path << " duplicate file name!" << std::endl;
				continue;
			}
			std::cout << " ### " << path << " was loaded!" << std::endl;
			resources.emplace(std::make_pair(key, loaded));
		}
	}

	return true;
}

std::shared_ptr<Resource> ResourceManager2::LoadAsset(const std::string& path)
{
	//if (path.find(".fbx") != std::string::npos)
	//	return FBXLoader::Load(path);

	//if (path.find(".FBX") != std::string::npos)
	//	return FBXLoader::Load(path);

	if (path.find(".jpg") != std::string::npos)
		return JPEGLoader::Load(path);

	return nullptr;
}


#include "assimp/Exporter.hpp"
aiScene* AssimpSceneClone(const aiScene* origin)
{
	Assimp::Exporter exporter;

	aiAnimation** anim = new aiAnimation * [3];

	std::string key;
	key = "Resource/Human.fbx";
	Assimp::Importer* importer0 = new Assimp::Importer();
	const aiScene* scene0 = importer0->ReadFile(key, aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_PopulateArmatureData | aiProcess_LimitBoneWeights);
	auto jj = const_cast<aiScene*>(scene0);
	exporter.Export(jj, "fbx", "Resource/Human.fbx");
	anim[0] = scene0->mAnimations[0];

	key = "Resource/Walk.fbx";
	Assimp::Importer* importer1 = new Assimp::Importer();
	const aiScene* scene1 = importer1->ReadFile(key, aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_PopulateArmatureData | aiProcess_LimitBoneWeights);
	jj->mNumAnimations++;
	anim[1] = scene1->mAnimations[0];

	key = "Resource/Run.fbx";
	Assimp::Importer* importer2 = new Assimp::Importer();
	const aiScene* scene2 = importer2->ReadFile(key, aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_PopulateArmatureData | aiProcess_LimitBoneWeights);
	jj->mNumAnimations++;
	anim[2] = scene2->mAnimations[0];

	jj->mAnimations = anim;



	aiScene* newScene = new aiScene;
	newScene->mName = scene0->mName;

	newScene->mNumMeshes = scene0->mNumMeshes;
	newScene->mMeshes = new aiMesh * [newScene->mNumMeshes];
	for (auto i = 0; i < newScene->mNumMeshes; ++i)
	{
		newScene->mMeshes[i] = new aiMesh;
		auto src = scene0->mMeshes[i];
		newScene->mMeshes[i]->mName = src->mName;
		newScene->mMeshes[i]->mNumVertices = src->mNumVertices;
		//newScene->mMeshes[i]->mVertices = new aiV
		//src->mVertices;

		newScene->mMeshes[i]->mNumFaces = src->mNumFaces;
		newScene->mMeshes[i]->mNumBones = src->mNumBones;
		newScene->mMeshes[i]->mNumAnimMeshes = src->mNumAnimMeshes;
		newScene->mMeshes[i]->mNumUVComponents[0] = src->mNumUVComponents[0];
		newScene->mMeshes[i]->mNumUVComponents[1] = src->mNumUVComponents[1];
		newScene->mMeshes[i]->mNumUVComponents[2] = src->mNumUVComponents[2];
		newScene->mMeshes[i]->mNumUVComponents[3] = src->mNumUVComponents[3];
		newScene->mMeshes[i]->mNumUVComponents[4] = src->mNumUVComponents[4];
		newScene->mMeshes[i]->mNumUVComponents[5] = src->mNumUVComponents[5];
		newScene->mMeshes[i]->mNumUVComponents[6] = src->mNumUVComponents[6];
		newScene->mMeshes[i]->mNumUVComponents[7] = src->mNumUVComponents[7];
	}

	newScene->mNumAnimations = scene0->mNumAnimations;
	newScene->mAnimations = new aiAnimation * [newScene->mNumAnimations];
	for (auto i = 0; i < newScene->mNumAnimations; ++i)
	{

	}

	return nullptr;
}