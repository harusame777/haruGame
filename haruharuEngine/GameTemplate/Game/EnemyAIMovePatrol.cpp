#include "stdafx.h"
#include "EnemyAIMovePatrol.h"
#include "EnemyBase.h"

//定数等
namespace {
	static const float SEARCH_RANGE = 200.0f;
}

//スタート関数
void EnemyAIMovePatrol::EnemyAIStart()
{
	//レベルレンダーを使用してレベルから巡回ポイントを取得
}

//アップデート関数
void EnemyAIMovePatrol::EnemyAIUpdate()
{

	//自分自身の位置を取得
	Vector3 myPos = GetEnemyPtr().GetPosition();

	//もしエネミーがプレイヤーを見失ったあとだったら
	if (true)
	{
		//SEARCH_RANGE外の巡回ポイントを探索してそこにランダムで向かう
	}

	//もしエネミーが巡回ステートなら
	if (true)
	{
		//巡回する
	}
}