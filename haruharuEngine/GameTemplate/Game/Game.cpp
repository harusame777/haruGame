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
#include "Title.h"
#include "Result.h"
#include "Gameover.h"
#include "Window.h"
#include "GameSound.h"


bool Game::Start()
{
	InitDirctionaLight();

	m_gameSound = NewGO<GameSound>(2, "gameSound");

	m_load = NewGO<Load>(1, "load");

	m_load->LoadExecutionFadeOut({ Load::en_loadImmediately,Load::en_loadImmediately });

	return true;
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
		m_load->LoadExecutionFadeOut({ Load::en_loadOrdinary,Load::en_loadOrdinary });

		if (m_load->IsLoadBlackout())
		{
			OutGameObjectDeleteProcces();

			m_result = NewGO<Result>(0, "result");

			m_result->SetFinalScore(m_scoreNum);

			m_load->LoadExecutionFadeIn();

			m_gameInState = GameInState::en_gameResult;
		}
		break;
	case Game::en_gameOver:

		if (m_gameover == nullptr)
		{
			m_gameover = NewGO<Gameover>(0, "gameover");
		}

		if (m_gameover->GetFadeOutFlag() == true)
		{
			m_load->LoadExecutionFadeOut({ Load::en_loadImmediately,Load::en_loadOrdinary });

			m_gameInState = GameInState::en_gameResultGameOver;
		}

		break;
	case Game::en_gameResultGameOver:

		if (m_gameover->GetKillEndFlag() == true &&
			m_load->IsLoadBlackout())
		{
			OutGameObjectDeleteProcces();

			m_load->LoadExecutionFadeIn();
		}

		if (m_load->IsLoadCompletion() == true &&
			m_gameover->GetGameoverEnd() == true)
		{
			m_load->LoadExecutionFadeOut({ Load::en_loadOrdinary, Load::en_loadOrdinary });

			m_gameOutState = GameOutState::en_gameTitle;
		}

		break;
	case Game::en_gameResult:

		if (m_result->IsResultEnd())
		{
			m_load->LoadExecutionFadeOut({ Load::en_loadOrdinary, Load::en_loadOrdinary });

			m_gameOutState = GameOutState::en_gameTitle;
		}

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

		if (m_load->IsLoadBlackout())
		{
			m_load->LoadExecutionFadeIn();

			if (m_result != nullptr)
			{
				DeleteGO(m_result);
			}

			if (m_gameover != nullptr)
			{
				DeleteGO(m_gameover);
			}

			m_result = nullptr;

			m_gameover = nullptr;

			m_title = NewGO<Title>(0, "title");
		}

		if (m_title != nullptr && 
			m_title->IsEndGameTitle() &&
			m_load->IsLoadCompletion())
		{
			m_gameSound->LocalSoundOrder(GameSound::en_decisionSound, false, 1.0f);

			m_load->LoadExecutionFadeOut({ Load::en_loadOrdinary,Load::en_loadCircular });

			m_gameOutState = GameOutState::en_gameLoad;

			m_gameInState = GameInState::en_gameUpdate;
		}

		break;
	case Game::en_gameLoad:
		
		if (m_isGameMainObjectLoadEnd == false && m_load->IsLoadBlackout())
		{
			OutGameLoadProcess();
		}

		if (m_load->IsLoadBlackout())
		{
			DeleteGO(m_title);

			m_title = nullptr;

			m_gameOutState = GameOutState::en_gameOutEnd;

			m_load->LoadExecutionFadeIn();
		}

		break;
	case Game::en_gameOutEnd:

		break;
	default:
		break;
	}

}

void Game::OutGameLoadProcess()
{
	//エネミーウォリアーのメタAI
	m_warriorMetaAI = NewGO<EnemyAIMetaWarrior>(0, "MetaAI");

	m_GetCOMSprite = NewGO<CrystalGetCommandSprite>(0, "comSprite");

	////クリスタルのメタAI
	m_managerCrystal = NewGO<ManagerCrystal>(0, "CrystalMetaAI");

	LevelRender levelRender;

	//レベルレンダーのテスト
	levelRender.Init("Assets/mapLevel/testLevel6.tkl", [&](LevelObjectData_Render& objData)
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
			else if (objData.ForwardMatchName(L"laboWall_2-4Model") == true)
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
			else if (objData.ForwardMatchName(L"laboFloor_MainModel") == true)
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
			//else if (objData.ForwardMatchName(L"locker") == true)
			//{
			//	Locker* locker = NewGO<Locker>(0, "object");
			//	locker->SetPosition(objData.m_position);
			//	return true;
			//}
			else if (objData.ForwardMatchName(L"elevator") == true)
			{
				Elevator* elevator = NewGO<Elevator>(0, "object");
				elevator->SetPosition(objData.m_position);
				return true;
			}
			//else if (objData.ForwardMatchName(L"desk") == true)
			//{
			//	Accessories* desk = NewGO<Accessories>(0, "object");
			//	desk->SetPosition(objData.m_position);
			//	desk->SetRotation(objData.m_rotation);
			//	return true;
			//}
			return true;
		});

	m_player = NewGO<Player>(0, "player");
	//UIの初期化
	PlayerScanCrystalUi* m_scanUi = NewGO<PlayerScanCrystalUi>(0, "ScanUI");
	PlayerScoreUi* m_scoreUi = NewGO<PlayerScoreUi>(0, "ScoreUI");
	m_scoreUi->InitMainScorePtr(m_scoreNum);
	PlayerStaminaUi* m_staminaUi = NewGO<PlayerStaminaUi>(0, "StaminaUI");
	PlayerOxygenUi* m_oxygenUi = NewGO<PlayerOxygenUi>(0, "OxygenUI");
	m_oxygenUi->InitTimerPtr(&m_timerIndex);

	m_timerIndex = MAX_GAMETIME;

	m_mainCamera = NewGO<GameCamera>(0, "camera");

	m_isGameMainObjectLoadEnd = true;
}

void Game::InitDirctionaLight()
{
	sunDirectionalLight.SetColor(1.0f, 1.0f, 1.0f);
	sunDirectionalLight.SetDirection(1.0f, -1.0f, -1.0f);
	sunDirectionalLight.LightDirectionNormalize();
	sunDirectionalLight.CastShadow();
}

//QueryGOs<IEnemy>("summonenemy", [&](IEnemy* ienemy) {
//	DeleteGO(ienemy);
//	return true;
//	});

void Game::OutGameObjectDeleteProcces()
{
	//壁消去
	QueryGOs<BackGroundWalls>("background", [&](BackGroundWalls* backGround) {
			DeleteGO(backGround);
			return true;
		});
	//床消去
	QueryGOs<BackGroundFloor>("background", [&](BackGroundFloor* backGround) {
		DeleteGO(backGround);
		return true;
		});
	//天井
	QueryGOs<BackGroundCeiling>("background", [&](BackGroundCeiling* backGround) {
		DeleteGO(backGround);
		return true;
		});

	QueryGOs<Elevator>("elevator", [&](Elevator* object) {
		DeleteGO(object);
		return true;
		});

	DeleteGO(m_warriorMetaAI);

	QueryGOs<Enemy_Warrior>("enemy", [&](Enemy_Warrior* UI) {
		DeleteGO(UI);
		return true;
		});

	QueryGOs<PlayerScanCrystalUi>("ScanUI", [&](PlayerScanCrystalUi* UI) {
		DeleteGO(UI);
		return true;
		});

	QueryGOs<PlayerScoreUi>("ScoreUI", [&](PlayerScoreUi* UI) {
		DeleteGO(UI);
		return true;
		});

	QueryGOs<PlayerStaminaUi>("StaminaUI", [&](PlayerStaminaUi* UI) {
		DeleteGO(UI);
		return true;
		});

	QueryGOs<PlayerOxygenUi>("OxygenUI", [&](PlayerOxygenUi* UI) {
		DeleteGO(UI);
		return true;
		});

	
	DeleteGO(m_managerCrystal);

	QueryGOs<Crystal>("object", [&](Crystal* object) {
		DeleteGO(object);
		return true;
		});

	DeleteGO(m_GetCOMSprite);

	DeleteGO(m_player);

	DeleteGO(m_mainCamera);

	m_isGameMainObjectLoadEnd = false;
}