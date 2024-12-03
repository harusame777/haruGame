#pragma once
#include "PatrolRuteDataHolder.h"

class GameCamera;
class BackGroundWalls;
class BackGroundFloor;
class Player;
class Enemy_Warrior;
class CrystalGetCommandSprite;
class EnemyAIMetaWarrior;
class DebugEnemyTrackingState;
class ManagerCrystal;
class PlayerScanCrystalUi;

class Game : public IGameObject
{
public:

	bool Start();

	void Update();

	//テスト用座標

	Vector3 m_modelTestPos = Vector3::Zero;

	Vector3 m_pointLightTestPos = { 0.0f,20.0f,0.0f };

	Vector3 m_spotLightTestPos = { 0.0f,80.0f,150.0f };

	Vector3 m_spotLightTestDirection = { 1.0f,-1.0f,1.0f };

	LevelRender m_levelRender;

	//エネミーウォリアーのメタAI
	EnemyAIMetaWarrior* m_warriorMetaAI;
	
	//テストカメラ
	GameCamera* m_testCamera = nullptr;

	ModelRender m_modelFloor;

	SpriteRender m_spriteTest1;

	//太陽光の作成
	DirectionalLight sunDirectionalLight;


	Player* m_player = nullptr;

	Enemy_Warrior* m_testEnemy = nullptr;

	CrystalGetCommandSprite* m_GetCOMSprite = nullptr;

	ManagerCrystal* m_managerCrystal;

	ModelRender m_bgModelRendedr;
	PhysicsStaticObject m_bgObject;


	FontRender m_testFont;

	/// <summary>
	/// プレイヤーのスキャンUI
	/// </summary>
	PlayerScanCrystalUi* m_scanUi = nullptr;
};

