#include "stdafx.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyBase.h"
#include "WarriorDataHolder.h"
#include "Player.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//スタート関数
void EnemyAIMoveAstar::EnemyAIStart()
{
	m_nvmMesh.Init("Assets/nvm/testnvm6.tkn");

	m_player = FindGO<Player>("player");
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
					
					return t;
			}
		);
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