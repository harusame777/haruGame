#pragma once
class Gameover : public IGameObject
{
private:
	/// <summary>
	/// ゲームオーバーステート
	/// </summary>
	enum GameoverState
	{
		en_standby,

		en_cameraEasing,

		en_enemyAnimation,
	};
	GameoverState m_gameoverState = GameoverState::en_standby;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Gameover() {}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Gameover(){}
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
	/// ゲームオーバーステートアップデート
	/// </summary>
	void GameoverStateUpdate();
	/// <summary>
	/// カメラのイージング処理
	/// </summary>
	/// <returns></returns>
	const bool& CameraEasing();
	/// <summary>
	/// カメラのイージングに使う関数
	/// </summary>
	Vector3 m_cameraToTargetDir;
	Vector3 m_cameraToWarriorDir;
	Quaternion m_startRotation;
	Quaternion m_endRotation;
	Quaternion m_finalQu;
	Vector3 m_startPos;
	Vector3 m_endPos;
	float m_cameraEasingRatio;
	Vector3 m_finalVector;
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 後ろ側のスプライト
	/// </summary>
	SpriteRender  m_backSideSprite;
};

