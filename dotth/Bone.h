#pragma once

#include "AssetBase.h"

template<class ty>
struct keyframe {
	ty value;
	float time;
};

class Bone
{
public:
	Bone(unsigned int boneID, aiNodeAnim* channel)
	{
		raw = new aiNodeAnim;
		
		raw->mNodeName.Set(channel->mNodeName.C_Str());
		raw->mNumPositionKeys = channel->mNumPositionKeys;
		raw->mNumScalingKeys = channel->mNumScalingKeys;
		raw->mNumRotationKeys = channel->mNumRotationKeys;
		raw->mPositionKeys = new aiVectorKey[raw->mNumPositionKeys];
		raw->mRotationKeys = new aiQuatKey[raw->mNumRotationKeys];
		raw->mScalingKeys = new aiVectorKey[raw->mNumScalingKeys];
		memcpy((void*)raw->mPositionKeys, (void*)channel->mPositionKeys, sizeof(aiVectorKey) * channel->mNumPositionKeys);
		memcpy((void*)raw->mRotationKeys, (void*)channel->mRotationKeys, sizeof(aiQuatKey) * channel->mNumRotationKeys);
		memcpy((void*)raw->mScalingKeys, (void*)channel->mScalingKeys, sizeof(aiVectorKey) * channel->mNumScalingKeys);

		id = boneID;
		name = channel->mNodeName.C_Str();

		positionKeys.resize(channel->mNumPositionKeys);
		for (unsigned int i = 0; i < channel->mNumPositionKeys; ++i)
		{
			positionKeys[i].time = static_cast<float>(channel->mPositionKeys[i].mTime);
			positionKeys[i].value.x = channel->mPositionKeys[i].mValue.x;
			positionKeys[i].value.y = channel->mPositionKeys[i].mValue.y;
			positionKeys[i].value.z = channel->mPositionKeys[i].mValue.z;
		}

		rotationKeys.resize(channel->mNumRotationKeys);
		for (unsigned int i = 0; i < channel->mNumRotationKeys; ++i)
		{
			rotationKeys[i].time = static_cast<float>(channel->mRotationKeys[i].mTime);
			rotationKeys[i].value.x = channel->mRotationKeys[i].mValue.x;
			rotationKeys[i].value.y = channel->mRotationKeys[i].mValue.y;
			rotationKeys[i].value.z = channel->mRotationKeys[i].mValue.z;
			rotationKeys[i].value.w = channel->mRotationKeys[i].mValue.w;
		}

		scaleKeys.resize(channel->mNumScalingKeys);
		for (unsigned int i = 0; i < channel->mNumScalingKeys; ++i)
		{
			scaleKeys[i].time = static_cast<float>(channel->mScalingKeys[i].mTime);
			scaleKeys[i].value.x = channel->mScalingKeys[i].mValue.x;
			scaleKeys[i].value.y = channel->mScalingKeys[i].mValue.y;
			scaleKeys[i].value.z = channel->mScalingKeys[i].mValue.z;
		}

		localTransform.set_identity();
	}

public:
	float GetFactor(float prev, float next, float time)
	{
		float factor = 0.f;
		float length = time - prev;
		float diff = next - prev;
		return length / diff;
	}
	unsigned int GetPositionIndex(float time)
	{
		for (unsigned int i = 0; i < raw->mNumPositionKeys-1; ++i)
		{
			if (time < raw->mPositionKeys[i+1].mTime)
				return i;
		}
		return 0;
	}
	unsigned int GetRotationIndex(float time)
	{
		for (unsigned int i = 0; i < raw->mNumRotationKeys-1; ++i)
		{
			if (time < raw->mRotationKeys[i+1].mTime)
				return i;
		}
		return 0;
	}
	unsigned int GetScaleIndex(float time)
	{
		for (unsigned int i = 0; i < raw->mNumScalingKeys-1; ++i)
		{
			if (time < raw->mScalingKeys[i+1].mTime)
				return i;
		}
		return 0;
	}
	XMMATRIX InterpolatePosition(float time)
	{
		const int lastIndex = raw->mNumPositionKeys - 1;
		int currentIndex = GetPositionIndex(time);
		int nextIndex = currentIndex + 1;
		if (nextIndex == lastIndex)
			nextIndex = 0;
		if (raw->mPositionKeys[lastIndex].mTime <= time)
			time -= static_cast<float>(raw->mPositionKeys[lastIndex].mTime);

		auto prev = raw->mPositionKeys[currentIndex];
		auto next = raw->mPositionKeys[nextIndex];
		auto nexttime = raw->mPositionKeys[currentIndex + 1];
		float factor = GetFactor(static_cast<float>(prev.mTime), static_cast<float>(nexttime.mTime), time);

		Assimp::Interpolator<aiVectorKey> interpolator;
		interpolator(finalPosition, prev, next, factor);

		XMFLOAT3 value;
		value.x = finalPosition.x;
		value.y = finalPosition.y;
		value.z = finalPosition.z;
		return XMMatrixTranslationFromVector(XMLoadFloat3(&value));
	}
	XMMATRIX InterpolateRotation(float time)
	{
		const int lastIndex = raw->mNumRotationKeys - 1;
		int currentIndex = GetRotationIndex(time);
		int nextIndex = currentIndex + 1;
		if (nextIndex == lastIndex)
			nextIndex = 0;
		if (raw->mRotationKeys[lastIndex].mTime <= time)
			time -= static_cast<float>(raw->mRotationKeys[lastIndex].mTime);

		auto prev = raw->mRotationKeys[currentIndex];
		auto next = raw->mRotationKeys[nextIndex];
		auto nexttime = raw->mRotationKeys[currentIndex + 1];
		float factor = GetFactor(static_cast<float>(prev.mTime), static_cast<float>(nexttime.mTime), time);

		Assimp::Interpolator<aiQuatKey> interpolator;
		interpolator(finalQuaternion, prev, next, factor);

		XMFLOAT4 value;
		value.x = finalQuaternion.x;
		value.y = finalQuaternion.y;
		value.z = finalQuaternion.z;
		value.w = finalQuaternion.w;
		return XMMatrixRotationQuaternion(XMLoadFloat4(&value));
	}
	XMMATRIX InterpolateScale(float time)
	{
		const int lastIndex = raw->mNumScalingKeys - 1;
		int currentIndex = GetScaleIndex(time);
		int nextIndex = currentIndex + 1;
		if (nextIndex == lastIndex)
			nextIndex = 0;
		if (raw->mScalingKeys[lastIndex].mTime <= time)
			time -= static_cast<float>(raw->mScalingKeys[lastIndex].mTime);

		auto prev = raw->mScalingKeys[currentIndex];
		auto next = raw->mScalingKeys[nextIndex];
		auto nexttime = raw->mScalingKeys[currentIndex + 1];
		float factor = GetFactor(static_cast<float>(prev.mTime), static_cast<float>(nexttime.mTime), time);

		Assimp::Interpolator<aiVectorKey> interpolator;
		interpolator(finalScale, prev, next, factor);

		XMFLOAT3 value;
		value.x = finalScale.x;
		value.y = finalScale.y;
		value.z = finalScale.z;
		return XMMatrixScalingFromVector(XMLoadFloat3(&value));
	}

	void Update(float time)
	{
		XMMATRIX p = InterpolatePosition(time);
		XMMATRIX r = InterpolateRotation(time);
		XMMATRIX s = InterpolateScale(time);
		localTransform = s * r * p;
	}

public:
	unsigned int id = 0;
	std::string name;
	aiVector3D finalScale;
	aiQuaternion finalQuaternion;
	aiVector3D finalPosition;

	dotth::matrix localTransform;
	dotth::matrix scaleTransform;
	dotth::matrix rotateTransform;
	dotth::matrix positionTransform;
	std::vector<keyframe<dotth::vector3>> positionKeys;
	std::vector<keyframe<dotth::vector4>> rotationKeys;
	std::vector<keyframe<dotth::vector3>> scaleKeys;
	aiNodeAnim* raw;
};