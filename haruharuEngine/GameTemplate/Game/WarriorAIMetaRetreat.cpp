#include "stdafx.h"
#include "WarriorAIMetaRetreat.h"
#include "EnemyBase.h"
#include "EnemyAIConBase.h"
#include "EnemyAIConWaitTime.h"

void WarriorAIMetaRetreat::MetaAIInit()
{

}

void WarriorAIMetaRetreat::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	SearchRute();
}

void WarriorAIMetaRetreat::SearchRute()
{

	//ゴール地点からプレイヤーまでの距離
	float ruteToMainWarriorDiff;
	//確定したパトロールルートのデータ
	PatrolRuteDataHolder::PatrolRuteData* confirmedRute = nullptr;
	//確定した距離
	float confirmedDiff;

	//ルートの数ぶん回す
	for (auto& ptr : m_sharedPatrolRuteDatas->m_patrolRuteList)
	{

		//そのパトロールルートが使用中だったら
		if (ptr->GetIsUse() == true)
		{
			//処理を飛ばす
			continue;
		}

		//長さ
		ruteToMainWarriorDiff = (ptr->GetPosition() - m_MainCallWarrior->GetEnemyPtr().GetPosition()).Length();

		//データが未入力状態であるまたは、
		//既に入力された距離より近かったら
		if (confirmedRute == nullptr
			|| ruteToMainWarriorDiff > confirmedDiff)
		{
			//現在のポインタのデータを入力して
			confirmedRute = ptr;

			//距離を代入する
			confirmedDiff = ruteToMainWarriorDiff;
		}
	
	}

	//もしデータが未入力状態じゃなかったら
	if (confirmedRute != nullptr)
	{
		//そのルートを使用中にして
		confirmedRute->SetIsUse(true);

		//そのルートを使用しているエネミーを登録して
		confirmedRute->SetUseEnemyPtr(m_MainCallWarrior);

		//追跡地点をエネミーに送る
		m_MainCallWarrior->GetEnemyPtr().SetMoveTargetPosition(confirmedRute->GetPosition());
	}

}

const bool WarriorAIMetaRetreat::ProcessEnd(EnemySMBase* initEnemy)
{
	for (auto& ptr : m_sharedPatrolRuteDatas->m_patrolRuteList)
	{

		if (m_MainCallWarrior == ptr->GetUseEnemyPtr())
		{
			ptr->SetIsUse(false);
			ptr->SetUseEnemyPtr(nullptr);
			m_isOneTimeGetRute = false;

			return true;
		}


	}

	return false;
}