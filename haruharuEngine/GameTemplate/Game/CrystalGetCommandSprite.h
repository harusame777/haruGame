#pragma once

class Crystal;
class GameSound;
class GameEffect;
class Player;

//定数等
namespace {
	/// <summary>
	/// ツルハシイージング
	/// </summary>
	/// 待機状態
	static const float  PICKAXE_STANDBY_RATIO_MIN = 40.0f;
	static const float  PICKAXE_STANDBY_RATIO_MAX = 20.0f;
	/// <summary>
	/// ツルハシイージング
	/// </summary>
	/// 採掘状態
	static const float PICKAXE_IMPACT_RATIO_MIN = -80.0f;
	static const float PICKAXE_IMPACT_RATIO_MAX = 40.0f;
}

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
	/// <summary>
	/// 採取開始
	/// </summary>
	/// <param name="crystal"></param>
	void CrystalCollectStart(Crystal* crystal)
	{
		//採取中だったら処理しない
		if (m_isCollectFlag == true)
		{
			return;
		}
		//採取されるクリスタルのインスタンスを登録する
		m_crystal = crystal;
		//コマンドをリストを更新する
		CommandMix();
		//制限時間を初期化
		m_timeLimit = 2.0f;
		//現在のコマンドリストの場所を初期化
		m_nowCommandNum = 0;
		//ツルハシのイージングを初期化する
		PickaxeEasingInit(PickaxeMoveState::en_standby);
		//回転も初期化
		Quaternion startRot;
		startRot.SetRotationDegZ(PICKAXE_STANDBY_RATIO_MIN);
		m_pickaxeSprite.SetRotation(startRot);
		//採取フラグをオンにする
		m_isCollectFlag = true;
		//コマンドを入力できるように
		m_isCommandInput = true;
	}

	const bool& GetCollectFlag() const
	{
		return m_isCollectFlag;
	}

private:
	/// <summary>
	/// ツルハシの回転ステート
	/// </summary>
	enum PickaxeMoveState
	{
		/// <summary>
		/// 待機
		/// </summary>
		en_standby,
		/// <summary>
		/// 掘る
		/// </summary>
		en_impact,
	};
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
	/// <summary>
	/// コマンドアップデート
	/// </summary>
	void CommandUpdate();
	/// <summary>
	/// コマンドリストにコマンドをランダムに決定する関数
	/// </summary>
	void CommandMix();
	/// <summary>
	/// スプライトを設定
	/// </summary>
	void InitSprite();
	/// <summary>
	/// ツルハシスプライトのアップデート関数
	/// </summary>
	void PickaxeSpriteUpdate();
	/// <summary>
	/// ツルハシの回転イージング関数
	/// </summary>
	const float PickaxeRotEasing(const PickaxeMoveState picMoveState);
	/// <summary>
	/// プレイヤーが採取可能範囲内にいるかどうかを判定
	/// </summary>
	/// <returns></returns>
	const bool& IsRangeInPlayer();
	/// <summary>
	/// 何ボタンが押されたかを判定するステート
	/// </summary>
	enum CommandTriggerState
	{
		//今押されたのはYボタン
		en_isTriggerY,
		//今押されたのはBボタン
		en_isTriggerB,
		//今押されたのはAボタン
		en_isTriggerA,
		//今押されたのはXボタン
		en_isTriggerX,
		//ボタン数
		ButtonNum
	};
	/// <summary>
	/// コマンドリストの最大値
	/// </summary>
	static const int COMMAND_MAX = 5;
	/// <summary>
	/// コマンドリスト
	/// </summary>
	int m_commandList[COMMAND_MAX];
	/// <summary>
	/// 現在のコマンドナンバー
	/// </summary>
	int m_nowCommandNum = 0;
	/// <summary>
	/// 正しいボタンが押されたかどうかのフラグ
	/// </summary>
	bool m_isCorrectButton = false;
	/// <summary>
	/// 採取フラグ
	/// </summary>
	bool m_isCollectFlag = false;
	/// <summary>
	/// コマンド入力できるか
	/// </summary>
	bool m_isCommandInput = true;
	/// <summary>
	/// ツルハシのスプライトが戻っているか
	/// </summary>
	bool m_isPickaxeImpactBackFlag = false;
	/// <summary>
	/// タイムリミット
	/// </summary>
	float m_timeLimit = 0.0f;
	/// <summary>
	/// ツルハシのスプライト
	/// </summary>
	SpriteRender m_pickaxeSprite;
	/// <summary>
	/// ツルハシの回転ステートの変数\
	/// </summary>
	PickaxeMoveState m_pickaxeMoveState = PickaxeMoveState::en_standby;
	/// <summary>
	/// ツルハシの回転値
	/// </summary>
	float m_pixkaxeRotValue = 0.0f;
	/// <summary>
	/// ツルハシイージング割合
	/// </summary>
	float m_pickaxeEasingRatio = 0.0f;
	/// <summary>
	/// イージング開始値
	/// </summary>
	float m_pickaxeRotStartValue = 0.0f;
	/// <summary>
	/// イージング終了値
	/// </summary>
	float m_pickaxeRotEndValue = 0.0f;
	/// <summary>
	/// ツルハシイージング初期化設定関数
	/// </summary>
	/// <param name="picMoveState"></param>
	void PickaxeEasingInit(const PickaxeMoveState picMoveState)
	{
		m_pickaxeMoveState = picMoveState;

		if (picMoveState == PickaxeMoveState::en_standby)
		{
			m_pickaxeRotStartValue = PICKAXE_STANDBY_RATIO_MIN;

			m_pickaxeRotEndValue = PICKAXE_STANDBY_RATIO_MAX;
		}
		else
		{
			m_pickaxeRotStartValue = PICKAXE_IMPACT_RATIO_MIN;

			m_pickaxeRotEndValue = PICKAXE_IMPACT_RATIO_MAX;
		}

		m_pickaxeEasingRatio = 1.0f;
	}

	/// <summary>
	///	石のスプライト
	/// </summary>
	SpriteRender m_rockSprite;
	/// <summary>
	/// タイマーのスプライト
	/// </summary>
	SpriteRender m_timerSprite;
	/// <summary>
	/// タイマーのスプライトの初期化処理
	/// </summary>
	void TimerSpriteInit();
	/// <summary>
	/// タイマーのスプライトの角度
	/// </summary>
	float m_degree = 9.45f;
	/// <summary>
	/// ボタンのスプライトの配列
	/// </summary>
	SpriteRender* m_sprites[COMMAND_MAX];
	/// <summary>
	/// ボタンのスプライトY
	/// </summary>
	SpriteRender m_buttonSpriteY;
	/// <summary>
	/// ボタンのスプライトB
	/// </summary>
	SpriteRender m_buttonSpriteB;
	/// <summary>
	/// ボタンのスプライトA
	/// </summary>
	SpriteRender m_buttonSpriteA;
	/// <summary>
	/// ボタンのスプライトX
	/// </summary>
	SpriteRender m_buttonSpriteX;
	/// <summary>
	/// クリスタルのインスタンス
	/// </summary>
	Crystal* m_crystal;
	/// <summary>
	/// XYABボタンが押されたかどうかを判定して、正しいボタンが押された、
	/// 押されなかった時の処理をする関数、ボタンが押されたらtrueが帰ってくる
	/// </summary>
	/// <returns></returns>
	bool IsTriggerButton();
	/// <summary>
	/// 正しいコマンドが入力されたかどうかを判断する
	/// </summary>
	void IsJudgeingTriggerButton(const CommandTriggerState& initCommand);
	/// <summary>
	/// ゲームサウンドのインスタンス
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// ゲームエフェクトのインスタンス
	/// </summary>
	GameEffect* m_gameEffect = nullptr;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// デバック用のfontrender
	/// </summary>
	FontRender m_debugFontRender;
	/// <summary>
	/// flaot用線形補間
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}
};

