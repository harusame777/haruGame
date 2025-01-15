#include "stdafx.h"
#include "Gameover.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"
#include "Load.h"
#include "GameSound.h"

//定数等
namespace {
	static const float BACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float BACKSIDE_SPRITE_H_SIZE = 900.0f;

	static const Vector3 GAMEOVERFONT_POSITION = { -500.0f,200.0f,0.0f };
	static const Vector3 MAIN_FONT_POSITION = { -150.0f,-100.0f,0.0f };
	static const Vector3 SUB_FONT_POSITION = { -50.0f,-150.0f,0.0f };

	static const Vector4 FONT_COLOR = { 1.0f,0.0f,0.0f,1.0f };
}

//スタート関数
bool Gameover::Start()
{
	m_backSideSprite.Init("Assets/modelData/title/back_side_1.DDS",
		BACKSIDE_SPRITE_W_SIZE,
		BACKSIDE_SPRITE_H_SIZE);

	m_load = FindGO<Load>("load");

	m_gameSound = FindGO<GameSound>("gameSound");

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
			SetFadeOutFlag(true);

			m_gameoverState = GameoverState::en_enemyAnimation;
		}

		break;
	case Gameover::en_enemyAnimation:

		if (m_attackEnemy->GetAnimationEnd() == true)
		{
			SetKillEndFlag(true);

			BackSideSpriteDraw(true);

			m_gameoverState = GameoverState::en_gameoverDraw;
		}

		break;
	case Gameover::en_gameoverDraw:

		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_gameSound->LocalSoundOrder(GameSound::en_decisionSound, false, 0.5f);

			m_gameoverState = Gameover::en_gameoverEnd;
		}

		break;
	case Gameover::en_gameoverEnd:
		break;
	default:
		break;
	}
}

//レンダー関数
void Gameover::Render(RenderContext& rc)
{
	if (m_backSideSpriteDrawFlag == true)
	{
		m_backSideSprite.Draw(rc);

		//メインフォント
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"Continue?");

		m_mainFont.SetColor(FONT_COLOR);

		m_mainFont.SetPivot({ 0.5f,0.5f });

		m_mainFont.SetPosition(MAIN_FONT_POSITION);

		m_mainFont.SetText(wcsbuf);
		//サブフォント
		swprintf_s(wcsbuf, 256, L"push B");

		m_subFont.SetColor(FONT_COLOR);

		m_subFont.SetPivot({ 0.5f,0.5f });

		m_subFont.SetPosition(SUB_FONT_POSITION);

		m_subFont.SetScale(0.5f);

		m_subFont.SetText(wcsbuf);

		swprintf_s(wcsbuf, 256, L"GAME_OVER");

		m_gameoverFont.SetColor(FONT_COLOR);

		m_gameoverFont.SetPivot({ 0.5f,0.5f });

		m_gameoverFont.SetPosition(GAMEOVERFONT_POSITION);

		m_gameoverFont.SetScale(3.0f);

		m_gameoverFont.SetText(wcsbuf);

		m_mainFont.Draw(rc);

		m_subFont.Draw(rc);

		m_gameoverFont.Draw(rc);
	}
}