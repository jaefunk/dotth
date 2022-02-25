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
	dotth2::matrix finalMatrixes[128];
	std::shared_ptr<dotth2::model> ModelRaw;
	dotth2::node* root;
	std::map<std::string, Bone> mapBones;

public:
	bool Load(const std::string& key, std::shared_ptr<SkeletalMesh> mesh);
	void Update(float delta);
	void CalculateBoneTransform(dotth2::node* target, const dotth2::matrix& parentTransform);
};