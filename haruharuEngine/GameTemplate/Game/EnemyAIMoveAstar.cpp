#include "stdafx.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyBase.h"
#include "WarriorDataHolder.h"
#include "Player.h"
#include <cmath>
#include "EnemyAIConBase.h"
#include "EnemyAIConWaitTime.h"
#include "EnemyAIConWallSearch.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//定数等
namespace {
	static const float ENEMY_SPEED = 150.0f;
}

//スタート関数
void EnemyAIMoveAstar::EnemyAIStart()
{
	m_nvmMesh.Init("Assets/nvm/testnvm10.tkn");

	m_player = FindGO<Player>("player");

	m_timer = (new EnemyAIConWaitTime(1.0f));

	m_wallChack = (new EnemyAIConWallSearch);

	m_wallChack->BinedEnemy(&GetEnemyPtr());

	m_wallChack->InitData();
 
}

//アップデート関数
void EnemyAIMoveAstar::EnemyAIUpdate()
{
	PathFidingExecute();
	
	bool isRetreat = false;

	if (aroundEnemyPtr)
	{
		isRetreat = aroundEnemyPtr->GetRetreat();
	}

	if (m_wallChack->Execution())
	{
		MoveAstar();
	}
	else
	{
		MoveUsually();
	}
}

void EnemyAIMoveAstar::PathFidingExecute()
{
	//自分自身の位置を取得
	Vector3 myPos = GetEnemyPtr().GetPosition();

	//移動先の位置を取得
	Vector3 tarPos = GetEnemyPtr().GetMoveTargetPosition();

	if (m_timer->Execution()) {
		m_timer->InitData();
		//パスを検索する
		m_pathFiding.Execute(
			m_path,							//構築されたパスの格納先
			m_nvmMesh,						//ナビメッシュ
			myPos,							//開始座標
			tarPos,							//移動先座標
			PhysicsWorld::GetInstance(),	//物理エンジン
			1.0f,							//AIエージョントの半径50.0
			1.0f,							//AIエージェントの高さ200
			[&](const nsAI::PathFinding::CellWork* nextCell
				)-> float {							//カスタムヒューリスティックコストの計算

					float t = 0.0f;


					//このエネミーが回り込みステートのエネミーでなければ
					if (GetEnemyPtr().GetTrackingStateNumber() != WarriorTrackingState::en_wrapAround)
					{
						//戻す
						return t;
					}

					Vector3 behindWarriorPos;

					if (GetEnemyPtr().GetTrackingStateNumber() == WarriorTrackingState::en_wrapAround) {
						for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
						{
							if (ptr->GetTrackingState() == WarriorTrackingState::en_chaseFromBehind)
							{
								chaseEnemyPtr = ptr;
							}
							if (ptr->GetTrackingState() == WarriorTrackingState::en_wrapAround)
							{
								aroundEnemyPtr = ptr;
							}
						}

						if (chaseEnemyPtr) {
							//追跡中の敵と自分との距離を計算して近ければ退却させる
							auto toAroundEnemyFromChaseEnemy = (chaseEnemyPtr->GetEnemyPtr().GetPosition() - GetEnemyPtr().GetPosition()).Length();
							if (toAroundEnemyFromChaseEnemy < 100.0f)
							{
								aroundEnemyPtr->SetRetreat(true);

								return 0.0f;
							}
							// 追跡中の敵との距離を計算して、近いほどコストが高くなるようにする
							auto toPlayerFromChaseEnemy = m_player->GetPosition() - chaseEnemyPtr->GetEnemyPtr().GetPosition();
							auto toPlayerFromNextCell = m_player->GetPosition() - nextCell->cell->GetCenterPosition();
							toPlayerFromChaseEnemy.Normalize();
							toPlayerFromNextCell.Normalize();
							if (toPlayerFromChaseEnemy.Dot(toPlayerFromNextCell) > 0.0f) {
								return 1000000.0f;
							}
							return 0.0f;
						}

					}

					return t;
			}
		);
	}
}

//エースター移動
void EnemyAIMoveAstar::MoveAstar()
{
	bool isEnd;

	//自分自身の位置を取得
	Vector3 myPos = GetEnemyPtr().GetPosition();

	//パス場を移動する
	//移動先を計算
	Vector3 pathMovePos = m_path.Move(
		myPos,
		3.0f,
		isEnd
	);

	//回転させる方向の計算
	Vector3 atan2CalcVec = pathMovePos - myPos;
	//正規化する
	atan2CalcVec.Normalize();
	//Y値を0にする
	atan2CalcVec.y = 0.0f;

	AstarRotationValueCalc(atan2CalcVec);

	GetEnemyPtr().SetPosition(pathMovePos);

	//正面値
	Vector3 newForward = Vector3::AxisZ;

	GetEnemyPtr().GetRotation().Apply(newForward);

	GetEnemyPtr().SetForward(newForward);
}

//通常移動
void EnemyAIMoveAstar::MoveUsually()
{
	//このエネミーのポジションを取得
	Vector3 enemyPos = GetEnemyPtr().GetPosition();
	//プレイヤーのポジションを取得
	Vector3 targetPos = GetEnemyPtr().GetMoveTargetPosition();

	//エネミーからプレイヤーに伸びるベクトルを計算
	Vector3 diff = targetPos - enemyPos;
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
	UsuallyRotationValueCalc(moveSpeed);

	//正面値
	Vector3 newForward = Vector3::AxisZ;

	GetEnemyPtr().SetForward(newForward);
}

void EnemyAIMoveAstar::AstarRotationValueCalc(const Vector3& direction)
{
	float angle = atan2(direction.x, direction.z);

	Quaternion finalRot;
	finalRot.SetRotation(Vector3::AxisY, angle);

	//回転値を送る
	GetEnemyPtr().SetRotation(finalRot);
}

void EnemyAIMoveAstar::UsuallyRotationValueCalc(const Vector3& moveSpeed)
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