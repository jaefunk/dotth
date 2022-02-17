#pragma once

#include "AssetBase.h"

//struct KeyFrame {
//	float time = 0.f;
//
//};
//struct AniNode {
//	std::vector<dotth::anim::node*>	keyFrame;
//	std::string name = "none";
//	dotth::matrix result;
//};

struct AnimationNode {
	std::string name;
	unsigned int numFrames = 0;
	dotth::keyframe* frames = nullptr;
	XMMATRIX result;
};

struct NodeInfo {
	unsigned int depth = 0;
	std::string name;
	NodeInfo* parent;
	XMMATRIX local = XMMatrixIdentity();
	XMMATRIX world = XMMatrixIdentity();
};

struct BoneInfo {
	NodeInfo* node = nullptr;
	XMMATRIX offset = XMMatrixIdentity();
};

enum class ANIMATION_STATUS {
	RUNNING, PAUSE, INVALID
};
class Animation2
{
public:
	std::vector<dotth::node*> nodes;
	void InitNodeInfos(dotth::node* node, dotth::node* parent)
	{
		nodes.push_back(node);
		for (unsigned int i = 0; i < node->numChildren; ++i)
		{
			InitNodeInfos(node->children[i], node);
		}
	}
public:
	void Load(std::shared_ptr<dotth::model> model)
	{
		InitNodeInfos(model->root, nullptr);
		std::sort(nodes.begin(), nodes.end(), [](const dotth::node* l, const dotth::node* r) { return l->depth < r->depth; });

		auto animation = model->animations[0];
		duration = animation->duration;
		tickPerSecond = animation->tickPerSecond;
		numAnimationNodes = animation->numNodeChannels;
		animationNodes = new AnimationNode[animation->numNodeChannels];
		for (unsigned int i = 0; i < numAnimationNodes; ++i)
		{
			dotth::anim::node* animnode = animation->nodeChannels[i];
			animationNodes[i].name = animnode->name;
			animationNodes[i].numFrames = animnode->numKeys;
			animationNodes[i].frames = animnode->keyframes;
		}
	}
public:
	ANIMATION_STATUS status = ANIMATION_STATUS::RUNNING;
	unsigned int numAnimationNodes = 0;
	AnimationNode* animationNodes = nullptr;


public:
	void GetNodeTransform(const std::string name, XMMATRIX& outTransform)
	{
		for (unsigned int i = 0; i < numAnimationNodes; ++i)
		{
			if (animationNodes[i].name == name)
			{
				outTransform = animationNodes[i].result;
				break;
			}
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

		for (unsigned int i = 0; i < numAnimationNodes; ++i)
		{
			auto& animNode = animationNodes[i];
			
			if (current <= animNode.frames[0].time)
			{	
				XMVECTOR Z = XMVectorSet(0.f, 0.f, 0.f, 1.f);
				XMFLOAT3 p = XMFLOAT3(animNode.frames[0].position);
				XMFLOAT4 r = XMFLOAT4(animNode.frames[0].rotation);
				XMFLOAT3 s = XMFLOAT3(animNode.frames[0].scale);
				XMVECTOR T = XMLoadFloat3(&p);
				XMVECTOR R = XMLoadFloat4(&r);
				XMVECTOR S = XMLoadFloat3(&s);
				animNode.result = XMMatrixAffineTransformation(S, Z, R, T);
			}
			else if (current >= animNode.frames[animNode.numFrames - 1].time)
			{
				XMVECTOR Z = XMVectorSet(0.f, 0.f, 0.f, 1.f);
				XMFLOAT3 p = XMFLOAT3(animNode.frames[animNode.numFrames - 1].position);
				XMFLOAT4 r = XMFLOAT4(animNode.frames[animNode.numFrames - 1].rotation);
				XMFLOAT3 s = XMFLOAT3(animNode.frames[animNode.numFrames - 1].scale);
				XMVECTOR T = XMLoadFloat3(&p);
				XMVECTOR R = XMLoadFloat4(&r);
				XMVECTOR S = XMLoadFloat3(&s);
				animNode.result = XMMatrixAffineTransformation(S, Z, R, T);
			}
			else
			{
				for (unsigned int j = 0; j < animNode.numFrames; ++j)
				{
					dotth::keyframe frame = animNode.frames[j];
					if (current <= frame.time)
					{
						XMVECTOR Z = XMVectorSet(0.f, 0.f, 0.f, 1.f);
						XMFLOAT3 p = XMFLOAT3(frame.position);
						XMFLOAT4 r = XMFLOAT4(frame.rotation);
						XMFLOAT3 s = XMFLOAT3(frame.scale);
						XMVECTOR T = XMLoadFloat3(&p);
						XMVECTOR R = XMLoadFloat4(&r);
						XMVECTOR S = XMLoadFloat3(&s);
						animNode.result = XMMatrixAffineTransformation(S, Z, R, T); 
						break;
					}
				}
			}
			
			for (auto& node : nodes)
			{
				XMMATRIX tm = XMMATRIX(node->local.f);
				GetNodeTransform(node->name, tm);
				node->world = tm;
				if (node->parent)
				{
					node->world = XMMatrixTranspose(tm * XMMATRIX(node->parent->world.f));
				}
			}
		}
	}

	void Play(void)
	{
		status = ANIMATION_STATUS::RUNNING;
	}
	void Pause(void)
	{
		status = ANIMATION_STATUS::PAUSE;
	}
	void Rewind(void)
	{
		current = 0.f;
	}
	void SetLoop(bool isLoop)
	{
		loop = isLoop;
	}

private:
	bool loop = true;
	float current = 0.f;	// current
	float duration = 0.f;		// animation length
	float tickPerSecond = 0.f;	// speed
};

enum class PLAY_STATE {
	PLAY, STOP
};

//Ű ������ ����
struct KeyFrame {
	float		timePos = 0.f;
	XMFLOAT3	trans = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT4	rotation = XMFLOAT4(0.f, 0.f, 0.f, 0.f);
	XMFLOAT3	scale = XMFLOAT3(0.f, 0.f, 0.f);
};

//���� ����� �ִϸ��̼� ����
struct AniNode {
	std::vector<KeyFrame>	keyFrame;							//Ű������ ����Ʈ
	std::string				name= "none";						//�̸�;					//����� �� �̸�

	XMMATRIX			aniTM = XMMatrixIdentity();		//�ִϸ��̼� ���, �����ӿ� ���� ������Ʈ�� ��� ������ ����
};


//�ִϸ��̼� Ŭ����
class Animation
{
	//*************************************** ��� �Լ� ************************************************//
public:
	Animation();
	~Animation();

	//Animation Play Function
	void				Play() { _playState = PLAY_STATE::PLAY; }
	void				Pause() { _playState = PLAY_STATE::STOP; }
	void				Stop() {
		_playState = PLAY_STATE::STOP;
		_playTime = 0.f;
	}

	//�ݺ� ��� ���� üũ
	bool				IsRepeat() { return _isRepeat; }

	//Set Function
	void				SetTickPerSecond(float tps) { _tickPerSecond = tps; }		//ƽ �� ����
	void				SetDuration(float duration) { _duration = duration; }		//����ӵ� ����
	void				SetLastFrame(float time) { _lastTime = time; }		//������ ������ ����
	void				SetName(std::string name) { _name = name; }		//�ִϸ��̼� �̸�
	void				TurnRepeat() { _isRepeat = !_isRepeat; }		//�ݺ���� ��ȯ


	//Get Function
	std::vector<AniNode>& GetAniNodeList() { return _aniNode; }		//�ִϸ��̼� ��� ����Ʈ ��ȯ
	XMMATRIX			GetAniTM(std::string nodeName, XMMATRIX& tm);												//��忡 �´� �ִϸ��̼� ����� ��ȯ
	std::string				GetName() { return _name; }		//�ִϸ��̼� �̸� ��ȯ

	//Update AniTM
	void				UpdateAnimation(float t);																//�ִϸ��̼��� ������Ʈ�Ѵ�.


//*************************************** ��� ���� ***********************************************//
private:
	std::vector<AniNode>		_aniNode;										//�ִϸ��̼� ��� ����Ʈ

	std::string				_name = "none";						//�̸�
	float				_tickPerSecond = 0.f;							//tick ����
	float				_duration = 0.f;							//�ӵ�
	float				_playTime = 0.f;							//���� ������
	float				_lastTime = 0.f;							//������ ������

	bool				_isRepeat = true;							//��� �Ϸ�� �ݺ� ��� �÷���
	PLAY_STATE			_playState = PLAY_STATE::STOP;				//��� ����
};
