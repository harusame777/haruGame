#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "PatrolRuteDataHolder.h"
#include "WarriorAIMetaTracking.h"
#include "WarriorAIMetapPatrol.h"
#include "EnemySM_Warrior.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"
#include "Player.h"
#include "DebugEnemyTrackingState.h"
#include "WarriorAIMetaRetreat.h"

//処理順
//
//1.プレイヤーを見つける
//
//2.自分の周りのエネミーに呼びかける
//
//3.呼びかけに気づいてくれた自分以外のエネミーの現在のステートを取得する
//
//4.自分のステート取得し、自分以外のエネミーのステートと見比べる
//
//5.結果によってステートの番号を返す
//
//どのタイミングで追跡ステートを変更するか？
//エネミーがプレイヤーに気づいて周囲に呼びかけを行ったタイミングで実行したい
//追跡中にほかのエネミーが気づいたりしたら、強制的に後ろを追うようにする。

//スタート関数
bool EnemyAIMetaWarrior::Start()
{

	//共通のデータホルダーを初期化
	m_warriorDataHolder = std::make_shared<WarriorDataHolder>();
	
	m_debugWarriorTrackingState = NewGO<DebugEnemyTrackingState>(0, "debug");

	m_debugWarriorTrackingState->InitWarriorListData(m_warriorDataHolder);

	//共通のデータホルダーを初期化
	m_patrolRuteDataHolder = std::make_shared<PatrolRuteDataHolder>();

	//レベルレンダーを使用して巡回地点を取得する
	m_patrolRuteLevelRender.Init("Assets/mapLevel/testLevel3.tkl", [&](LevelObjectData_Render& objData)
		{
			if (objData.ForwardMatchName(L"patrolroute") == true)
			{
				PatrolRuteDataHolder::PatrolRuteData* newData = new PatrolRuteDataHolder::PatrolRuteData;

				//レベルから位置を取得する
				newData->SetPosition(objData.m_position);

				//配列に格納する
				m_patrolRuteDataHolder->m_patrolRuteList.push_back(newData);

				return true;
			}
			return true;
		});

	//メタAIの処理プログラムを初期化
	ListInitAIMeta(new WarriorAIMetaTracking(m_warriorDataHolder), true);

	//メタAIの処理プログラムを初期化
	ListInitAIMeta(new WarriorAIMetapPatrol(m_warriorDataHolder, m_patrolRuteDataHolder), false);

	//メタAIの処理プログラムを初期化
	ListInitAIMeta(new WarriorAIMetaRetreat(m_patrolRuteDataHolder), true);

	for (auto& metaAIs : m_AIMetaList)
	{
		//初期化
		//metaAIs->MetaAIInit();
		metaAIs->GetAIMetaProgram()->MetaAIInit();
	}

	return true;
}

//ウォリアー全体の追跡ステートを変更する関数
void EnemyAIMetaWarrior::MetaAIExecution(EnemySM_Warrior* enemyPtr, const MetaAIMode setMode)
{

	if (m_AIMetaList[setMode]->GetAIMetaProgram()->GetOneTimeUpdateFlag() == true &&
		m_AIMetaList[setMode]->GetOneTimeOnlyUpdate() == true)
	{
		return;
	}

	if (m_AIMetaList[setMode]->GetOneTimeOnlyUpdate() == true)
	{
		m_AIMetaList[setMode]->GetAIMetaProgram()->SetOneTimeUpdateFlag(true);
	}

	//この関数を呼び出したエネミーのポインタを格納する
	m_MainCallWarrior = enemyPtr;

	//処理を実行する
	m_AIMetaList[setMode]->GetAIMetaProgram()->MetaAIExecution(enemyPtr);

}

//リストにウォリアーを代入
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//リストにウォリアーを代入する
	m_warriorDataHolder->m_warriorDatas.push_back(enemyPtr);
}

void EnemyAIMetaWarrior::ListInitAIMeta(EnemyAIMetaBase* programData, const bool isOneTime)
{
	//新しくメタAIのデータを作成する
	MetaAIData* newProgramData = new MetaAIData;
	//メタAIのプログラムデータを設定する
	newProgramData->SetAIMetaProgram(programData);
	//このメタAIが終了まで一回しか起動しないのかを設定する
	newProgramData->SetOneTimeOnlyUpdate(isOneTime);
	//データを格納する
	m_AIMetaList.push_back(newProgramData);
}

void EnemyAIMetaWarrior::ProcessEnd(const MetaAIMode setMode, EnemySMBase* initEnemy)
{

	//すべての処理が終了していたら
	if (m_AIMetaList[setMode]->GetAIMetaProgram()->ProcessEnd(initEnemy) == true)
	{
		//もう一度起動できるようにする
		m_AIMetaList[setMode]->GetAIMetaProgram()->SetOneTimeUpdateFlag(false);
	}

}