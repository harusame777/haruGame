#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"

class EnemyBase;

class EnemySM_Warrior : public EnemySMBase, public virtual EnemyAIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemySM_Warrior(){};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemySM_Warrior(){};
private:
	/// <summary>
	/// �G�l�~�[�E�H���A�[�̃X�e�[�g
	/// </summary>
	enum WarriorState
	{
		//�ҋ@���
		en_warrior_idle,
		//�ǐՏ��
		en_warrior_tracking,
	};
public:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	void Start() override;
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update() override;
	/// <summary>
	/// ���ʃX�e�[�g�ύX�֐�
	/// </summary>
	void ChangeState() override;
private:
	/// <summary>
	/// �G�l�~�[�E�H���A�[�̃X�e�[�g�A�ҋ@��Ԃŏ�����
	/// </summary>
	WarriorState m_warriorState = WarriorState::en_warrior_idle;
};

