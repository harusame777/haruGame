#include "stdafx.h"
#include "Enemy_Warrior.h"
#include "Player.h"
#include "EnemyAIMoveAstar.h"

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

	m_EnemyAIList.push_back(new EnemyAIMoveAstar);

	m_EnemyAIList[0]->BinedEnemy(this);
	
	return true;
}

//アップデート関数
void Enemy_Warrior::Update()
{
	Vector3 plaPos = m_player->GetPosition();

	SetMoveTargetPosition(plaPos);

	m_EnemyAIList[0]->Update();

	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
}

//ドロー関数
void Enemy_Warrior::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}