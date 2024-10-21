#pragma once
#include "ObjectBase.h"

class Player;

class Crystal : public ObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Crystal();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Crystal();
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// クリスタル取得関数
	/// </summary>
	void GetCrystal();
	/// <summary>
	/// レイテストを行って壁がないかどうかを調べる関数
	/// </summary>
	/// <returns></returns>
	bool RayTestWall();
	/// <summary>
	/// レンダー関数
	/// </summary>
	void Render(RenderContext& rc);
	/// <summary>
	/// このオブジェクトが取得されているかどうか
	/// </summary>
	bool m_isGetObject = false;
	/// <summary>
	/// コライダー
	/// </summary>
	SphereCollider m_sphereCollider;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	Player* m_player = nullptr;
};

