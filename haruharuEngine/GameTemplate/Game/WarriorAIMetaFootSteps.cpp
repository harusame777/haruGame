#include "stdafx.h"
#include "WarriorAIMetaFootSteps.h"
#include "GameSound.h"
#include "Player.h"

namespace {

	static const float MAX_RANGE_CALC_NUM = 500.0f;
	static const float MIN_RANGE_NUM = 0.0f;

	static const float MAX_VOLUME_NUM = 1.0f;
	static const float MIN_VOLUME_NUM = 0.0f;
}

//メタAIの初期化
void WarriorAIMetaFootSteps::MetaAIInit()
{
	m_player = FindGO<Player>("player");

	m_gameSound = FindGO<GameSound>("gamesound");
}

//メタAIの実行
void WarriorAIMetaFootSteps::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	LengthCalc();

	float finalValume = RatioCalc();

	m_gameSound->LocalSoundOrder(
		GameSound::en_enemyWarriorWalkSound
		, false
		, finalValume);
}

//距離計算
void WarriorAIMetaFootSteps::LengthCalc()
{
	Vector3 playerPos = m_player->GetPosition();

	Vector3 enemyPos = m_MainCallWarrior
		->GetEnemyPtr().GetPosition();

	Vector3 playerToEnemydiff = playerPos - enemyPos;

	m_playerToEnemyDiffSq = playerToEnemydiff.LengthSq();
}

//距離計算
const float& WarriorAIMetaFootSteps::RatioCalc()
{
	float finalValue;

	float RangeValue = MAX_RANGE_CALC_NUM * MAX_RANGE_CALC_NUM;

	finalValue = MIN_VOLUME_NUM + (m_playerToEnemyDiffSq / RangeValue) *
		(MAX_VOLUME_NUM - MIN_VOLUME_NUM);

	return finalValue;
}

//処理終了
const bool WarriorAIMetaFootSteps::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}
