#pragma once

#include "Animation.h"

template<int PoolSize>
class AnimationBlendSystem
{
private:
	int activeIndex = -1;
	std::array<Animation*, PoolSize> animations;
	std::array<float, PoolSize> values;
	float valueSum = 0.f;

public:
	void SetActiveIndex(int index) {
		activeIndex = index;
	}

	void Update(float delta) {
		auto clamp = [](float value, float min, float max) {
			return min >= value ? min : max <= value ? max : value;
		};

		float blendDurationScalar = 4.f;
		valueSum = 0.f;
		for (auto index = 0; index < PoolSize; ++index) {

			float blendDurationFactor = delta * blendDurationScalar;
			values[index] += index == activeIndex ? blendDurationFactor : -blendDurationFactor;
			values[index] = clamp(values[index], 0.f, 1.f);

			if (values[index] > 0.f) {
				animations[index]->Update(delta);
			}

			valueSum += values[index];
		}
	}

	float Weight(int index) {
		return values[index] / valueSum;
	}

	float Value(int index) {
		return values[index];
	}

	Animation*& operator[] (int index) {
		return animations[index];
	}
};

#define MAX_BLEND_SIZE 8

class AnimationController
{
public:
	bool Load(const std::string& key)
	{
		return true;
	}

public:
	std::shared_ptr<dotth::model> model;
	std::vector<std::string> boneNames;
	std::vector<Animation*> animArray;

	AnimationBlendSystem<MAX_BLEND_SIZE> BlendSystem;
	std::unordered_map<std::string, dotth::matrix> result;

public:
	std::vector<dotth::matrix> finalMatrixes;

public:
	void SetAnimation(int index, Animation* clip)
	{
		animArray.push_back(clip);
		BlendSystem[index] = clip;
	}
		
public:
	void BlendTo(int index) {
		BlendSystem.SetActiveIndex(index);
		BlendSystem[index]->current = 0.f;
	}

public:
	void Update(float delta)
	{
		BlendSystem.Update(delta);

		for (auto name : boneNames) {
			aiVector3D scaleResult;
			scaleResult.Set(0.f, 0.f, 0.f);
			aiQuaternion rotationBefore = aiQuaternion(0.f, 0.f, 0.f);
			aiQuaternion rotationResult = aiQuaternion(0.f, 0.f, 0.f);
			aiVector3D positionResult;
			positionResult.Set(0.f, 0.f, 0.f);

			int beforeIndex = -1;
			for (auto i = 0; i < MAX_BLEND_SIZE; ++i) {
				if (BlendSystem.Weight(i) <= 0.f)
					continue;
				auto iter = BlendSystem[i]->mapBones.find(name);
				if (iter != BlendSystem[i]->mapBones.end())
				{
					positionResult += iter->second.finalPosition * BlendSystem.Weight(i);
					scaleResult += iter->second.finalScale * BlendSystem.Weight(i);

					if (beforeIndex == -1)
					{
						beforeIndex = i;
						rotationResult = iter->second.finalQuaternion;
					}
					else
					{
						float factor = BlendSystem.Weight(i) / (BlendSystem.Weight(beforeIndex) + BlendSystem.Weight(i));
						auto rotIter2 = BlendSystem[i]->mapBones.find(name);
						if (rotIter2 != BlendSystem[i]->mapBones.end())
						{
							Assimp::Interpolator<aiQuaternion> interpolationQuaternion;
							interpolationQuaternion(rotationResult, rotationResult, rotIter2->second.finalQuaternion, factor);
							beforeIndex = i;
						}
					}
				}
			}

			XMFLOAT3 s;
			s.x = scaleResult.x;
			s.y = scaleResult.y;
			s.z = scaleResult.z;
			auto ss = XMMatrixScalingFromVector(XMLoadFloat3(&s));

			XMFLOAT4 r;
			r.x = rotationResult.x;
			r.y = rotationResult.y;
			r.z = rotationResult.z;
			r.w = rotationResult.w;
			auto rr = XMMatrixRotationQuaternion(XMLoadFloat4(&r));

			XMFLOAT3 p;
			p.x = positionResult.x;
			p.y = positionResult.y;
			p.z = positionResult.z;
			auto pp = XMMatrixTranslationFromVector(XMLoadFloat3(&p));
			result[name] = ss * rr * pp;
		}

		dotth::matrix m;
		m.set_identity();
		CalculateBoneTransform(model->root, m);
	}

	void CalculateBoneTransform(dotth::node* target, const dotth::matrix& parentTransform)
	{
		dotth::matrix boneMatrix, modelOffset;
		boneMatrix.set_identity();
		modelOffset.set_identity();

		int boneID = -1;

		auto boneIter = result.find(target->name);
		if (boneIter != result.end())
		{
			boneMatrix = boneIter->second;
		}

		auto offsetIter = model->mapBones.find(target->name);
		if (offsetIter != model->mapBones.end())
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
};