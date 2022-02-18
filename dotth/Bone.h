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
	Bone(unsigned int boneID, dotth::anim::node* channel)
	{
		id = boneID;
		name = channel->name;

		positionKeys.resize(channel->numKeys);
		rotationKeys.resize(channel->numKeys);
		scaleKeys.resize(channel->numKeys);
		for (unsigned int i = 0; i < channel->numKeys; ++i)
		{
			const dotth::keyframe& key = channel->keyframes[i];
			positionKeys[i].time = key.time;
			positionKeys[i].value = key.position;
			rotationKeys[i].time = key.time;
			rotationKeys[i].value = key.rotation;
			scaleKeys[i].time = key.time;
			scaleKeys[i].value = key.scale;
		}
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
		keyframe<dotth::vector3> prev = positionKeys[GetPositionIndex(time)];
		keyframe<dotth::vector3> next = positionKeys[GetPositionIndex(time) + 1];
		float factor = GetFactor(prev.time, next.time, time);
		dotth::vector3 finalPosition;
		dotth::vector3::multiply(next.value, factor, finalPosition);
		dotth::vector3::add(prev.value, finalPosition, finalPosition);
		XMFLOAT3 float3 = finalPosition;
		return XMMatrixTranslationFromVector(XMLoadFloat3(&float3));
	}
	XMMATRIX InterpolateRotation(float time)
	{
		keyframe<dotth::vector4> prev = rotationKeys[GetRotationIndex(time)];
		keyframe<dotth::vector4> next = rotationKeys[GetRotationIndex(time) + 1];
		float factor = GetFactor(prev.time, next.time, time);
		dotth::vector4 finalRotation;
		dotth::vector4::multiply(next.value, factor, finalRotation);
		dotth::vector4::add(prev.value, finalRotation, finalRotation);
		XMFLOAT4 float4 = XMFLOAT4(finalRotation);
		XMLoadFloat4(&float4);
		return XMMatrixRotationQuaternion(XMLoadFloat4(&float4));;
	}
	XMMATRIX InterpolateScale(float time)
	{
		keyframe<dotth::vector3> prev = scaleKeys[GetScaleIndex(time)];
		keyframe<dotth::vector3> next = scaleKeys[GetScaleIndex(time) + 1];
		float factor = GetFactor(prev.time, next.time, time);
		dotth::vector3 finalScale;
		dotth::vector3::multiply(next.value, factor, finalScale);
		dotth::vector3::add(prev.value, finalScale, finalScale);
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

private:
	unsigned int id = 0;
	std::string name;
	dotth::matrix localTransform;
	std::vector<keyframe<dotth::vector3>> positionKeys;
	std::vector<keyframe<dotth::vector4>> rotationKeys;
	std::vector<keyframe<dotth::vector3>> scaleKeys;
};