#pragma once

class EnemyBase;
class Load;
class GameSound;

class Gameover : public IGameObject
{
public:
	enum GameoverInitState
	{
		en_initKillEnemy,

		en_initKillOxygen,

		en_null
	};
private:
	GameoverInitState m_gameoverInitState = GameoverInitState::en_null;
	/// <summary>
	/// ゲームオーバーステート
	/// </summary>
	enum GameoverState
	{
		en_standby,

		en_cameraEasing,

		en_enemyAnimation,

		en_gameoverDraw,
		
		en_gameoverEnd,
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

	void InitGameoverInitState(const GameoverInitState initState)
	{
		m_gameoverInitState = initState;
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
	/// ゲームオーバーステートアップデート
	/// </summary>
	void GameoverStateUpdate();
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// フェードアウトフラグ
	/// </summary>
	bool m_fadeOutFlag = false;
	/// <summary>
	/// 暗転したか
	/// </summary>
	bool m_killEndFlag = false;
	/// <summary>
	/// 後ろ側のスプライト
	/// </summary>
	SpriteRender  m_backSideSprite;
	/// <summary>
	/// メイン文字
	/// </summary>
	FontRender m_mainFont;
	/// <summary>
	/// サブ文字
	/// </summary>
	FontRender m_subFont;
	/// <summary>
	/// gameover文字
	/// </summary>
	FontRender m_gameoverFont;
	/// <summary>
	/// 後ろ側のスプライトを描画するかどうか
	/// </summary>
	bool m_backSideSpriteDrawFlag = false;
	/// <summary>
	/// 攻撃エネミー
	/// </summary>
	EnemyBase* m_attackEnemy = nullptr;
	/// <summary>
	/// ロードインスタンス
	/// </summary>
	Load* m_load = nullptr;
	/// <summary>
	/// ゲームサウンド
	/// </summary>
	GameSound* m_gameSound = nullptr;
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
	/// <summary>
	/// 暗転するかどうかを設定
	/// </summary>
	/// <param name="flag"></param>
	void SetFadeOutFlag(const bool& flag)
	{
		m_fadeOutFlag = flag;
	}
	/// <summary>
	/// 暗転するかどうかを取得
	/// </summary>
	/// <returns></returns>
	const bool& GetFadeOutFlag() const
	{
		return m_fadeOutFlag;
	}
	/// <summary>
	/// ゲームオーバーが終了したかどうか
	/// </summary>
	/// <returns></returns>
	const bool& GetGameoverEnd() const
	{
		if (m_gameoverState == GameoverState::en_gameoverEnd)
		{
			return true;
		}

		return false;
	}
	/// <summary>
	/// 後ろ側のスプライトを描画するかどうか
	/// </summary>
	/// <param name="flag"></param>
	void BackSideSpriteDraw(const bool& flag)
	{
		m_backSideSpriteDrawFlag = flag;
	}
};

