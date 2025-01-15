#include "stdafx.h"
#include "WarriorAIMetaStop.h"

//���^AI�̏�����
void WarriorAIMetaStop::MetaAIInit()
{

}

//���^AI�̎��s
void WarriorAIMetaStop::MetaAIExecution(EnemySMBase* initEnemy)
{
	for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
	{

		if (ptr == initEnemy)
		{
			continue;
		}

		ptr->SetState(EnemySM_Warrior::en_stop);

	}
}

//���^AI�̏I��
const bool WarriorAIMetaStop::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}
