#pragma once
#include "EnemyAIMetaBase.h"
#include "PatrolRuteDataHolder.h"

class EnemyBase;

class WarriorAIMetaRetreat : public EnemyAIMetaBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WarriorAIMetaRetreat(std::shared_ptr<PatrolRuteDataHolder> patrolData)
	{
		m_sharedPatrolRuteDatas = patrolData;
	};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WarriorAIMetaRetreat() {};
	/// <summary>
	/// ���^AI�̏������֐�
	/// </summary>
	void MetaAIInit();
	/// <summary>
	/// ���^AI�̎��s�֐�
	/// </summary>
	/// <param name="initEnemy"></param>
	void MetaAIExecution(EnemySMBase* initEnemy);
	/// <summary>
	/// �����I��
	/// </summary>
	const bool ProcessEnd(EnemySMBase* initEnemy);
private:
	/// <summary>
	/// 
	/// </summary>
	void SearchRute();
	/// <summary>
	/// ���[�g���擾�������ǂ���
	/// </summary>
	bool m_isOneTimeGetRute = false;
	/// <summary>
	/// �ړ����I���������ǂ���
	/// </summary>
	bool m_isMoveEnd = false;
	/// <summary>
	/// �Ăяo�����G�l�~�[
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;
protected:
	/// <summary>
	/// ���ʂ��Ă��鏄�񃋁[�g�̃f�[�^
	/// </summary>
	std::shared_ptr<PatrolRuteDataHolder> m_sharedPatrolRuteDatas;
};

