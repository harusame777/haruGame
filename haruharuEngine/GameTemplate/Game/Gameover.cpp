#include "stdafx.h"
#include "Gameover.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Load.h"

//定数等
namespace {
	static const float BACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float BACKSIDE_SPRITE_H_SIZE = 900.0f;
}

//スタート関数
bool Gameover::Start()
{
	m_backSideSprite.Init("Assets/modelData/title/back_side_1.DDS",
		BACKSIDE_SPRITE_W_SIZE,
		BACKSIDE_SPRITE_H_SIZE);

	m_load = FindGO<Load>("load");

	EnemyAIMetaWarrior* enemyMetaAI = FindGO<EnemyAIMetaWarrior>("MetaAI");

	std::shared_ptr<WarriorDataHolder> warriorDataHolder;

	warriorDataHolder = enemyMetaAI->GetEnemyDatas();

	for (auto& ptr : warriorDataHolder->m_warriorDatas)
	{

		if (ptr->GetEnemyPtr().GetStateNumber() 
			== EnemySM_Warrior::en_attack)
		{
			m_attackEnemy = &ptr->GetEnemyPtr();
		}

	}

	m_gameoverState = GameoverState::en_cameraEasing;

	return true;
}

//アップデート関数
void Gameover::Update()
{
	GameoverStateUpdate();
}

//ステート更新関数
void Gameover::GameoverStateUpdate()
{
	Vector3 cameraToEnemyVec;
	Vector3 targetPos;

	switch (m_gameoverState)
	{
	case Gameover::en_standby:
		break;
	case Gameover::en_cameraEasing:
		
		cameraToEnemyVec = m_attackEnemy->GetPosition() 
			- g_camera3D->GetPosition();
			 

		cameraToEnemyVec.Normalize();

		cameraToEnemyVec.x *= 50.0f;
		cameraToEnemyVec.z *= 50.0f;
		cameraToEnemyVec.y = 10.0f;

		targetPos = cameraToEnemyVec + g_camera3D->GetPosition();

		g_camera3D->SetTarget(targetPos);

		if (m_attackEnemy->GetAttackImpact() == true)
		{
			m_load->LoadExecutionFadeOut({ Load::en_loadImmediately,Load::en_loadOrdinary });

			m_gameoverState = GameoverState::en_enemyAnimation;
		}

		break;
	case Gameover::en_enemyAnimation:

		if (m_attackEnemy->GetAnimationEnd() == true)
		{
			SetKillEndFlag(true);

			m_gameoverState = GameoverState::en_gameoverDraw;
		}

		break;
	case Gameover::en_gameoverDraw:

	

	default:
		break;
	}
}

//レンダー関数
void Gameover::Render(RenderContext& rc)
{

}