#include "stdafx.h"
#include "WarriorAIMetaIdle.h"

//メタAIの初期化
void WarriorAIMetaIdle::MetaAIInit()
{

}

//メタAIの実行
void WarriorAIMetaIdle::MetaAIExecution(EnemySMBase* initEnemy)
{
	for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
	{

		ptr->SetState(EnemySM_Warrior::en_warrior_idle);

	}
}

//メタAIの終了
const bool WarriorAIMetaIdle::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}