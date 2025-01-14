#include "stdafx.h"
#include "Enemy_Warrior.h"
#include "Player.h"
#include "EnemyAIMoveAstar.h"
#include "EnemySM_Warrior.h"
#include "EnemyAIMetaWarrior.h"
#include "GameSound.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//AttackImpact

//コンストラクタ
Enemy_Warrior::Enemy_Warrior()
{

}

//デストラクタ
Enemy_Warrior::~Enemy_Warrior()
{
	delete m_enemyWarriorSM;

	DeleteGO(m_collisionObject);
}


//スタート関数
bool Enemy_Warrior::Start()
{
	m_animationClip[EnAnimationClip::en_idle].Load("Assets/modelData/enemyWarrior/enemy_Warrior_idle.tka");
	m_animationClip[EnAnimationClip::en_idle].SetLoopFlag(true);

	m_animationClip[EnAnimationClip::en_patrol].Load("Assets/modelData/enemyWarrior/enemy_Warrior_run.tka");
	m_animationClip[EnAnimationClip::en_patrol].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/enemyWarrior/enemy_Warrior.tkm", m_animationClip,en_animationNum
		,enModelUpAxisZ,ModelRender::en_shadowShader);
	m_modelRender.SetScale(1.0f, 1.0f, 1.0f);
	m_modelRender.SetPosition({500.0f,0.0f,0.0f});

	//アニメーションイベント用関数設定
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	m_gameSound = FindGO<GameSound>("gameSound");

	//シャドウマップに描画するようにする
	m_modelRender.SetShadowChasterFlag(false);


	InitAIList();

	//キャラクターコントローラーを初期化
	m_CController.Init(10.0f, 20.0f, m_position);

	//位置の初期設定
	m_CController.SetPosition(m_position);

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);

	EnemyAIMetaWarrior* enemyMetaAI = FindGO<EnemyAIMetaWarrior>("MetaAI");

	std::shared_ptr<WarriorDataHolder> warriorDataHolder;

	warriorDataHolder = enemyMetaAI->GetEnemyDatas();

	int enemyNum = warriorDataHolder->m_warriorDatas.size();

	char colName[20] = "enemy_col:";

	char enemyNumChar[20] = "";

	std::sprintf(enemyNumChar, "%d", enemyNum);  // 数字を文字列に変換
	std::strcat(colName, enemyNumChar);        // 配列に追加

	SetCollisionName(colName);

	//球状のコリジョンを作成する。
	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 30.0f * m_scale.z);
	m_collisionObject->SetName(GetCollisionName());
	m_collisionObject->SetPosition(m_position);
	////コリジョンオブジェクトが自動で削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);
	
	return true;
}

void Enemy_Warrior::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	if (wcscmp(eventName, L"enemyRunSound") == 0)
	{
		//m_gameSound->LocalSoundOrder(GameSound::en_enemyWarriorWalkSound,false
		//	,0.5f
		//	,m_position
		//);

		//m_gameSound->SoundListInit(
		//	GameSound::en_enemyWarriorWalkSound,
		//	GameSound::en_priority_low,
		//	0.5f);
	}
}

//アップデート関数
void Enemy_Warrior::Update()
{
	AIListUpdate();

	m_modelRender.PlayAnimation(m_animationClipState);

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