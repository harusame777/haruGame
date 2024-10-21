#pragma once
#include "ObjectBase.h"

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
	/// オブジェクト取得関数
	/// </summary>
	void GetObject();
	/// <summary>
	/// レンダー関数
	/// </summary>
	void Render(RenderContext& rc);
	/// <summary>
	/// このオブジェクトが取得されているかどうか
	/// </summary>
	bool m_isGetObject = false;
};

