#pragma once
class CrystalGetCommandSprite : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CrystalGetCommandSprite();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CrystalGetCommandSprite();
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
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
};

