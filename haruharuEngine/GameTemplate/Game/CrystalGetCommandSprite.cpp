#include "stdafx.h"
#include "CrystalGetCommandSprite.h"
#include "Crystal.h"
#include <random>

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//定数等
namespace {
	/// <summary>
	/// 文字震えの強さ
	/// </summary>
	static const float SHAKE_POWER = 5.0f;
	/// <summary>
	/// 文字震えの速さ
	/// </summary>
	static const float SHAKE_SPEED = 20.0f;
	/// <summary>
	/// 文字サイズ
	/// </summary>
	static const float SPRITE_W_SIZE = 150.0f;
	static const float SPRITE_H_SIZE = 150.0f;
	/// <summary>
	/// ツルハシスプライトサイズ
	/// </summary>
	static const float PICKAXE_SPRITE_W_SIZE = 200.0f;
	static const float PICKAXE_SPRITE_H_SIZE = 200.0f;
	/// <summary>
	/// 岩スプライトサイズ
	/// </summary>
	static const float ROCK_SPRITE_W_SIZE = 600.0f;
	static const float ROCK_SPRITE_H_SIZE = 600.0f;
	/// <summary>
	/// 文字の位置
	/// </summary>
	static const Vector3 SPRITE_POSITION = { 0.0f,-250.0f,0.0f };
	/// <summary>
	/// ツルハシ位置
	/// </summary>
	static const Vector3 PICKAXE_POSITION = { -140.0f,-150.0f,0.0f };
	/// <summary>
	/// 岩位置
	/// </summary>
	static const Vector3 ROCK_POSITION = { 0.0f,-250.0f,0.0f };
}

//コンストラクタ
CrystalGetCommandSprite::CrystalGetCommandSprite()
{

}

//デストラクタ
CrystalGetCommandSprite::~CrystalGetCommandSprite()
{

}

//スタート関数
bool CrystalGetCommandSprite::Start()
{
	//演出のスプライトの初期化
	//ツルハシ
	m_pickaxeSprite.Init("Assets/modelData/objects/crystal/digital_pickaxe_sprite.DDS", PICKAXE_SPRITE_W_SIZE, PICKAXE_SPRITE_H_SIZE);
	m_pickaxeSprite.SetPivot({ 0.5f,0.0f });
	m_pickaxeSprite.SetPosition(PICKAXE_POSITION);
	//岩
	m_rockSprite.Init("Assets/modelData/objects/crystal/digital_rock_sprite.DDS", ROCK_SPRITE_W_SIZE, ROCK_SPRITE_H_SIZE);
	m_rockSprite.SetPosition(ROCK_POSITION);

	//ボタンのスプライトの初期化
	m_buttonSpriteY.Init("Assets/modelData/objects/crystal/CommandSprite_Y.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteY.SetPosition(SPRITE_POSITION);

	m_buttonSpriteB.Init("Assets/modelData/objects/crystal/CommandSprite_B.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteB.SetPosition(SPRITE_POSITION);

	m_buttonSpriteA.Init("Assets/modelData/objects/crystal/CommandSprite_A.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteA.SetPosition(SPRITE_POSITION);

	m_buttonSpriteX.Init("Assets/modelData/objects/crystal/CommandSprite_X.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteX.SetPosition(SPRITE_POSITION);

	PickaxeEasingInit(PickaxeMoveState::en_standby);

	return true;
}

void CrystalGetCommandSprite::TimerSpriteInit()
{

	SpriteInitData timerSpriteData;



}

//スプライトの初期化
void CrystalGetCommandSprite::InitSprite()
{

	int nowCommandListNum;
	
	//コマンドリスト分for文を回す
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		//コマンドリストのナンバーを格納する
		nowCommandListNum = m_commandList[i];

		//スプライトレンダーを設定
		switch (nowCommandListNum)
		{
		case en_isTriggerY:
			m_sprites[i] = &m_buttonSpriteY;
			break;
		case en_isTriggerB:
			m_sprites[i] = &m_buttonSpriteB;
			break;
		case en_isTriggerA:
			m_sprites[i] = &m_buttonSpriteA;
			break;
		case en_isTriggerX:
			m_sprites[i] = &m_buttonSpriteX;
			break;
		}
	}
}

//アップデート関数
void CrystalGetCommandSprite::Update()
{
	//コマンドのアップデート処理
	CommandUpdate();
#ifdef DEBUG_MODE
	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"Command[%01d]",int(m_commandList[m_nowCommandNum]));

	m_debugFontRender.SetText(wcsbuf);

	//Quaternion test;

	//m_pixkaxeRotValue += 5.0f;

	//test.AddRotationDegZ(m_pixkaxeRotValue);

	//m_pickaxeSprite.SetRotation(test);

#endif
	//コレクトフラグがtrueで現在のコマンドが5以下だったら
	if (m_isCollectFlag == true /*&& 
		m_nowCommandNum < COMMAND_MAX*/)
	{
		//ドローコール
		m_pickaxeSprite.Update();
		m_rockSprite.Update();

		if (m_nowCommandNum >= COMMAND_MAX)
			return;
		m_sprites[m_nowCommandNum]->Update();

	}
}

//レンダー関数
void CrystalGetCommandSprite::Render(RenderContext& rc)
{
	//コレクトフラグがtrueで現在のコマンドが5以下だったら
	if (m_isCollectFlag == true /*&& 
		m_nowCommandNum < COMMAND_MAX*/)
	{
		m_pickaxeSprite.Draw(rc);
		m_rockSprite.Draw(rc);

		if (m_nowCommandNum >= COMMAND_MAX)
			return;
		m_sprites[m_nowCommandNum]->Draw(rc);
	}
#ifdef DEBUG_MODE
	m_debugFontRender.Draw(rc);
#endif
}

void CrystalGetCommandSprite::CommandUpdate()
{

	//コレクトフラグがfalseだったら
	if (m_isCollectFlag == false)
	{
		//処理はしない
		return;
	}

	//ツルハシのスプライト更新処理をする
	PickaxeSpriteUpdate();

	//ボタンが正しく押されたかどうかのフラグを初期化
	m_isCorrectButton = false;

	//ボタン入力ができなかったら
	if (m_isCommandInput == false)
	{
		//戻す
		return;
	}

	if (m_nowCommandNum > CommandTriggerState::ButtonNum)
	{
		//取得成功時の処理を行う

		//取得フラグをfalseに
		m_isCollectFlag = false;

		//クリスタル本体にこのクリスタルは採取されたと伝える
		m_crystal->CrystalCollected();

		return;
	}

	//タイムリミットを減少
	m_timeLimit -= g_gameTime->GetFrameDeltaTime();

	//ボタンが押されたかどうかを判定して、押されたら
	//コマンドが正しいかを判定する
	//もしボタンが押されていて、コマンドが正しかったら
	if (IsTriggerButton() &&
		m_isCorrectButton == true)
	{

		//タイムリミットを初期化
		m_timeLimit = 2.0f;
		//commandListを次に進める
		m_nowCommandNum++;
	}

	//もしボタンが押されていて、コマンドが間違っていたら、または
	//タイムリミットが0秒以下だったら
	else if(IsTriggerButton() && m_isCorrectButton == false ||
		m_timeLimit <= 0.0f)
	{
		//間違っていた時の処理
		 
		//採取フラグをオフにする
		m_isCollectFlag = false;

		//クリスタル本体にこのクリスタルの採取に失敗したと伝える
		m_crystal->CollectedFailure();
	}

}

void CrystalGetCommandSprite::CommandMix()
{
	//randomライブラリを使用してランダムな値を生成する
	//シード生成
	std::random_device rd;
	std::mt19937 gen(rd());
	//0から3までの範囲で一様分布の整数を生成
	std::uniform_int_distribution<> dist(0, 3);

	//コマンドをランダムに決定する
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		//ランダムな数を入力
		m_commandList[i] = dist(gen);
	}

	//スプライトを初期化する
	InitSprite();
}

//XYABボタンが押されたかどうかを判定して、正しいボタンが押された、
// 押されなかった時の処理をする関数、ボタンが押されたらtrueが帰ってくる
bool CrystalGetCommandSprite::IsTriggerButton()
{

	//もしYボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		//押されたボタンに対応したボタンステートを送る
		IsJudgeingTriggerButton(CommandTriggerState::en_isTriggerY);
		return true;
	}
	//もしBボタンが押されたら
	else if (g_pad[0]->IsTrigger(enButtonB))
	{
		//押されたボタンに対応したボタンステートを送る
		IsJudgeingTriggerButton(CommandTriggerState::en_isTriggerB);
		return true;
	}
	//もしAボタンが押されたら
	else if (g_pad[0]->IsTrigger(enButtonA))
	{
		//押されたボタンに対応したボタンステートを送る
		IsJudgeingTriggerButton(CommandTriggerState::en_isTriggerA);
		return true;
	}
	//もしXボタンが押されたら
	else if (g_pad[0]->IsTrigger(enButtonX))
	{
		//押されたボタンに対応したボタンステートを送る
		IsJudgeingTriggerButton(CommandTriggerState::en_isTriggerX);
		return true;
	}

	return false;
}

//正しいコマンドが入力されたかどうかを判断する関数
void CrystalGetCommandSprite::IsJudgeingTriggerButton(const CommandTriggerState& initCommand)
{

	//入力されたコマンドナンバーを取得する
	int initNumber = initCommand;

	//コマンドリストのナンバーを取得する
	int JudgeNum = m_commandList[m_nowCommandNum];

	//もし同じナンバーだったら
	if (JudgeNum == initNumber)
	{
		//正しくコマンドが入力された
		PickaxeEasingInit(PickaxeMoveState::en_impact);

		m_isCommandInput = false;

		m_isCorrectButton = true;
	}
	else
	{
		//間違ったコマンドが入力された
		PickaxeEasingInit(PickaxeMoveState::en_impact);

		m_isCommandInput = false;

		m_isCorrectButton = false;
	}

}

//ツルハシのスプライトのアップデート関数
void CrystalGetCommandSprite::PickaxeSpriteUpdate()
{
	//回転値を作成
	Quaternion picRot;

	//イージングの値を取得
	m_pixkaxeRotValue = PickaxeRotEasing(m_pickaxeMoveState);

	//回転値を加減
	picRot.SetRotationDegZ(m_pixkaxeRotValue);

	//描画変更
	m_pickaxeSprite.SetRotation(picRot);
}

//ツルハシの回転イージング関数
const float CrystalGetCommandSprite::PickaxeRotEasing(const PickaxeMoveState picMoveState)
{
	//割合を減らす

	//最終的な回転値
	float finalFloat;
	//入れ替えに使う変数
	float swap = 0.0f;

	if (picMoveState == PickaxeMoveState::en_standby)
	{
		m_pickaxeEasingRatio -= g_gameTime->GetFrameDeltaTime();

		//もし割合が0以下だったら
		if (m_pickaxeEasingRatio <= 0.0f)
		{
			//初期化して…
			m_pickaxeEasingRatio = 1.0f;
			//入れ替えて処理する
			swap = m_pickaxeRotStartValue;
			m_pickaxeRotStartValue = m_pickaxeRotEndValue;
			m_pickaxeRotEndValue = swap;
		}

	}
	else
	{
		m_pickaxeEasingRatio -= g_gameTime->GetFrameDeltaTime() * 2;

		//もし割合が0以下だったら
		if (m_pickaxeEasingRatio <= 0.0f)
		{
			//もしツルハシのスプライトが帰ってきていたら
			if (m_isPickaxeImpactBackFlag == true)
			{
				//0で初期化して…
				m_pickaxeEasingRatio = 0.0f;
				//フラグをfalseに
				m_isPickaxeImpactBackFlag = false;
				//コマンドを入力できるように
				m_isCommandInput = true;
				//ツルハシのスプライトを待機状態にして
				PickaxeEasingInit(PickaxeMoveState::en_standby);
				//線形補間した値を返す	
				return finalFloat = Leap(m_pickaxeRotStartValue, m_pickaxeRotEndValue, m_pickaxeEasingRatio);
			}
			//初期化して…
			m_pickaxeEasingRatio = 1.0f;

			//入れ替えて処理する
			swap = m_pickaxeRotStartValue;
			m_pickaxeRotStartValue = m_pickaxeRotEndValue;
			m_pickaxeRotEndValue = swap;
			//ツルハシを返すようにする
			m_isPickaxeImpactBackFlag = true;
		}

	}

	//線形補間した値を返す	
	return finalFloat = Leap(m_pickaxeRotStartValue, m_pickaxeRotEndValue, m_pickaxeEasingRatio);
}
