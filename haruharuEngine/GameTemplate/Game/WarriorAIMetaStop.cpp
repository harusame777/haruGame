#include "stdafx.h"
#include "WarriorAIMetaStop.h"

//メタAIの初期化
void WarriorAIMetaStop::MetaAIInit()
{

}

//メタAIの実行
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

//メタAIの終了
const bool WarriorAIMetaStop::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}
