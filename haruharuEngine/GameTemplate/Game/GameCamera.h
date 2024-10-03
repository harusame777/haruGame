#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCamera();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameCamera();
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
	/// 注視点から視点までのベクトル
	/// </summary>
	Vector3 m_toCameraPos;
	/// <summary>
	/// プレイヤーのインスタンスを格納するための変数
	/// </summary>
	Player* m_player = nullptr;
};
