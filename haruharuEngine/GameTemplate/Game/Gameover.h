#pragma once

class EnemyBase;
class Load;

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

		en_gameoverDraw,
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
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 暗転したか
	/// </summary>
	bool m_killEndFlag = false;
	/// <summary>
	/// 後ろ側のスプライト
	/// </summary>
	SpriteRender  m_backSideSprite;
	/// <summary>
	/// 攻撃エネミー
	/// </summary>
	EnemyBase* m_attackEnemy = nullptr;
	/// <summary>
	/// ロードインスタンス
	/// </summary>
	Load* m_load = nullptr;
public:
	/// <summary>
	/// 暗転したかどうかを設定
	/// </summary>
	/// <param name="is"></param>
	void SetKillEndFlag(const bool& is)
	{
		m_killEndFlag = is;
	}
	/// <summary>
	/// 暗転したかどうかを取得
	/// </summary>
	/// <returns></returns>
	const bool& GetKillEndFlag() const
	{
		return m_killEndFlag;
	}
};

