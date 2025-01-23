#pragma once
#include "EnemyBase.h"
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class GameSound;
class Player;

class Enemy_Warrior : public EnemyBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy_Warrior();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	~Enemy_Warrior();
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アニメーションイベント
	/// </summary>
	/// <param name="clipName"></param>
	/// <param name="eventName"></param>
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ドロー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// AIListの初期化
	/// </summary>
	void InitAIList();
	/// <summary>
	/// AIList内のプログラムのアップデート
	/// </summary>
	void AIListUpdate();
private:
	/// <summary>
	/// コリジョンオブジェクト
	/// </summary>
	CollisionObject* m_collisionObject;	

	//test
	Player* m_player = nullptr;
	/// <summary>
	/// ゲームサウンド
	/// </summary>
	GameSound* m_gameSound = nullptr;
};

