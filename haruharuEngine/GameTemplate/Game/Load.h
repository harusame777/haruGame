#pragma once
class Load : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Load(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Load(){}
private:
	enum LoadState
	{
		en_ordinaryLoad,

		en_circularLoad
	};
	LoadState m_loadState;
	/// <summary>
	/// スタート関数
	/// </summary>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 距離値
	/// </summary>
	float m_loadRange = 0.0f;
	/// <summary>
	/// ロード後ろ側スプライト
	/// </summary>
	SpriteRender m_loadBackSideSprite;
};

