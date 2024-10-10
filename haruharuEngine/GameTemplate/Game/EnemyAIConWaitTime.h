#pragma once
#include "EnemyAIConBase.h"

class EnemyBase;

class EnemyAIConWaitTime : public EnemyAIConBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="setTime"></param>
	EnemyAIConWaitTime(float setTime)
	{
		m_timerMax = setTime;
	}
	/// <summary>
	/// スタート関数、初期化するので、別処理が
	/// 入って、タイマーを初期化しなければならない時もこちらを使う
	/// </summary>
	void Start() override;
	/// <summary>
	/// 条件実行
	/// </summary>
	/// <returns></returns>
	bool Execution() override;
private:
	/// <summary>
	/// タイマー
	/// </summary>
	float m_timer = 0.0f;
	/// <summary>
	/// タイマー最大値
	/// </summary>
	float m_timerMax = 0.0f;
	/// <summary>
	/// タイマーを初期化するかどうか
	/// </summary>
	bool m_isTimerInit = false;
};

