#include "stdafx.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyBase.h"

//アップデート関数
void EnemyAIMoveAstar::Update()
{
	m_nvmMesh.Init("Assets/nvm/test.tkn");

	bool isEnd;

	//自分自身の位置を取得
	Vector3 myPos = GetEnemyPtr().GetPosition();
	
	//移動先の位置を取得
	Vector3 tarPos = GetEnemyPtr().GetMoveTargetPosition();

	//パスを検索する
	m_pathFiding.Execute(
		m_path,							//構築されたパスの格納先
		m_nvmMesh,						//ナビメッシュ
		myPos,							//開始座標
		tarPos,							//移動先座標
		PhysicsWorld::GetInstance(),	//物理エンジン
		50.0f,							//AIエージョントの半径
		200.0f							//AIエージェントの高さ
	);

	//パス場を移動する
	//移動先を計算
	Vector3 pathMovePos = m_path.Move(
		myPos,
		10.0f,
		isEnd
	);

	//移動した座標を送る
	GetEnemyPtr().SetPosition(pathMovePos);
}