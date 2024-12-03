#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "BackGroundWalls.h"
#include "BackGroundFloor.h"
#include "Crystal.h"
#include "CrystalGetCommandSprite.h"
#include "Player.h"
#include "EnemyAIMetaWarrior.h"
#include "Enemy_Warrior.h"
#include "DebugEnemyTrackingState.h"
#include "Locker.h"
#include "Accessories.h"
#include "ManagerCrystal.h"
#include "PlayerScanCrystalUi.h"



bool Game::Start()
{
	sunDirectionalLight.SetColor(1.0f, 1.0f, 1.0f);
	sunDirectionalLight.SetDirection(1.0f, -1.0f, -1.0f);
	sunDirectionalLight.LightDirectionNormalize();
	sunDirectionalLight.CastShadow();

	m_GetCOMSprite = NewGO<CrystalGetCommandSprite>(0, "object");

	//エネミーウォリアーのメタAI
	m_warriorMetaAI = NewGO<EnemyAIMetaWarrior>(0, "MetaAI");

	////クリスタルのメタAI
	m_managerCrystal = NewGO<ManagerCrystal>(0, "CrystalMetaAI");

	//レベルレンダーのテスト
	m_levelRender.Init("Assets/mapLevel/testLevel5.tkl", [&](LevelObjectData_Render& objData)
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
		//else if (objData.ForwardMatchName(L"crystal01_Model") == true)
		//{
		//	Crystal* crystal = NewGO<Crystal>(0, "object");
		//	crystal->SetPosition(objData.m_position);
		//	crystal->SetRotation(objData.m_rotation);
		//	crystal->SetScale(objData.m_scalse);
		//	return true;
		//}
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
		else if (objData.ForwardMatchName(L"desk") == true)
		{
			Accessories* desk = NewGO<Accessories>(0, "object");
			desk->SetPosition(objData.m_position);
			desk->SetRotation(objData.m_rotation);
			return true;
		}
		return true;
	});

	m_bgModelRendedr.Init("Assets/modelData/bg/bg.tkm");
	//m_bgObject.CreateFromModel(m_bgModelRendedr.GetModel(), m_bgModelRendedr.GetModel().GetWorldMatrix());

	m_player = NewGO<Player>(0, "player");
	//UIの初期化
	m_scanUi = NewGO<PlayerScanCrystalUi>(0, "UI");

	m_modelFloor.Init("Assets/modelData/testMap/Map_floor.tkm",nullptr,0,enModelUpAxisZ,true);
	m_modelFloor.SetShadowChasterFlag(false);

	m_spriteTest1.Init("Assets/modelData/Enemy_UI_A.DDS", 1280.0f, 720.0f);

	Vector3 testpos = { 0.0f,130.0f,0.0f };

	m_spriteTest1.SetPosition(testpos);
	
	m_modelFloor.SetPosition(Vector3::Zero);

	m_testCamera = NewGO<GameCamera>(0, "camera");

	
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

void Game::Update()
{

	m_modelTestPos = Vector3::Zero;

	m_modelFloor.Update();

	Vector3 targetPos = m_modelTestPos;

	targetPos.y += 50.0f;

	Vector3 diff = targetPos - m_spotLightTestPos;

	diff.Normalize();

	m_spriteTest1.Update();

	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"test");

	m_testFont.SetText(wcsbuf);
}