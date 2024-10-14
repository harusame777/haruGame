#pragma once
#include "EnemyBase.h"
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

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
	/// モデル
	/// </summary>
	ModelRender m_modelRender;
	/// <summary>
	/// コリジョンオブジェクト
	/// </summary>
	CollisionObject* m_collisionObject;	
	//test
	Player* m_player = nullptr;


};

