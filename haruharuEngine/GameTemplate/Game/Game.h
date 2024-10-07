#pragma once

class GameCamera;
class BackGroundWalls;
class Player;
class Enemy_Warrior;

class Game : public IGameObject
{
public:

	bool Start();

	void Update();

	void Render(RenderContext& rc);

	//�e�X�g�p���W

	Vector3 m_modelTestPos = Vector3::Zero;

	Vector3 m_pointLightTestPos = { 0.0f,20.0f,0.0f };

	Vector3 m_spotLightTestPos = { 0.0f,80.0f,150.0f };

	Vector3 m_spotLightTestDirection = { 1.0f,-1.0f,1.0f };

	LevelRender m_levelRender;
	
	//�e�X�g�J����
	GameCamera* m_testCamera = nullptr;

	ModelRender m_modelFloor;

	SpriteRender m_spriteTest1;

	PointLight m_testPointLight;

	//���z���̍쐬
	DirectionalLight sunDirectionalLight;

	SpotLight m_testSpotLight;

	Player* m_player = nullptr;

	Enemy_Warrior* m_testEnemy = nullptr;

	ModelRender m_bgModelRendedr;
	PhysicsStaticObject m_bgObject;
};

