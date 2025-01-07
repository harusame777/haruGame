#include "stdafx.h"
#include "EnemyAIMove.h"
#include "EnemyBase.h"
#include "Player.h"
#include "EnemyAIConBase.h"

//定数等
namespace{
	static const float ENEMY_SPEED = 200.0f;
}

//スタート関数
void EnemyAIMove::EnemyAIStart()
{
	m_player = FindGO<Player>("player");
}

//アップデート関数
void EnemyAIMove::EnemyAIUpdate()
{
	//このエネミーのポジションを取得
	Vector3 enemyPos = GetEnemyPtr().GetPosition();
	//プレイヤーのポジションを取得
	Vector3 playerPos = m_player->GetPosition();

	//エネミーからプレイヤーに伸びるベクトルを計算
	Vector3 diff = playerPos - enemyPos;
	//ベクトルを単位ベクトルに
	diff.Normalize();
	//スピードを加算
	Vector3 moveSpeed = diff * ENEMY_SPEED;
	//最終的な移動位置を設定
	Vector3 finalPos = GetEnemyPtr().GetCController()
		->Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	//位置を設定
	GetEnemyPtr().SetPosition(finalPos);

	//回転地の計算
	RotationCalc(moveSpeed);

	//正面値
	Vector3 newForward = Vector3::AxisZ;

	GetEnemyPtr().SetForward(newForward);
}

//回転値の計算
void EnemyAIMove::RotationCalc(const Vector3& moveSpeed)
{
	if (fabsf(moveSpeed.x) < 0.001f
		&& fabsf(moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(moveSpeed.x, moveSpeed.z);
	Quaternion rotation;
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	rotation.SetRotationY(angle);
	//回転値を設定
	GetEnemyPtr().SetRotation(rotation);
}