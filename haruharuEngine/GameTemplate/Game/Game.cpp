#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "BackGroundWalls.h"
#include "BackGroundFloor.h"
#include "BackGroundCeiling.h"
#include "Crystal.h"
#include "CrystalGetCommandSprite.h"
#include "Player.h"
#include "EnemyAIMetaWarrior.h"
#include "Enemy_Warrior.h"
#include "DebugEnemyTrackingState.h"
#include "Locker.h"
#include "Elevator.h"
#include "Accessories.h"
#include "ManagerCrystal.h"
#include "PlayerScanCrystalUi.h"
#include "PlayerScoreUi.h"
#include "PlayerStaminaUi.h"
#include "PlayerOxygenUi.h"
#include "Load.h"



bool Game::Start()
{
	InitDirctionaLight();


	//エネミーウォリアーのメタAI
	m_warriorMetaAI = NewGO<EnemyAIMetaWarrior>(0, "MetaAI");

	InitObjectCrystal();

	//レベルレンダーのテスト
	m_levelRender.Init("Assets/mapLevel/testLevel6.tkl", [&](LevelObjectData_Render& objData)
	{
		if (objData.ForwardMatchName(L"laboWall_1-4Model") == true)
		{
			BackGroundWalls* walls = NewGO<BackGroundWalls>(0, "background");
			walls->SetWallType(BackGroundWalls::en_wallType1_4);
			walls->SetPosition(objData.m_position);
			walls->SetRotation(objData.m_rotation);
			walls->SetScale(objData.m_scalse);
			return true;
		}
		else if(objData.ForwardMatchName(L"laboWall_2-4Model") == true)
		{
			BackGroundWalls* walls = NewGO<BackGroundWalls>(0, "background");
			walls->SetWallType(BackGroundWalls::en_wallType2_4);
			walls->SetPosition(objData.m_position);
			walls->SetRotation(objData.m_rotation);
			walls->SetScale(objData.m_scalse);
			return true;
		}
		else if (objData.ForwardMatchName(L"laboWall_4-4Model") == true)
		{
			BackGroundWalls* walls = NewGO<BackGroundWalls>(0, "background");
			walls->SetWallType(BackGroundWalls::en_wallType4_4);
			walls->SetPosition(objData.m_position);
			walls->SetRotation(objData.m_rotation);
			walls->SetScale(objData.m_scalse);
			return true;
		}
		else if (objData.ForwardMatchName(L"laboWall_4-6Model") == true)
		{
			BackGroundWalls* walls = NewGO<BackGroundWalls>(0, "background");
			walls->SetWallType(BackGroundWalls::en_wallType4_6);
			walls->SetPosition(objData.m_position);
			walls->SetRotation(objData.m_rotation);
			walls->SetScale(objData.m_scalse);
			return true;
		}
		else if (objData.ForwardMatchName(L"laboDoorWay_4-4Model") == true)
		{
			BackGroundWalls* walls = NewGO<BackGroundWalls>(0, "background");
			walls->SetWallType(BackGroundWalls::en_wallTypeDoorWay4_4);
			walls->SetPosition(objData.m_position);
			walls->SetRotation(objData.m_rotation);
			walls->SetScale(objData.m_scalse);
			return true;
		}
		else if(objData.ForwardMatchName(L"laboFloor_MainModel") == true)
		{
			BackGroundFloor* floor = NewGO<BackGroundFloor>(0, "background");
			floor->SetPosition(objData.m_position);
			floor->SetRotation(objData.m_rotation);
			floor->SetScale(objData.m_scalse);
			return true;
		}
		else if (objData.ForwardMatchName(L"laboCeiling_MainModel") == true)
		{
			BackGroundCeiling* ceiling = NewGO<BackGroundCeiling>(0, "background");
			ceiling->SetPosition(objData.m_position);
			ceiling->SetRotation(objData.m_rotation);
			ceiling->SetScale(objData.m_scalse);
		}
		else if (objData.ForwardMatchName(L"youtai") == true)
		{
			Enemy_Warrior* enemy_warrior = NewGO<Enemy_Warrior>(0, "enemy");
			enemy_warrior->SetPosition(objData.m_position);
			enemy_warrior->SetRotation(objData.m_rotation);
			enemy_warrior->SetScale(objData.m_scalse);
			return true;
		}
		else if (objData.ForwardMatchName(L"locker") == true)
		{
			Locker* locker = NewGO<Locker>(0, "object");
			locker->SetPosition(objData.m_position);
			return true;
		}
		else if (objData.ForwardMatchName(L"elevator") == true)
		{
			Elevator* elevator = NewGO<Elevator>(0, "object");
			elevator->SetPosition(objData.m_position);
			return true;
		}
		else if (objData.ForwardMatchName(L"desk") == true)
		{
			Accessories* desk = NewGO<Accessories>(0, "object");
			desk->SetPosition(objData.m_position);
			desk->SetRotation(objData.m_rotation);
			return true;
		}
		return true;
	});

	m_player = NewGO<Player>(0, "player");
	//UIの初期化
	m_scanUi = NewGO<PlayerScanCrystalUi>(0, "ScanUI");
	m_scoreUi = NewGO<PlayerScoreUi>(0, "ScoreUI");
	m_scoreUi->InitMainScorePtr(m_scoreNum);
	m_staminaUi = NewGO<PlayerStaminaUi>(0, "StaminaUI");
	m_oxygenUi = NewGO<PlayerOxygenUi>(0, "OxygenUI");
	m_oxygenUi->InitTimerPtr(&m_timerIndex);

	m_timerIndex = MAX_GAMETIME;

	m_mainCamera = NewGO<GameCamera>(0, "camera");

	//m_load = NewGO<Load>(0, "Load");

	return true;
}

void Game::InitDirctionaLight()
{
	sunDirectionalLight.SetColor(1.0f, 1.0f, 1.0f);
	sunDirectionalLight.SetDirection(1.0f, -1.0f, -1.0f);
	sunDirectionalLight.LightDirectionNormalize();
	sunDirectionalLight.CastShadow();
}

void Game::InitObjectCrystal()
{
	m_GetCOMSprite = NewGO<CrystalGetCommandSprite>(0, "object");

	////クリスタルのメタAI
	m_managerCrystal = NewGO<ManagerCrystal>(0, "CrystalMetaAI");
}

void Game::Update()
{

	if (m_gameOutState != GameOutState::en_gameOutEnd)
	{
		DoOutGame();
	}
	else
	{
		DoInGame();
	}
}

void Game::DoInGame()
{

	switch (m_gameInState)
	{
	case Game::en_gameUpdate:

		TimerProcess();

		break;
	case Game::en_gameClear:
		break;
	case Game::en_gameOver:
		break;
	default:
		break;
	}

}

void Game::TimerProcess()
{

	m_timerIndex -= g_gameTime->GetFrameDeltaTime();

	if (m_timerIndex <= 0)
	{

		m_gameInState = GameInState::en_gameOver;

	}

}

void Game::DoOutGame()
{

	switch (m_gameOutState)
	{
	case Game::en_gameTitle:

		m_gameOutState = GameOutState::en_gameLoad;

		break;
	case Game::en_gameLoad:

		OutGameLoadProcess();

		m_gameOutState = GameOutState::en_gameOutEnd;

		break;
	case Game::en_gameOutEnd:
		break;
	default:
		break;
	}

}

void Game::OutGameLoadProcess()
{



}