#include "stdafx.h"
#include "PlayerScanCrystalUi.h"
#include "Player.h"
#include "ManagerCrystal.h"
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

	static const float SCANINFO_EASING_START = 0.0f;
	static const float SCANINFO_EASING_END = -1600.0f;
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

	m_managerCrystal = FindGO<ManagerCrystal>("CrystalMetaAI");

	m_crystalDataHolder = m_managerCrystal->GetCrystalDataHolder();

	InitInfomationDatas();

	m_playerPtr = FindGO<Player>("player");

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
	for (int infoNum = 0; infoNum < MAX_CRYSTAL_NUM; infoNum++)
	{
		//スプライトのデータを作成

		SpriteInitData infoSpriteInitData;

		//画像を設定
		infoSpriteInitData.m_ddsFilePath[0] = "Assets/modelData/playerUI/PlayerScanCrystalUi/digital_infomation_sprite_1.DDS";
		//シェーダーファイルを設定
		infoSpriteInitData.m_fxFilePath = "Assets/shader/haruharuWipeSpriteMoveVer.fx";
		//ユーザー拡張データを設定
		infoSpriteInitData.m_expandConstantBuffer = &m_infoDatas[infoNum].m_easingData;
		infoSpriteInitData.m_expandConstantBufferSize = sizeof(m_infoDatas[infoNum].m_easingData);
		//比率を設定
		infoSpriteInitData.m_width = static_cast<UINT>(INFOMATION_SPRITE_W_SIZE);
		infoSpriteInitData.m_height = static_cast<UINT>(INFOMATION_SPRITE_H_SIZE);
		//ブレンドモードを設定
		infoSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

		m_infoDatas[infoNum].m_infoPtr.Init(infoSpriteInitData);

		m_infoDatas[infoNum].m_easingData.m_wipeDir.Set(-1.0f, 0.0);

		m_infoDatas[infoNum].m_infoPtr.SetPivot({0.0f, 0.0f});

		m_infoDatas[infoNum].m_infoPtr.SetScale({0.5f,0.5f,1.0f});

		m_infoDatas[infoNum].m_easingData.m_wipeSize = 0.0f;

		//描画しない設定に
		m_infoDatas[infoNum].SetIsDraw(false);

		m_infoDatas[infoNum].SetCrystalData(m_crystalDataHolder->GetCrystalDataHolder(infoNum));

	}

}

//アップデート関数
void PlayerScanCrystalUi::Update()
{
	//もしスキャンフラグがtrueだったら
	if (m_scanState != ScanState::en_scanStandby)
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
		&& m_scanState == ScanState::en_scanStandby)
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

		for (int infoNum = 0; infoNum < MAX_CRYSTAL_NUM; infoNum++)
		{
			if (AngleCheck(infoNum) 
				&& m_infoDatas[infoNum].GetCrystalData()->GetCollected() == false)
			{
				m_infoDatas[infoNum].SetIsDraw(true);

				m_infoDatas[infoNum].m_easingData.m_wipeSize = InfoWipeEasing(infoNum);

				SetInfoSpritePosition(infoNum);

				m_infoDatas[infoNum].m_infoPtr.Update();
			}	
			else
			{
				m_infoDatas[infoNum].SetIsDraw(false);
			}
		}

		if (m_scanLineData.m_paramA >= 0.0f)
		{
			m_scanLineData.m_paramA -= 0.05f;
		}

		if (m_waitTime5s->Execution())
		{
			for (int infoNum = 0; infoNum < MAX_CRYSTAL_NUM; infoNum++)
			{
				m_infoDatas[infoNum].SetIsDraw(false);
			}

			m_scanState = ScanState::en_scanStandby;
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

const float PlayerScanCrystalUi::InfoWipeEasing(const int infoNo)
{
	float finalEasing;

	float finalWipeRatio = m_infoDatas[infoNo].GetInfoWipeRatio();

	m_infoDatas[infoNo].SetInfoWipeRatio(finalWipeRatio
		+= g_gameTime->GetFrameDeltaTime());

	if (m_infoDatas[infoNo].GetInfoWipeRatio() > 1.0f)
	{
		//初期化して
		m_infoDatas[infoNo].SetInfoWipeRatio(1.0f);
	}

	return finalEasing = Leap(SCANINFO_EASING_START,
		SCANINFO_EASING_END, m_infoDatas[infoNo].GetInfoWipeRatio());
}

void PlayerScanCrystalUi::SetInfoSpritePosition(const int infoNum)
{
	Vector2 spritePos;

	Vector3 crystalPos;

	crystalPos = m_infoDatas[infoNum].GetCrystalData()->GetPosition();

	g_camera3D->CalcScreenPositionFromWorldPosition(spritePos, crystalPos);

	m_infoDatas[infoNum].m_infoPtr.SetPosition({spritePos.x,spritePos.y,0.0f});
}

//プレイヤーのカメラ内にあるかどうかを調べる関数
const bool PlayerScanCrystalUi::AngleCheck(const int infoNum)
{
	//エネミーからプレイヤーに向かうベクトルを計算
	Vector3 diff = m_infoDatas[infoNum].GetCrystalData()->GetPosition() - m_playerPtr->GetPosition();

	//エネミーからプレイヤーに向かうベクトルを正規化
	diff.Normalize();
	//エネミーの正面ベクトルと、敵からプレイヤーに向かうベクトルの
	//内積(cosθ)を求める。
	float cos = g_camera3D->GetForward().Dot(diff);
	if (cos >= 1)
	{
		cos = 1.0f;
	}
	//内積(cosθ)から角度(θ)を求める
	float angle = acosf(cos);
	//角度(θ)が90°(視野角)より小さければ
	if (angle <= (Math::PI / 180.0f) * 90.f)
	{
		//見つかった！
		return true;
	}

	return false;
}

//ドロー関数
void PlayerScanCrystalUi::Render(RenderContext& rc)
{
	if (m_scanFlag == true)
	{
		m_scanlineSprite.Draw(rc);
	}

	for (int infoNum = 0; infoNum < MAX_CRYSTAL_NUM; infoNum++)
	{
		if (m_infoDatas[infoNum].GetIsDraw() == true)
		{
			m_infoDatas[infoNum].m_infoPtr.Draw(rc);
		}
	}

}