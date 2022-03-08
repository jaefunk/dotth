#pragma once

#include "Animation.h"

class AnimationBlendLink
{
public:
	float factor;
	Animation* from;
	Animation* to;

public:
	void update(float delta)
	{
		factor += delta;
		//factor = clamp(0.f, 1.f, factor);
	}

};

class AnimationController
{
private:
	std::unordered_map<std::string, Animation*> Animations;
	
public:
	float accTime = 0.f;
	float clampFactor = 0.f;
	float blendFactor = 0.f;
	float blendDuration = 0.f;
	Animation* activeClip = nullptr;
	Animation* blendClip = nullptr;

	std::unordered_map<std::string, dotth::matrix> result;

public:
	std::vector<dotth::matrix> finalMatrixes;

public:
	void AddClip(const std::string& key, Animation* clip)
	{
		Animations.insert({ key, clip });
	}
		
public:
	void SetClip(const std::string& key, float blending = 0.5f)
	{
		blendFactor = 0.f;
		blendDuration = blending;
		
		if (activeClip == nullptr)
		{
			activeClip = Animations[key];
			finalMatrixes.resize(activeClip->ModelRaw->mapBones.size());
			for (auto& matrix : finalMatrixes)
				matrix.set_identity();
		}
		else
			blendClip = Animations[key];
	}

public:
	void Update(float delta)
	{
		accTime += delta;
		clampFactor = fmod(accTime, 1.f);
		result.clear();
		
		activeClip->Update(clampFactor);
		for (const auto& activeIter : activeClip->mapBones)
		{
			result[activeIter.first] = activeIter.second.localTransform;
		}

		
		if (blendClip != nullptr)
		{
			//if (blendFactor <= blendDuration)
			{
				//blendFactor += delta;
				blendClip->Update(clampFactor);

				/////////////////////////////
				float factor = blendFactor;// / blendDuration;
				for (const auto blendPair : blendClip->mapBones)
				{
					auto key = blendPair.first;
					auto value = blendPair.second;

					auto activeIter = activeClip->mapBones.find(key);
					if (activeIter != activeClip->mapBones.end())
					{
						Assimp::Interpolator<aiVector3D> interpolationVector3D;
						Assimp::Interpolator<aiQuaternion> interpolationQuaternion;

						auto as = activeIter->second.finalScale;
						auto bs = value.finalScale;
						aiVector3D rs;
						interpolationVector3D(rs, as, bs, factor);

						auto aq = activeIter->second.finalQuaternion;
						auto bq = value.finalQuaternion;
						aiQuaternion rq;
						interpolationQuaternion(rq, aq, bq, factor);

						auto ap = activeIter->second.finalPosition;
						auto bp = value.finalPosition;
						aiVector3D rp;
						interpolationVector3D(rp, ap, bp, factor);
						
						XMFLOAT3 s;
						s.x = rs.x;
						s.y = rs.y;
						s.z = rs.z;
						auto ss = XMMatrixScalingFromVector(XMLoadFloat3(&s));

						XMFLOAT4 r;
						r.x = rq.x;
						r.y = rq.y;
						r.z = rq.z;
						r.w = rq.w;
						auto rr = XMMatrixRotationQuaternion(XMLoadFloat4(&r));

						XMFLOAT3 p;
						p.x = rp.x;
						p.y = rp.y;
						p.z = rp.z;
						auto pp = XMMatrixTranslationFromVector(XMLoadFloat3(&p));

						result[activeIter->first] = ss * rr * pp;
					}
				}

				//if (blendFactor >= blendDuration)
				//{
				//	printf(" update blend done");
				//	blendDuration = 0.f;
				//	blendFactor = 0.f;
				//	activeClip = blendClip;
				//	blendClip = nullptr;
				//}
			}
		}	

		dotth::matrix m;
		m.set_identity();
		CalculateBoneTransform(activeClip->root, m);
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
			//boneID = boneIter->second.id;
		}

		auto offsetIter = activeClip->ModelRaw->mapBones.find(target->name);
		if (offsetIter != activeClip->ModelRaw->mapBones.end())
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