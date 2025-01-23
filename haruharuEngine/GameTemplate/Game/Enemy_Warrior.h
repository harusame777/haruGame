#pragma once
#include "EnemyBase.h"
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class GameSound;
class Player;

class Enemy_Warrior : public EnemyBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Enemy_Warrior();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	~Enemy_Warrior();
private:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �A�j���[�V�����C�x���g
	/// </summary>
	/// <param name="clipName"></param>
	/// <param name="eventName"></param>
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �h���[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// AIList�̏�����
	/// </summary>
	void InitAIList();
	/// <summary>
	/// AIList���̃v���O�����̃A�b�v�f�[�g
	/// </summary>
	void AIListUpdate();
private:
	/// <summary>
	/// �R���W�����I�u�W�F�N�g
	/// </summary>
	CollisionObject* m_collisionObject;	

	//test
	Player* m_player = nullptr;
	/// <summary>
	/// �Q�[���T�E���h
	/// </summary>
	GameSound* m_gameSound = nullptr;
};

