#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "BackGroundWalls.h"
#include "Player.h"
#include "Enemy_Warrior.h"

bool Game::Start()
{
	sunDirectionalLight.SetColor(1.0f, 1.0f, 1.0f);
	sunDirectionalLight.SetDirection(1.0f, -1.0f, -1.0f);
	sunDirectionalLight.LightDirectionNormalize();
	sunDirectionalLight.CastShadow();

	//レベルレンダーのテスト
	//m_levelRender.Init("Assets/mapLevel/testLevel1.tkl", [&](LevelObjectData_Render& objData)
	//{
	//	if (objData.ForwardMatchName(L"laboWall_1-4Model") == true)
	//	{
	//		BackGroundWalls* walls = NewGO<BackGroundWalls>(0, "background");
	//		walls->SetWallType(BackGroundWalls::en_wallType1_4);
	//		walls->SetPosition(objData.m_position);
	//		walls->SetRotation(objData.m_rotation);
	//		walls->SetScale(objData.m_scalse);
	//		return true;
	//	}
	//	else if(objData.ForwardMatchName(L"laboWall_2-4Model") == true)
	//	{
	//		BackGroundWalls* walls = NewGO<BackGroundWalls>(0, "background");
	//		walls->SetWallType(BackGroundWalls::en_wallType2_4);
	//		walls->SetPosition(objData.m_position);
	//		walls->SetRotation(objData.m_rotation);
	//		walls->SetScale(objData.m_scalse);
	//		return true;
	//	}
	//	else if (objData.ForwardMatchName(L"laboWall_4-4Model") == true)
	//	{
	//		BackGroundWalls* walls = NewGO<BackGroundWalls>(0, "background");
	//		walls->SetWallType(BackGroundWalls::en_wallType4_4);
	//		walls->SetPosition(objData.m_position);
	//		walls->SetRotation(objData.m_rotation);
	//		walls->SetScale(objData.m_scalse);
	//		return true;
	//	}
	//	else if (objData.ForwardMatchName(L"laboWall_4-6Model") == true)
	//	{
	//		BackGroundWalls* walls = NewGO<BackGroundWalls>(0, "background");
	//		walls->SetWallType(BackGroundWalls::en_wallType4_6);
	//		walls->SetPosition(objData.m_position);
	//		walls->SetRotation(objData.m_rotation);
	//		walls->SetScale(objData.m_scalse);
	//		return true;
	//	}
	//	return true;
	//});

	m_bgModelRendedr.Init("Assets/modelData/bg/bg.tkm");
	m_bgObject.CreateFromModel(m_bgModelRendedr.GetModel(), m_bgModelRendedr.GetModel().GetWorldMatrix());

	m_player = NewGO<Player>(0, "player");

	m_testEnemy = NewGO<Enemy_Warrior>(0, "enemy");

	m_modelFloor.Init("Assets/modelData/testMap/Map_floor.tkm",nullptr,0,enModelUpAxisZ,true);
	m_modelFloor.SetShadowChasterFlag(false);

	m_spriteTest1.Init("Assets/modelData/Enemy_UI_A.DDS", 1280.0f, 720.0f);

	Vector3 testpos = { 0.0f,130.0f,0.0f };

	m_spriteTest1.SetPosition(testpos);
	
	m_modelFloor.SetPosition(Vector3::Zero);

	m_testCamera = NewGO<GameCamera>(0, "camera");

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

void Game::Update()
{

	m_modelTestPos = Vector3::Zero;

	m_modelFloor.Update();

	m_testSpotLight.SetPosition(m_spotLightTestPos);

	m_testSpotLight.SetColor(10.0f, 10.0f, 10.0f);

	m_spotLightTestDirection.Normalize();

	Vector3 targetPos = m_modelTestPos;

	targetPos.y += 50.0f;

	Vector3 diff = targetPos - m_spotLightTestPos;

	diff.Normalize();

	m_testSpotLight.SetDirection(diff);

	m_testSpotLight.SetRange(300.0f);

	m_testSpotLight.SetAngle(25.0f);

	m_testPointLight.SetAffectPowParam(0.5f);

	m_spriteTest1.Update();
}

void Game::Render(RenderContext& rc)
{
	m_bgModelRendedr.Draw(rc);

	//m_modelFloor.Draw(rc);

	//m_spriteTest1.Draw(rc);
}