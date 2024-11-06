#include "stdafx.h"
#include "Enemy_Warrior.h"
#include "Player.h"
#include "EnemyAIMoveAstar.h"
#include "EnemySM_Warrior.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

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

	//キャラクターコントローラーを初期化
	m_CController.Init(10.0f, 20.0f, m_position);

	//位置の初期設定
	m_CController.SetPosition(m_position);

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//球状のコリジョンを作成する。
	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 30.0f * m_scale.z);
	m_collisionObject->SetName("enemy_col");
	m_collisionObject->SetPosition(m_position);
	////コリジョンオブジェクトが自動で削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);
	
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

	m_collisionObject->SetPosition(m_position);

	m_CController.SetPosition(m_position);

#ifdef DEBUG_MODE
	DebugStateDisplay(GetStateNumber());
#endif

	m_modelRender.Update();
}

//ドロー関数
void Enemy_Warrior::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

#ifdef DEBUG_MODE
	m_debugStateDisplayRender.Draw(rc);
#endif
}

//AIListの初期化
void Enemy_Warrior::InitAIList()
{
	//ステートマシン
	m_enemyWarriorSM = new EnemySM_Warrior;

	m_enemyWarriorSM->BinedEnemy(this);

	m_enemyWarriorSM->EnemyAIStart();

}

void Enemy_Warrior::AIListUpdate()
{
	m_enemyWarriorSM->EnemyAIUpdate();
}