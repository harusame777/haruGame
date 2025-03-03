#pragma once
#include "PlayerUIBase.h"

class Elevator;

class PlayerPointerUi : public PlayerUIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerPointerUi() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerPointerUi() {};
	/// <summary>
	/// 描画できるか設定
	/// </summary>
	/// <param name="setDraw"></param>
	void SetPointerDraw(bool setDraw)
	{
		m_isPointerDraw = setDraw;
	}
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
	/// ポインタの位置更新
	/// </summary>
	void PointerPositionUpdate();
	/// <summary>
	/// スプライトの更新
	/// </summary>
	void SpriteUpdate();
	/// <summary>
	/// カメラ内にスプライトがあるか調べる
	/// </summary>
	/// <returns></returns>
	bool IsSpriteInCamera();
	/// <summary>
	/// ドロー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ポインタ
	/// </summary>
	SpriteRender m_pointer;
	/// <summary>
	/// フォントレンダー
	/// </summary>
	FontRender m_font;
	/// <summary>
	/// ポインタ
	/// </summary>
	bool m_isPointerDraw = false;
	/// <summary>
	/// スプライトの位置
	/// </summary>
	Vector2 m_spritePosition;
	/// <summary>
	/// エレベーターのインスタンス
	/// </summary>
	Elevator* m_elevator = nullptr;
};

