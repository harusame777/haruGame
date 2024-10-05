#include "stdafx.h"
#include "Enemy_Warrior.h"
#include "Player.h"

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

	m_nvmMesh.Init("Assets/nvm/test.tkn");

	return true;
}

//アップデート関数
void Enemy_Warrior::Update()
{
	bool isEnd;

	Vector3 playerPos = m_player->GetPosition();

	m_pathFiding.Execute(
		m_path,
		m_nvmMesh,
		m_position,
		playerPos,
		PhysicsWorld::GetInstance(),
		50.0f,
		200.0f
	);

	//パス場を移動する
	m_position = m_path.Move(
		m_position,
		10.0f,
		isEnd
	);

	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
}

//ドロー関数
void Enemy_Warrior::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}