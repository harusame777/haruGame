#include "stdafx.h"
#include "EnemyAIConWaitTime.h"
#include "EnemyBase.h"

//スタート関数
void EnemyAIConWaitTime::Start()
{
	//タイマーを0.0fに
	m_timer = 0.0f;

	//フラグをfalseに
	m_isTimerInit = false;
}

//条件実行関数
bool EnemyAIConWaitTime::Execution()
{
	//初期化されていなかったら
	if (!m_isTimerInit)
	{
		//初期化する
		m_timer = m_timerMax;
		//フラグをtrueに
		m_isTimerInit = true;
	}

	//フレームタイムでタイマーを減らす
	m_timer -= g_gameTime->GetFrameDeltaTime();
	
	//もしタイマーが0.0f以下だったら
	if (m_timer <= 0.0f) 
	{
		//タイマーを0.0fに
		m_timer = 0.0f;

		//フラグをfalseに
		m_isTimerInit = false;

		//初期化する
		m_timer = m_timerMax;

		//trueを返す
		return true;
	}

	//falseを返す
	return false;
}