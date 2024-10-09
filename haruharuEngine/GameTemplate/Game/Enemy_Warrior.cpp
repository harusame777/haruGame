#include "stdafx.h"
#include "Enemy_Warrior.h"
#include "Player.h"
#include "EnemyAIMoveAstar.h"
#include "EnemySM_Warrior.h"

//コンストラクタ
Enemy_Warrior::Enemy_Warrior()
{

}

//デストラクタ
Enemy_Warrior::~Enemy_Warrior()
{

}

//スタート関数
bool Enemy_Warrior::Start()
{
	m_modelRender.Init("Assets/modelData/testEnemy/youtai.tkm");
	m_modelRender.SetScale(1.0f, 1.0f, 1.0f);
	m_modelRender.SetPosition({500.0f,0.0f,0.0f});

	//シャドウマップに描画するようにする
	m_modelRender.SetShadowChasterFlag(false);

	m_player = FindGO<Player>("player");

	InitAIList();
	
	return true;
}

//アップデート関数
void Enemy_Warrior::Update()
{
	Vector3 plaPos = m_player->GetPosition();

	SetMoveTargetPosition(plaPos);

	AIListUpdate();

	m_modelRender.SetRotation(m_rotation);

	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
}

//ドロー関数
void Enemy_Warrior::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

//AIListの初期化
void Enemy_Warrior::InitAIList()
{
	//AIのListをこのエネミーに必要な物で初期化する
	//ステートマシン
	m_EnemyAIList.push_back(new EnemySM_Warrior);
	//経路探索
	m_EnemyAIList.push_back(new EnemyAIMoveAstar);

	//このエネミーのインスタンスをAIListのプログラムに渡す
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->BinedEnemy(this);
	}

	//AIListの中のプログラムのスタート関数を起動する
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->Start();
	}
}

void Enemy_Warrior::AIListUpdate()
{
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->Update();
	}
}