#pragma once
#include "WarriorDataHolder.h"
#include "EnemyAIBase.h"

class EnemyAIConBase;
class EnemyBase;

class EnemyAIMetaBase : public EnemyAIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyAIMetaBase(std::shared_ptr<WarriorDataHolder> data)
	{
		m_sharedWarriorDatas = data;
	}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EnemyAIMetaBase(){}
	/// <summary>
	/// ���^AI�̏�����
	/// </summary>
	virtual void MetaAIInit() = 0;
	/// <summary>
	/// ���^AI���s
	/// </summary>
	virtual void MetaAIExecution(EnemySMBase* initEnemy) = 0;
protected:
	/// <summary>
	/// ���ʂ��Ă���E�H���A�[�̃f�[�^
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
};

