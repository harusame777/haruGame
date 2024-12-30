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
	enum EnAnimationClip
	{
		en_idle,
		en_tracking,
		en_patrol,
		en_animationNum,
	};

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
	/// <summary>
	/// デバックディスプレイ文字設定
	/// </summary>
	void DebugStateDisplay(int setnum)
	{
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"NowState[%01d]", int(setnum));

		m_debugStateDisplayRender.SetText(wcsbuf);
	}
private:
	/// <summary>
	/// モデル
	/// </summary>
	ModelRender m_modelRender;
	/// <summary>
	/// コリジョンオブジェクト
	/// </summary>
	CollisionObject* m_collisionObject;	
	/// <summary>
	/// アニメーションクリップ
	/// </summary>
	AnimationClip m_animationClip[en_animationNum];
	//test
	Player* m_player = nullptr;
};

