#include "stdafx.h"
#include "PlayerScanCrystalUi.h"
#include "Player.h"
//↓これが便利過ぎてつらたん
#include "EnemyAIConWaitTime.h"

//定数等
namespace {
	/// <summary>
	/// 走査線スプライトサイズ
	/// </summary>
	static const float SCANLINE_SPRITE_W_SIZE = 1600.0f;
	static const float SCANLINE_SPRITE_H_SIZE = 900.0f;

	static const float INFOMATION_SPRITE_W_SIZE = 400.0f;
	static const float INFOMATION_SPRITE_H_SIZE = 225.0f;

	static const float SCANLINE_ALPHA_EASING_START = 0.3f;
	static const float SCANLINE_ALPHA_EASING_END = 0.5f;

	static const float SCANLINE_WIPE_START = 0.0f;
	static const float SCANLINE_WIPE_END = -900.0f;
}

//スタート関数
bool PlayerScanCrystalUi::Start()
{
	SpriteInitData scanLineSpriteInitData;

	//画像を設定
	scanLineSpriteInitData.m_ddsFilePath[0] = "Assets/modelData/playerUI/PlayerScanCrystalUi/scanline_sprite.DDS";
	//シェーダーファイルを設定
	scanLineSpriteInitData.m_fxFilePath = "Assets/shader/haruharuWipeSprite.fx";
	//ユーザー拡張データを設定
	scanLineSpriteInitData.m_expandConstantBuffer = &m_scanLineData;
	scanLineSpriteInitData.m_expandConstantBufferSize = sizeof(m_scanLineData);
	//比率を設定
	scanLineSpriteInitData.m_width = static_cast<UINT>(SCANLINE_SPRITE_W_SIZE);
	scanLineSpriteInitData.m_height = static_cast<UINT>(SCANLINE_SPRITE_H_SIZE);
	//ブレンドモードを設定
	scanLineSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//設定したデータをスプライトに設定
	m_scanlineSprite.Init(scanLineSpriteInitData);

	m_scanlineSprite.SetPosition({ 0.0f,0.0f,0.0f });
	
	m_scanLineData.m_wipeDir.Set(0.0f,-1.0f);

	InitInfomationDatas();

	m_waitTime2s = new EnemyAIConWaitTime(2.0f);

	m_waitTime2s->InitData();

	m_waitTime5s = new EnemyAIConWaitTime(5.0f);

	m_waitTime5s->InitData();

	return true;
}

//インフォメーションのデータの初期化関数
void PlayerScanCrystalUi::InitInfomationDatas()
{
	//配列ぶん回す
	for (auto& ptr : m_infoDatas)
	{
		//スプライトのデータを作成
		
		SpriteInitData infoSpriteInitData;

		//画像を設定
		infoSpriteInitData.m_ddsFilePath[0] = "Assets/modelData/playerUI/PlayerScanCrystalUi/digital_infomation_sprite_1.DDS";
		//シェーダーファイルを設定
		infoSpriteInitData.m_fxFilePath = "Assets/shader/haruharuWipeSprite.fx";
		//ユーザー拡張データを設定
		infoSpriteInitData.m_expandConstantBuffer = &ptr.m_easingData;
		infoSpriteInitData.m_expandConstantBufferSize = sizeof(ptr.m_easingData);
		//比率を設定
		infoSpriteInitData.m_width = static_cast<UINT>(INFOMATION_SPRITE_W_SIZE);
		infoSpriteInitData.m_height = static_cast<UINT>(INFOMATION_SPRITE_H_SIZE);
		//ブレンドモードを設定
		infoSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

		ptr.m_infoPtr.Init(infoSpriteInitData);

		//描画しない設定に
		ptr.SetIsDraw(false);

	}

}

//アップデート関数
void PlayerScanCrystalUi::Update()
{
	//もしスキャンフラグがtrueだったら
	if (m_scanFlag == true)
	{
		//スプライトを更新する
		SpriteUpdate();

		//スプライト更新
		m_scanlineSprite.Update();

		for (auto& ptr : m_infoDatas)
		{
			if (ptr.GetIsDraw() == true)
				ptr.m_infoPtr.Update();
		}
	
	}

	//もしRTボタンが押されていて
	//スキャンフラグがfalseだったら
	if (g_pad[0]->IsTrigger(enButtonRB2) 
		&& m_scanFlag == false)
	{
		//スキャンを開始する
		ScanStart();
	}
}

void PlayerScanCrystalUi::SpriteUpdate()
{

	//ステートで分岐させる
	switch (m_scanState)
	{
		//待機状態だったら何もしない
	case PlayerScanCrystalUi::en_scanStandby:
		break;
		//走査線をイージングする
	case PlayerScanCrystalUi::en_scanLineEasing:

		m_scanLineData.m_wipeSize = WipeEasing();

		break;
		//走査線を透明にする
	case PlayerScanCrystalUi::en_scanAEasing:

		m_scanLineData.m_paramA = AlphaEasingWeakBlinking();

		if (m_waitTime2s->Execution())
		{
			m_scanLineData.m_paramA = 0.3;

			m_waitTime5s->InitData();

			m_scanState = ScanState::en_scanMarkerDraw;
		}

		break;
		//マーカーを描画する
	case PlayerScanCrystalUi::en_scanMarkerDraw:

		for (auto& ptr : m_infoDatas)
		{
			if (AngleCheck())
			{

			}	
		}

		if (m_waitTime5s->Execution())
		{

		}

		break;
	default:
		break;
	}

}

//アルファ値イージング関数
const float PlayerScanCrystalUi::AlphaEasingWeakBlinking()
{
	float finalEasing;

	if (m_swapEasing == true)
	{
		m_alphaRatio += g_gameTime->GetFrameDeltaTime() / 2;
	}
	else
	{
		m_alphaRatio += g_gameTime->GetFrameDeltaTime() / 2;
	}

	if (m_alphaRatio > 1.0f)
	{
		//初期化して
		m_alphaRatio = 0.0f;

		m_waitTime2s->InitData();
		
		m_swapEasing = !m_swapEasing;
	}

	if (m_swapEasing == true)
	{
		return finalEasing = Leap(SCANLINE_ALPHA_EASING_START
			, SCANLINE_ALPHA_EASING_END, m_alphaRatio);
	}
	else
	{
		return finalEasing = Leap(SCANLINE_ALPHA_EASING_END
			, SCANLINE_ALPHA_EASING_START, m_alphaRatio);
	}
}

//ワイプイージング関数
const float PlayerScanCrystalUi::WipeEasing()
{
	float finalEasing;

	m_wipeRatio += g_gameTime->GetFrameDeltaTime() / 2;

	if (m_wipeRatio > 1.0f)
	{
		//初期化して…
		m_wipeRatio = 1.0f;
		//ステートを変更
		m_scanState = ScanState::en_scanAEasing;
	}

	return finalEasing = Leap(SCANLINE_WIPE_START
		, SCANLINE_WIPE_END, m_wipeRatio);
}

//プレイヤーのカメラ内にあるかどうかを調べる関数
const bool PlayerScanCrystalUi::AngleCheck()
{


	return false;
}

//ドロー関数
void PlayerScanCrystalUi::Render(RenderContext& rc)
{
	if (m_scanFlag == true)
	{
		m_scanlineSprite.Draw(rc);
	}

}