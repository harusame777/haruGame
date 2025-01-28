#pragma once
#include "PlayerUIBase.h"

class PlayerInteractableUi : public PlayerUIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerInteractableUi(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerInteractableUi(){}
	/// <summary>
	/// インタラクト可能スプライト描画フラグ設定
	/// </summary>
	/// <param name="drawFlag"></param>
	void SetInteractableDrawFlag(const bool& drawFlag)
	{
		if (m_interactableDarwFlag == true)
		{
			return;
		}

		m_interactableDarwFlag = drawFlag;
	}
	/// <summary>
	/// インタラクト可能スプライト描画フラグ取得
	/// </summary>
	/// <returns></returns>
	const bool& GetInteractableDrawFlag() const
	{
		return m_interactableDarwFlag;
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
	/// レンダー関数
	/// </summary>
	void Render(RenderContext& rc);
	/// <summary>
	/// インタラクト可能スプライト描画フラグ
	/// </summary>
	bool m_interactableDarwFlag = false;
	/// <summary>
	/// インタラクト可能スプライト
	/// </summary>
	FontRender m_interactableFontSprite;
};

