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
	/// 文字の位置
	/// </summary>
	static const Vector3 SPRITE_POSITION = { 0.0f,-200.0f,0.0f };
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
	//ボタンのスプライトの初期化
	m_buttonSpriteY.Init("Assets/modelData/objects/crystal/testCommandSprite_Y.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteY.SetPosition(SPRITE_POSITION);

	m_buttonSpriteB.Init("Assets/modelData/objects/crystal/testCommandSprite_B.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteB.SetPosition(SPRITE_POSITION);

	m_buttonSpriteA.Init("Assets/modelData/objects/crystal/testCommandSprite_A.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteA.SetPosition(SPRITE_POSITION);

	m_buttonSpriteX.Init("Assets/modelData/objects/crystal/testCommandSprite_X.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteX.SetPosition(SPRITE_POSITION);

	return true;
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
#endif
	//コレクトフラグがtrueで現在のコマンドが5以下だったら
	if (m_isCollectFlag == true && 
		m_nowCommandNum < COMMAND_MAX)
	{
		//ドローコール
		m_sprites[m_nowCommandNum]->Update();
	}
}

//レンダー関数
void CrystalGetCommandSprite::Render(RenderContext& rc)
{
	//コレクトフラグがtrueで現在のコマンドが5以下だったら
	if (m_isCollectFlag == true && 
		m_nowCommandNum < COMMAND_MAX)
	{
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

	if (m_nowCommandNum > CommandTriggerState::ButtonNum)
	{
		//取得成功時の処理を行う

		//取得フラグをfalseに
		m_isCollectFlag = false;

		//クリスタル本体にこのクリスタルは採取されたと伝える
		m_crystal->CrystalCollected();
	}

	//ボタンが正しく押されたかどうかのフラグを初期化
	m_isCorrectButton = false;

	//タイムリミットを現象
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
		m_isCorrectButton = true;
	}
	else
	{
		//間違ったコマンドが入力された
		m_isCorrectButton = false;
	}

}
