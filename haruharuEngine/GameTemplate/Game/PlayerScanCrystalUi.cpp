#include "stdafx.h"
#include "PlayerScanCrystalUi.h"
#include "Player.h"

//定数等
namespace {
	/// <summary>
	/// 走査線スプライトサイズ
	/// </summary>
	static const float SCANLINE_SPRITE_W_SIZE = 1600.0f;
	static const float SCANLINE_SPRITE_H_SIZE = 900.0f;

	static const float SCANLINE_ALPHA_EASING_START = 0.0f;
	static const float SCANLINE_ALPHA_EASING_END = 0.5f;

	static const float SCANLINE_WIPE_START = 450.0f;
	static const float SCANLINE_WIPE_END = -450.0f;
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

	m_scanLineData.m_wipeDir.Set(0.0f,1.0f);

	return true;
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
		//現在が待機状態だったら
	case PlayerScanCrystalUi::en_scanStandby:
		//何もしない
		break;
		//現在がアルファ値イージングだったら
	case PlayerScanCrystalUi::en_scanAEasing:
		//画像のアルファ値を操作する
		m_scanLineData.m_paramA = AlphaEasing();
		break;
		//現在が画像イージングだったら
	case PlayerScanCrystalUi::en_scanLineEasing:
		//画像をワイプする
		m_scanLineData.m_wipeSize = WipeEasing();
		break;
		//現在がマーカードローだったら
	case PlayerScanCrystalUi::en_scanMarkerDraw:
		//マーカーを描画する
		break;
	default:
		break;
	}

}

//アルファ値イージング関数
const float PlayerScanCrystalUi::AlphaEasing()
{
	float finalEasing;

	m_alphaRatio -= g_gameTime->GetFrameDeltaTime() / 2;

	if (m_alphaRatio <= 0.0f)
	{
		//初期化して
		m_alphaRatio = 1.0f;
		//ステートを変更
		m_scanState = ScanState::en_scanLineEasing;

	}

	return finalEasing = Leap(SCANLINE_ALPHA_EASING_START
		, SCANLINE_ALPHA_EASING_END, m_alphaRatio);
}

//ワイプイージング関数
const float PlayerScanCrystalUi::WipeEasing()
{
	float finalEasing;

	m_wipeRatio -= g_gameTime->GetFrameDeltaTime() / 2;

	if (m_wipeRatio <= 0.0f)
	{
		//初期化して…
		m_wipeRatio = 1.0f;
		//ステートを変更
		m_scanState = ScanState::en_scanMarkerDraw;
	}

	return finalEasing = Leap(SCANLINE_WIPE_START
		, SCANLINE_WIPE_END, m_wipeRatio);
}

//ドロー関数
void PlayerScanCrystalUi::Render(RenderContext& rc)
{
	if (m_scanFlag == true)
	{
		m_scanlineSprite.Draw(rc);
	}
}