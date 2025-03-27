#include "stdafx.h"
#include "WarriorAIMetaChaseBGM.h"
#include "GameSound.h"


//起動関数
void WarriorAIMetaChaseBGM::MetaAIInit()
{

	m_gameSound = FindGO<GameSound>("gameSound");

	m_gameBGM = &m_gameSound->ReturnPointerLocalSoundOrder(GameSound::en_chaseBGM, 0.5f);

}

//実行関数
void WarriorAIMetaChaseBGM::MetaAIExecution(EnemySMBase* initEnemy)
{
	//追跡状態のエネミーを探す
	SearchTrackingStateEnemy();

	//もしBGMが鳴ってたら
	if (m_isBGMPlayBack == true)
	{
		//もし追跡中のエネミーが居なかったら
		if (m_isTrackingStateEnemy == false)
		{
			//BGMを止める
			BGMEnd();
		}
	}
	else
	{
		//もし追跡中のエネミーが居たら
		if (m_isTrackingStateEnemy == true)
		{
			//BGMを始める
			BGMStart();
		}
	}

	if (m_isBGMFadeOut == true)
	{
		BGMFadeOut();
	}

}

//追跡状態のエネミーが存在するかどうかを探す
void WarriorAIMetaChaseBGM::SearchTrackingStateEnemy()
{
	int enemyStateNum = 0;

	for (auto& enemyPtr : m_sharedWarriorDatas->m_warriorDatas)
	{
		enemyStateNum = enemyPtr->GetEnemyPtr().GetStateNumber();
		
		if (enemyStateNum == EnemyBase::en_tracking)
		{
			m_isTrackingStateEnemy = true;
			return;
		}
	}

	m_isTrackingStateEnemy = false;
}

//BGM再生関数
void WarriorAIMetaChaseBGM::BGMStart()
{

	m_gameBGM->Play(true);

	m_gameBGM->SetVolume(0.5f);

	m_isBGMPlayBack = true;

	m_volumeRatio = 0.0f;

}

void WarriorAIMetaChaseBGM::BGMEnd()
{

	m_isBGMFadeOut = true;

}

void WarriorAIMetaChaseBGM::BGMFadeOut()
{
	if (m_volumeRatio > 1.0f)
	{
		m_volumeRatio = 0.0f;

		m_gameBGM->Stop();

		m_isBGMPlayBack = false;

		m_isBGMFadeOut = false;
	}

	m_volumeRatio += g_gameTime->GetFrameDeltaTime();

	m_gameBGM->SetVolume(Leap(0.5f, 0.0f, m_volumeRatio));
}

//終了関数
const bool WarriorAIMetaChaseBGM::ProcessEnd(EnemySMBase* initEnemy)
{
	m_gameBGM->Stop();

	m_isBGMPlayBack = false;

	return true;
}
