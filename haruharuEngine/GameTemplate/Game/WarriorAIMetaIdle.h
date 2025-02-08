#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"

class WarriorAIMetaIdle : public EnemyAIMetaBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WarriorAIMetaIdle(std::shared_ptr<WarriorDataHolder> enemyData)
	{
		m_sharedWarriorDatas = enemyData;
	};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WarriorAIMetaIdle(){}
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
	/// �Ăяo�����G�l�~�[
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;
	/// <summary>
	/// ���ʂ��Ă���E�H���A�[�̃f�[�^
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
};

