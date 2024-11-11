#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"

class EnemyAIMetaWarrior;
class WarriorDataHolder;
class Player;

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
	/// <summary>
	/// �G�l�~�[�E�H���A�[�̃X�e�[�g
	/// </summary>
	enum WarriorState
	{
		//�ҋ@���
		en_warrior_idle,
		//�ǐՏ��
		en_warrior_tracking,
		//������
		en_warrior_patrol,
		//���^AI�w�ߒǐՏ��
		en_warrior_trackingMetaAI,
	};
public:
	enum EnemyAINum
	{
		en_enemyAIMoveAstar
	};
	enum EnemyAIConNum
	{
		en_enemyAIConSearch,
		en_enemyAIConWaitTime10f,
		en_enemyAIConColPlayer
	};
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
	/// �X�e�[�g�J�ځF�ǐ�
	/// </summary>
	void StateTransition_Tracking();
	/// <summary>
	/// �ǐՃX�e�[�g�i���o�[��ݒ�
	/// </summary>
	/// <param name="stateNum = �X�e�[�g�i���o�["></param>
	void SetTrackingState(const WarriorTrackingState setState)
	{
		GetEnemyPtr().SetTrackingStateNumber(setState);
		m_warriorTrackingState = setState;
	}
	/// <summary>
	/// �ǐՃX�e�[�g�i���o�[���擾
	/// </summary>
	/// <returns></returns>
	const WarriorTrackingState GetTrackingState()
	{
		return m_warriorTrackingState;
	}
	/// <summary>
	/// �X�e�[�g�i���o�[��ݒ�
	/// </summary>
	/// <param name="stateNum = �X�e�[�g�i���o�["></param>
	void SetState(const WarriorState setState)
	{
		GetEnemyPtr().SetStateNumber(setState);
		m_warriorState = setState;
	}
	/// <summary>
	/// �X�e�[�g�i���o�[���擾
	/// </summary>
	/// <returns></returns>
	const WarriorState GetState()
	{
		return m_warriorState;
	}
	/// <summary>
	/// ���^AI�ɌĂ΂ꂽ���ǂ���
	/// </summary>
	/// <param name="setBool"></param>
	void SetCallMetaAI(const bool setBool)
	{
		m_isCallMetaAI = setBool;
	}
	/// <summary>
	/// ���^AI�ɌĂ΂ꂽ���ǂ���
	/// </summary>
	/// <returns></returns>
	const bool GetCallMetaAI()
	{
		
		return m_isCallMetaAI;
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
	/// �ҋ@��Ԃ�
	/// </summary>
	bool m_isWaitIdle = false;
	/// <summary>
	/// 
	/// </summary>
	bool m_isCallMetaAI = false;
	/// <summary>
	/// �E�H���A�[�̃��^AI
	/// </summary>
	EnemyAIMetaWarrior* m_warriorMetaAI;
	/// <summary>
	/// �E�H���A�[�̋��ʃf�[�^�z���_�`
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
	Player* m_player = nullptr;
};

