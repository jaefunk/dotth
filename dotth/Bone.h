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
		for (unsigned int i = 0; i < positionKeys.size()-1; ++i)
		{
			if (time < positionKeys[i + 1].time)
				return i;
		}
		return 0;
	}
	unsigned int GetRotationIndex(float time)
	{
		for (unsigned int i = 0; i < rotationKeys.size() - 1; ++i)
		{
			if (time < rotationKeys[i + 1].time)
				return i;
		}
		return 0;
	}
	unsigned int GetScaleIndex(float time)
	{
		for (unsigned int i = 0; i < scaleKeys.size() - 1; ++i)
		{
			if (time < scaleKeys[i + 1].time)
				return i;
		}
		return 0;
	}
	XMMATRIX InterpolatePosition(float time)
	{
		keyframe<dotth2::vector3> prev = positionKeys[GetPositionIndex(time)];
		keyframe<dotth2::vector3> next = positionKeys[GetPositionIndex(time) + 1];
		float factor = GetFactor(prev.time, next.time, time);
		dotth2::vector3 finalPosition;
		dotth2::vector3::subtract(next.value, prev.value, finalPosition);
		dotth2::vector3::multiply(finalPosition, factor, finalPosition);
		dotth2::vector3::add(prev.value, finalPosition, finalPosition);
		XMFLOAT3 float3 = XMFLOAT3(finalPosition);
		auto aa = XMMatrixTranslationFromVector(XMLoadFloat3(&float3));
		return aa;
	}
	XMMATRIX InterpolateRotation(float time)
	{
		auto lerp = [](const dotth2::vector4& a, const dotth2::vector4& b, float f) {
			dotth2::vector4 r;
			float t_ = 1 - f;
			r.x = t_ * a.x + f * b.x;
			r.y = t_ * a.y + f * b.y;
			r.z = t_ * a.z + f * b.z;
			r.w = t_ * a.w + f * b.w;
			dotth2::vector4::normalize(r, r);
			return r;
		};
		keyframe<dotth2::vector4> prev = rotationKeys[GetRotationIndex(time)];
		keyframe<dotth2::vector4> next = rotationKeys[GetRotationIndex(time) + 1];
		float factor = GetFactor(prev.time, next.time, time);
		dotth2::vector4 finalRotation = lerp(prev.value, prev.value, factor);
		//dotth2::vector4::subtract(next.value, prev.value, finalRotation);
		//dotth2::vector4::multiply(finalRotation, factor, finalRotation);
		//dotth2::vector4::add(prev.value, finalRotation, finalRotation);
		XMFLOAT4 float4 = XMFLOAT4(finalRotation);
		XMLoadFloat4(&float4);

		

		return XMMatrixRotationQuaternion(XMLoadFloat4(&float4));;
	}
	XMMATRIX InterpolateScale(float time)
	{
		keyframe<dotth2::vector3> prev = scaleKeys[GetScaleIndex(time)];
		keyframe<dotth2::vector3> next = scaleKeys[GetScaleIndex(time) + 1];
		float factor = GetFactor(prev.time, next.time, time);
		dotth2::vector3 finalScale;
		dotth2::vector3::subtract(next.value, prev.value, finalScale);
		dotth2::vector3::multiply(finalScale, factor, finalScale);
		dotth2::vector3::add(prev.value, finalScale, finalScale);
		XMFLOAT3 float3 = finalScale;
		return XMMatrixScalingFromVector(XMLoadFloat3(&float3));
	}

	void Update(float time)
	{
		XMMATRIX p, r, s;
		p = InterpolatePosition(time);
		r = InterpolateRotation(time);
		s = InterpolateScale(time);
		localTransform = p * r * s;
	}

public:
	unsigned int id = 0;
	std::string name;
	dotth2::matrix localTransform;
	std::vector<keyframe<dotth2::vector3>> positionKeys;
	std::vector<keyframe<dotth2::vector4>> rotationKeys;
	std::vector<keyframe<dotth2::vector3>> scaleKeys;
};