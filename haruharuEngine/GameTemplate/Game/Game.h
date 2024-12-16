#pragma once
#include "PatrolRuteDataHolder.h"

class GameCamera;
class BackGroundWalls;
class BackGroundFloor;
class BackGroundCeiling;
class Player;
class Enemy_Warrior;
class CrystalGetCommandSprite;
class EnemyAIMetaWarrior;
class DebugEnemyTrackingState;
class ManagerCrystal;
class PlayerScanCrystalUi;
class PlayerScoreUi;
class PlayerStaminaUi;
class PlayerOxygenUi;
class Load;

//定数等
namespace {

	static const float MAX_GAMETIME = 300.0f;

}

class Game : public IGameObject
{
public:

	void PlauerGameClear()
	{
		m_gameInState = GameInState::en_gameClear;
	}

	void PlayerGameOver()
	{
		m_gameInState = GameInState::en_gameOver;
	}

private:

	enum GameOutState
	{
		en_gameTitle,

		en_gameLoad,

		en_gameOutEnd,
	};
	GameOutState m_gameOutState = GameOutState::en_gameTitle;
	enum GameInState
	{
		en_gameUpdate,

		en_gameClear,

		en_gameOver,

		
	};
	GameInState m_gameInState = GameInState::en_gameUpdate;
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ディレクションライト作成
	/// </summary>
	void InitDirctionaLight();
	/// <summary>
	/// クリスタルを初期化
	/// </summary>
	void InitObjectCrystal();
	/// <summary>
	/// インゲーム
	/// </summary>
	void DoInGame();
	/// <summary>
	/// タイマー処理
	/// </summary>
	void TimerProcess();
	/// <summary>
	/// アウトゲーム
	/// </summary>
	void DoOutGame();
	/// <summary>
	/// アウトゲームのロード処理
	/// </summary>
	void OutGameLoadProcess();
	/// <summary>
	/// レベルレンダー
	/// </summary>
	LevelRender m_levelRender;
	/// <summary>
	/// エネミーウォリアーのメタAI
	/// </summary>
	EnemyAIMetaWarrior* m_warriorMetaAI;
	/// <summary>
	/// カメラ
	/// </summary>
	GameCamera* m_mainCamera = nullptr;
	/// <summary>
	/// 太陽光
	/// </summary>
	DirectionalLight sunDirectionalLight;
	/// <summary>
	/// プレイヤー
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// クリスタルコマンドスプライト
	/// </summary>
	CrystalGetCommandSprite* m_GetCOMSprite = nullptr;
	/// <summary>
	/// クリスタルマネージャー
	/// </summary>
	ManagerCrystal* m_managerCrystal;
	/// <summary>
	/// プレイヤーのスキャンUI
	/// </summary>
	PlayerScanCrystalUi* m_scanUi = nullptr;
	/// <summary>
	/// プレイヤーのスコアUI
	/// </summary>
	PlayerScoreUi* m_scoreUi = nullptr;
	/// <summary>
	/// プレイヤーのスタミナUI
	/// </summary>
	PlayerStaminaUi* m_staminaUi = nullptr;
	/// <summary>
	/// プレイヤーの酸素UI
	/// </summary>
	PlayerOxygenUi* m_oxygenUi = nullptr;
	/// <summary>
	/// スコア
	/// </summary>
	float m_scoreNum = 0.0; 
	/// <summary>
	/// タイマー
	/// </summary>
	float m_timerIndex = 0.0f;

	Load* m_load = nullptr;
};

