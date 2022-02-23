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
		for (int i = 0; i < channel->mNumPositionKeys; ++i)
		{
			positionKeys[i].time = channel->mPositionKeys[i].mTime;
			positionKeys[i].value.x = channel->mPositionKeys[i].mValue.x;
			positionKeys[i].value.y = channel->mPositionKeys[i].mValue.y;
			positionKeys[i].value.z = channel->mPositionKeys[i].mValue.z;
		}

		rotationKeys.resize(channel->mNumRotationKeys);
		for (int i = 0; i < channel->mNumRotationKeys; ++i)
		{
			rotationKeys[i].time = channel->mRotationKeys[i].mTime;
			rotationKeys[i].value.x = channel->mRotationKeys[i].mValue.x;
			rotationKeys[i].value.y = channel->mRotationKeys[i].mValue.y;
			rotationKeys[i].value.z = channel->mRotationKeys[i].mValue.z;
			rotationKeys[i].value.w = channel->mRotationKeys[i].mValue.w;
		}

		scaleKeys.resize(channel->mNumScalingKeys);
		for (int i = 0; i < channel->mNumScalingKeys; ++i)
		{
			scaleKeys[i].time = channel->mScalingKeys[i].mTime;
			scaleKeys[i].value.x = channel->mScalingKeys[i].mValue.x;
			scaleKeys[i].value.y = channel->mScalingKeys[i].mValue.y;
			scaleKeys[i].value.z = channel->mScalingKeys[i].mValue.z;
		}

		localTransform.set_identity();
	}

public:
	float GetFactor(float prev, float next, float time)
	{
		float length = time - prev;
		float diff = next - prev;
		return length / diff;
	}
	unsigned int GetPositionIndex(float time)
	{
		for (int i = 0; i < raw->mNumPositionKeys-1; ++i)
		{
			if (time < raw->mPositionKeys[i + 1].mTime)
				return i;
		}
		//for (unsigned int i = 0; i < positionKeys.size()-1; ++i)
		//{
		//	if (time < positionKeys[i + 1].time)
		//		return i;
		//}
		return 0;
	}
	unsigned int GetRotationIndex(float time)
	{
		for (int i = 0; i < raw->mNumRotationKeys - 1; ++i)
		{
			if (time < raw->mRotationKeys[i + 1].mTime)
				return i;
		}
		//for (unsigned int i = 0; i < rotationKeys.size() - 1; ++i)
		//{
		//	if (time < rotationKeys[i + 1].time)
		//		return i;
		//}
		return 0;
	}
	unsigned int GetScaleIndex(float time)
	{
		for (int i = 0; i < raw->mNumScalingKeys - 1; ++i)
		{
			if (time < raw->mScalingKeys[i + 1].mTime)
				return i;
		}
		//for (unsigned int i = 0; i < scaleKeys.size() - 1; ++i)
		//{
		//	if (time < scaleKeys[i + 1].time)
		//		return i;
		//}
		return 0;
	}
	XMMATRIX InterpolatePosition(float time)
	{
		auto prev = raw->mPositionKeys[GetPositionIndex(time)];
		auto next = raw->mPositionKeys[GetPositionIndex(time) + 1];
		float factor = GetFactor(prev.mTime, next.mTime, time);

		Assimp::Interpolator<aiVectorKey> interpolator;
		aiVector3D finalPosition;
		interpolator(finalPosition, prev, next, factor);

		XMFLOAT3 float3;
		float3.x = finalPosition.x;
		float3.y = finalPosition.y;
		float3.z = finalPosition.z;
		auto aa = XMMatrixTranslationFromVector(XMLoadFloat3(&float3));
		return aa;
	}
	XMMATRIX InterpolateRotation(float time)
	{
		auto prev = raw->mRotationKeys[GetRotationIndex(time)];
		auto next = raw->mRotationKeys[GetRotationIndex(time) + 1];
		float factor = GetFactor(prev.mTime, next.mTime, time);

		Assimp::Interpolator<aiQuatKey> interpolator;
		aiQuaternion finalValue;
		interpolator(finalValue, prev, next, factor);

		XMFLOAT4 float4;
		float4.x = finalValue.x;
		float4.y = finalValue.y;
		float4.z = finalValue.z;
		float4.w = finalValue.w;
		auto aa = XMMatrixRotationQuaternion(XMLoadFloat4(&float4));
		return aa;
	}
	XMMATRIX InterpolateScale(float time)
	{
		auto prev = raw->mScalingKeys[GetScaleIndex(time)];
		auto next = raw->mScalingKeys[GetScaleIndex(time) + 1];
		float factor = GetFactor(prev.mTime, next.mTime, time);
		Assimp::Interpolator<aiVectorKey> interpolator;
		aiVector3D finalScale;
		interpolator(finalScale, prev, next, factor);
		XMFLOAT3 float3;
		float3.x = finalScale.x;
		float3.y = finalScale.y;
		float3.z = finalScale.z;
		auto aa = XMMatrixScalingFromVector(XMLoadFloat3(&float3));
		return aa;
	}

	void Update(float time)
	{
		XMMATRIX p, r, s;
		p = InterpolatePosition(time);
		r = InterpolateRotation(time);
		s = InterpolateScale(time);
		localTransform = s * r * p;
	}

public:
	unsigned int id = 0;
	std::string name;
	dotth2::matrix localTransform;
	std::vector<keyframe<dotth2::vector3>> positionKeys;
	std::vector<keyframe<dotth2::vector4>> rotationKeys;
	std::vector<keyframe<dotth2::vector3>> scaleKeys;
	aiNodeAnim* raw;
};