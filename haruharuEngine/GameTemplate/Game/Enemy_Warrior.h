#pragma once
#include "EnemyBase.h"
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class Enemy_Warrior : public EnemyBase
{
public:
	enum EnAnimationClip
	{
		en_idle,
		en_tracking,
		en_patrol,
		en_animationNum,
	};

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
	/// <summary>
	/// �f�o�b�N�f�B�X�v���C�����ݒ�
	/// </summary>
	void DebugStateDisplay(int setnum)
	{
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"NowState[%01d]", int(setnum));

		m_debugStateDisplayRender.SetText(wcsbuf);
	}
private:
	/// <summary>
	/// ���f��
	/// </summary>
	ModelRender m_modelRender;
	/// <summary>
	/// �R���W�����I�u�W�F�N�g
	/// </summary>
	CollisionObject* m_collisionObject;	
	/// <summary>
	/// �A�j���[�V�����N���b�v
	/// </summary>
	AnimationClip m_animationClip[en_animationNum];
	//test
	Player* m_player = nullptr;
};

