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
	ANIMATION_STATUS status = ANIMATION_STATUS::RUNNING;
	bool loop = true;
	float current = 0.f;
	float duration = 0.f;
	float tickPerSecond = 0.f;

	std::vector<dotth::matrix> finalMatrixes;
	std::shared_ptr<dotth::model> ModelRaw;
	dotth::node* root;
	std::map<std::string, Bone> mapBones;

public:
	bool Load(const std::string& key, SkeletalMesh* skeletalMesh);
	void BoneUpdate(void);
	void Update(float delta);
	void CalculateBoneTransform(dotth::node* target, const dotth::matrix& parentTransform);
};