#include "stdafx.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyBase.h"
#include "WarriorDataHolder.h"
#include "Player.h"
#include <cmath>
#include "EnemyAIConBase.h"
#include "EnemyAIConWaitTime.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//スタート関数
void EnemyAIMoveAstar::EnemyAIStart()
{
	m_nvmMesh.Init("Assets/nvm/testnvm10.tkn");

	m_player = FindGO<Player>("player");

	m_timer = (new EnemyAIConWaitTime(1.0f));
 
}

//アップデート関数
void EnemyAIMoveAstar::EnemyAIUpdate()
{
	bool isEnd;

	//自分自身の位置を取得
	Vector3 myPos = GetEnemyPtr().GetPosition();
	
	//移動先の位置を取得
	Vector3 tarPos = GetEnemyPtr().GetMoveTargetPosition();

#ifdef DEBUG_MODE
	if (g_pad[0]->IsPress(enButtonA))
	{
#endif
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

						EnemySM_Warrior* aroundEnemyPtr = nullptr;

						//このエネミーが回り込みステートのエネミーでなければ
						if (GetEnemyPtr().GetTrackingStateNumber() != WarriorTrackingState::en_wrapAround)
						{
							//戻す
							return t;
						}

						Vector3 behindWarriorPos;

						if (GetEnemyPtr().GetTrackingStateNumber() == WarriorTrackingState::en_wrapAround) {
							EnemySM_Warrior* chaseEnemyPtr = nullptr;
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
								/*auto diff = chaseEnemyPtr->GetEnemyPtr().GetPosition() - nextCell->cell->GetCenterPosition();
								float t =pow( min(1.0f, diff.Length() / 10000.0f), 0.1f);
								auto toPlayerFromChaseEnemy = m_player->GetPosition() - chaseEnemyPtr->GetEnemyPtr().GetPosition();
								auto toPlayerFromNextCell = m_player->GetPosition() - nextCell->cell->GetCenterPosition();
								toPlayerFromChaseEnemy.Normalize();
								toPlayerFromNextCell.Normalize();
								t *= max(0.0f, toPlayerFromChaseEnemy.Dot(toPlayerFromNextCell));
								t = std::lerp(100000, 0, t);
								*/
								return t;
							}

						}

#if 0
						for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
						{
							if (ptr->GetTrackingState() != WarriorTrackingState::en_chaseFromBehind)
							{
								return t;
							}

							behindWarriorPos = ptr->GetEnemyPtr().GetPosition();

							Vector3 cellPos = nextCell->cell->GetCenterPosition();

							float behindWarriorToCellPosDiff = (cellPos - behindWarriorPos).Length();

							Vector3 playerPos = m_player->GetPosition();

							float behindWarriorToPlayerPosDiff = (playerPos - behindWarriorPos).Length();

							if (behindWarriorToCellPosDiff <= 500.0f/*behindWarriorToPlayerPosDiff*/)
							{
								t += 10000.0f;
							}

						}
#endif

						return t;
				}
			);
		}
#ifdef DEBUG_MODE
	}
#endif

		//パス場を移動する
		//移動先を計算
		Vector3 pathMovePos = m_path.Move(
			myPos,
			5.0f,
			isEnd
		);

		//回転させる方向の計算
		Vector3 atan2CalcVec = pathMovePos - myPos;
		//正規化する
		atan2CalcVec.Normalize();
		//Y値を0にする
		atan2CalcVec.y = 0.0f;

		RotationValueCalc(atan2CalcVec);

		//Vector3 moveVec = { 0.0f,0.0f,0.0f };

		//moveVec = pathMovePos;

		//moveVec.Normalize();

		//moveVec += GetEnemyPtr().GetFoward() * 150.0f;

		//Vector3 newPos = GetEnemyPtr().GetCController()->Execute(moveVec, g_gameTime->GetFrameDeltaTime());

		////移動した座標を送る
		//GetEnemyPtr().SetPosition(newPos);

		GetEnemyPtr().SetPosition(pathMovePos);


		//正面値
		Vector3 newForward = Vector3::AxisZ;

		GetEnemyPtr().GetRotation().Apply(newForward);

		GetEnemyPtr().SetForward(newForward);
}

void EnemyAIMoveAstar::RotationValueCalc(const Vector3& direction)
{
	float angle = atan2(direction.x, direction.z);

	Quaternion finalRot;
	finalRot.SetRotation(Vector3::AxisY, angle);

	//回転値を送る
	GetEnemyPtr().SetRotation(finalRot);
}