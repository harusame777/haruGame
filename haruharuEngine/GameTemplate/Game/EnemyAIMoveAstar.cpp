#include "stdafx.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyBase.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//スタート関数
void EnemyAIMoveAstar::EnemyAIStart()
{
	m_nvmMesh.Init("Assets/nvm/testnvm3.tkn");
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
			10.0f,							//AIエージョントの半径50.0
			10.0f							//AIエージェントの高さ200
		);
#ifdef DEBUG_MODE
	}
#endif

		//パス場を移動する
		//移動先を計算
		Vector3 pathMovePos = m_path.Move(
			myPos,
			2.0f,
			isEnd
		);

		//回転させる方向の計算
		Vector3 atan2CalcVec = pathMovePos - myPos;
		//正規化する
		atan2CalcVec.Normalize();
		//Y値を0にする
		atan2CalcVec.y = 0.0f;

		float angle = atan2(atan2CalcVec.x, atan2CalcVec.z);

		Quaternion finalRot;
		finalRot.SetRotation(Vector3::AxisY, angle);

		//移動した座標を送る
		GetEnemyPtr().SetPosition(pathMovePos);

		//回転値を送る
		GetEnemyPtr().SetRotation(finalRot);

		//正面値
		Vector3 newForward = Vector3::AxisZ;

		GetEnemyPtr().GetRotation().Apply(newForward);

		GetEnemyPtr().SetForward(newForward);
}