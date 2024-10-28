#pragma once

class Crystal;

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
		//採取フラグをオンにする
		m_isCollectFlag = true;
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
	/// コマンドリスト
	/// </summary>
	int m_commandList[5];
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
	/// タイムリミット
	/// </summary>
	float m_timeLimit = 0.0f;
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
	/// デバック用のfontrender
	/// </summary>
	FontRender m_debugFontRender;
};

