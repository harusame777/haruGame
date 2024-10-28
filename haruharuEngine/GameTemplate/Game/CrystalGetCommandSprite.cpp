#include "stdafx.h"
#include "CrystalGetCommandSprite.h"
#include "Crystal.h"
#include <random>

//これを有効にするとデバッグモードになる
#define DEBUG_MODE

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
	return true;
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

}

//レンダー関数
void CrystalGetCommandSprite::Render(RenderContext& rc)
{
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
		m_timeLimit = 0.0f;
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
		m_timeLimit = 0.0f;
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
	for (int i = 0; i < 5; i++)
	{
		//ランダムな数を入力
		m_commandList[i] = dist(gen);
	}
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
