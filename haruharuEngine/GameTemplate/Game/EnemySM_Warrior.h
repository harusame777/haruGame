#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"
#include "EnemyWarriorTrackingState.h"

class EnemyBase;
class EnemyAIMetaWarrior;

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
	void EnemyAIStart() override;
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void EnemyAIUpdate() override;
	/// <summary>
	/// ���ʃX�e�[�g�ύX�֐�
	/// </summary>
	void ChangeState() override;
	/// <summary>
	/// ���ԏ����֐�
	/// </summary>
	void TimeUpdate();
	/// <summary>
	/// �ǐՏ�Ԃ��H
	/// </summary>
	/// <returns></returns>
	const bool IsTracking() const
	{
		return m_isTracking;
	}
private:
	/// <summary>
	/// �G�l�~�[�E�H���A�[�̃X�e�[�g�A�ҋ@��Ԃŏ�����
	/// </summary>
	WarriorState m_warriorState = WarriorState::en_warrior_idle;
	/// <summary>
	/// �G�l�~�[�E�H���A�[�̒ǐՃX�e�[�g�A�ҋ@��ԂŔ�ǐՏ��
	/// </summary>
	WarriorTrackingState m_warriorTrackingState = WarriorTrackingState::en_nonTracking;
	/// <summary>
	/// ���Ԃɂ���ĒǐՂ������邩�ǂ���
	/// </summary>
	bool m_isTrackingTimeOver = false;
	/// <summary>
	/// �ǐՏ�Ԃ��ǂ���
	/// </summary>
	bool m_isTracking = false;
	/// <summary>
	/// �E�H���A�[�̃��^AI
	/// </summary>
	EnemyAIMetaWarrior* m_warriorMetaAI;
};

