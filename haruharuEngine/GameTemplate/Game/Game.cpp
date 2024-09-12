#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"

bool Game::Start()
{
	m_modelPlayer.Init("Assets/modelData/unityChan.tkm");

	m_modelBackGround.Init("Assets/modelData/testMap/Map7.tkm",nullptr,0,enModelUpAxisZ,true);
	m_modelFloor.SetShadowChasterFlag(false);

	m_modelFloor.Init("Assets/modelData/testMap/Map_floor.tkm",nullptr,0,enModelUpAxisZ,true);
	m_modelFloor.SetShadowChasterFlag(false);

	m_spriteTest1.Init("Assets/modelData/Enemy_UI_A.DDS", 1280.0f, 720.0f);

	Vector3 testpos = { 0.0f,130.0f,0.0f };

	m_spriteTest1.SetPosition(testpos);
	
	m_modelPlayer.SetPosition(m_modelTestPos);

	m_modelBackGround.SetPosition(Vector3::Zero);

	m_modelFloor.SetPosition(Vector3::Zero);

	m_testCamera = NewGO<GameCamera>(0, "camera");

	return true;
}

void Game::Update()
{

	m_modelTestPos = Vector3::Zero;

	m_modelPlayer.Update();

	m_modelBackGround.Update();

	m_modelFloor.Update();

	m_testSpotLight.SetPosition(m_spotLightTestPos);

	m_testSpotLight.SetColor(10.0f, 10.0f, 10.0f);

	m_spotLightTestDirection.Normalize();

	m_testSpotLight.SetDirection(m_spotLightTestDirection);

	m_testSpotLight.SetRange(300.0f);

	m_testSpotLight.SetAngle(25.0f);

	m_testPointLight.SetAffectPowParam(0.5f);

	m_spriteTest1.Update();
}

void Game::Render(RenderContext& rc)
{

	m_modelPlayer.Draw(rc);

	m_modelBackGround.Draw(rc);

	m_modelFloor.Draw(rc);

	//m_spriteTest1.Draw(rc);
}