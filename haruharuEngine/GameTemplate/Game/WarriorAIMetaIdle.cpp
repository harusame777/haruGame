#include "stdafx.h"
#include "WarriorAIMetaIdle.h"

//���^AI�̏�����
void WarriorAIMetaIdle::MetaAIInit()
{

}

//���^AI�̎��s
void WarriorAIMetaIdle::MetaAIExecution(EnemySMBase* initEnemy)
{
	for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
	{

		ptr->SetState(EnemySM_Warrior::en_warrior_idle);

	}
}

//���^AI�̏I��
const bool WarriorAIMetaIdle::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}