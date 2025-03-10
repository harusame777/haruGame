#include "stdafx.h"
#include "PlayerStaminaUi.h"

//定数等
namespace {
	//スタミナ枠のサイズWとH
	static const float STAMINABASE_SPRITE_W_SIZE = 545.0f;
	static const float STAMINABASE_SPRITE_H_SIZE = 157.0f;
	//スタミナバーのサイズWとH
	static const float STAMINABAR_SPRITE_W_SIZE = 530.0f;
	static const float STAMINABAR_SPRITE_H_SIZE = 142.0f;
	//スタミナの位置、サイズ
	static const Vector3 OXYGENBASE_SPRITE_POSITION = { -0.0f,-350.0f,0.0f };
	static const Vector3 STAMINABASE_SPRITE_SIZE = { 0.2f,0.2f,0.0f };
	//スタミナ低下ラインと、空になるライン
	static const float STAMINA_LOW = 45.0f;
	static const float STAMINA_OUT = 0.0f;
	//スタミナバーのアルファ値イージングAとB
	static const float STAMINABAR_ALPHA_EASING_START = 0.4f;
	static const float STAMINABAR_ALPHA_EASING_END = 0.7f;
}

//スタート関数
bool PlayerStaminaUi::Start()
{
	//スタミナの枠を初期化
	m_staminaBase.Init("Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gauge_sprite_1.DDS",
		STAMINABASE_SPRITE_W_SIZE,
		STAMINABASE_SPRITE_H_SIZE);
	//位置を設定
	m_staminaBase.SetPosition(OXYGENBASE_SPRITE_POSITION);
	m_staminaBase.Update();

	SpriteInitData staminaBarInitData;
	//画像を設定
	staminaBarInitData.m_ddsFilePath[0] = "Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gaugebar_sprite_1.DDS";
	//アルファ値操作用の画像設定
	m_staminaBarAlphaTexture.InitFromDDSFile(L"Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gaugebar_sprite_2.DDS");
	staminaBarInitData.m_expandShaderResoruceView[0] = &m_staminaBarAlphaTexture;
	staminaBarInitData.m_fxFilePath = "Assets/shader/haruharuStaminaBarSpriteShader.fx";
	//ユーザー拡張データを設定
	staminaBarInitData.m_expandConstantBuffer = &m_staminaBarData;
	staminaBarInitData.m_expandConstantBufferSize += sizeof(m_staminaBarData);
	//比率を設定
	staminaBarInitData.m_width = static_cast<UINT>(STAMINABAR_SPRITE_W_SIZE);
	staminaBarInitData.m_height = static_cast<UINT>(STAMINABAR_SPRITE_H_SIZE);
	//ブレンドモードを設定
	staminaBarInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//設定したデータをスプライトに設定
	m_staminaBar.Init(staminaBarInitData);
	//位置を設定
	m_staminaBar.SetPosition(OXYGENBASE_SPRITE_POSITION);
	m_staminaBar.Update();

	//m_staminaBar.Init("Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gaugebar_sprite_1.DDS",
	//	STAMINABAR_SPRITE_W_SIZE,
	//	STAMINABAR_SPRITE_H_SIZE);

	return true;
}

//アップデート関数
void PlayerStaminaUi::Update()
{
	//プレイヤーからスタミナの値を受け取っていなかったら更新しない
	if (m_playerStamina == nullptr)
	{
		return;
	}

	//UIのスタミナ値を更新
	m_mainStamina = *m_playerStamina;
	//スタミナのステートを更新
	StaminaStateUpdate();
	//スタミナの点滅処理
	BlinkingBarCalc();
	//スタミナバーの制御処理
	m_staminaBarData.SetDegree(WipeCalc());
	//スタミナバーを更新
	m_staminaBar.Update();
	//スタミナ枠を更新
	m_staminaBase.Update();
}

//スタミナのステートを更新する関数
void PlayerStaminaUi::StaminaStateUpdate()
{
	//スタミナの値を取得
	const float nowStaminaValue = m_mainStamina;

	//もしスタミナが空だったら
	if (m_staminaOutFlag == true)
	{
		//もしスタミナが100未満だったら
		if (m_mainStamina < MAX_STAMINA_INDEX)
		{
			//この後の処理をしない
			return;
		}
		//もしスタミナが100以上だったら
		else
		{
			//スタミナは空ではない
			m_staminaOutFlag = false;
		}
	}

	//もしスタミナが0以下だったら
	if (nowStaminaValue <= STAMINA_OUT)
	{
		//ステートをスタミナ空状態に
		m_staminaState = StaminaUiState::en_staminaOut;
		//スタミナは空である
		m_staminaOutFlag = true;
	}
	//もしスタミナがSTAMINA_OUTより多くSTAMINA_LOW以下であったら
	else if (nowStaminaValue <= STAMINA_LOW
		&& nowStaminaValue > STAMINA_OUT)
	{
		//ステートをスタミナ低下状態に
		m_staminaState = StaminaUiState::en_staminaLow;
	}
	//もしスタミナがSTAMINA_LOWより多くMAX_STAMINA_INDEX以下であったら
	else if (nowStaminaValue <= MAX_STAMINA_INDEX
		&& nowStaminaValue > STAMINA_LOW)
	{
		//ステートをスタミナ通常状態に
		m_staminaState = StaminaUiState::en_staminaHigh;
	}
}

//スタミナの点滅制御関数
void PlayerStaminaUi::BlinkingBarCalc()
{
	//スタミナステートによって制御を変化
	switch (m_staminaState)
	{
		//ステートがen_staminaHighの場合
	case PlayerStaminaUi::en_staminaHigh:
		//アルファ値が1.0f以下であれば
		if (m_staminaBarData.GetAlpha() <= 0.7f)
		{
			//アルファ値を0.1加算
			m_staminaBarData.AddAlpha(0.1f);

			m_alphaRatio = 0.0f;
		}
		//バーの色を通常色に
		m_staminaBarData.SetRedAddFlag(false);

		break;
		//ステートがen_staminaLowの場合
	case PlayerStaminaUi::en_staminaLow:
		//スタミナを点滅させて
		m_staminaBarData.SetAlpha(AlphaEasing());
		//バーの色を通常色に
		m_staminaBarData.SetRedAddFlag(false);

		break;
	case PlayerStaminaUi::en_staminaOut:
		//スタミナを点滅させて
		m_staminaBarData.SetAlpha(AlphaEasing());
		//バーの色を赤に
		m_staminaBarData.SetRedAddFlag(true);

		break;
	default:
		break;
	}

}

//スタミナのワイプ計算関数
const float& PlayerStaminaUi::WipeCalc()
{
	float finalValue;

	//スタミナの値の割合でスタミナバーの割合を制御する計算
	finalValue = INIT_DEGREE_VALUE + (m_mainStamina / MAX_STAMINA_INDEX) *
		(MAX_DEGREE_VALUE - INIT_DEGREE_VALUE);

	return finalValue;
}

//スタミナのアルファ値イージング関数
const float& PlayerStaminaUi::AlphaEasing()
{
	//もしアルファ値イージング割合が1.0f以下だったら
	if (m_alphaRatio >= 1.0f)
	{
		//アルファ値イージング割合を0.0fに
		m_alphaRatio = 0.0f;
	}

	//イージングのAとBの変数
	float easingStart = 0.0f;
	float easingEnd = 0.0f;

	//イージングが完了すたびにAとBを入れ替える
	if (m_alphaEasingInversionFlag == true)
	{
		easingStart = STAMINABAR_ALPHA_EASING_END;

		easingEnd = STAMINABAR_ALPHA_EASING_START;
	}
	else
	{
		easingStart = STAMINABAR_ALPHA_EASING_START;

		easingEnd = STAMINABAR_ALPHA_EASING_END;
	}

	//アルファ値イージング割合を加算
	m_alphaRatio += g_gameTime->GetFrameDeltaTime();

	//アルファ値イージング割合が1.0fより多かったら
	if (m_alphaRatio > 1.0f)
	{
		//アルファ値イージング割合を1.0fにして
		m_alphaRatio = 1.0f;
		//AとBを反転させる
		m_alphaEasingInversionFlag = !m_alphaEasingInversionFlag;
	}

	//Leapで計算した値を返す
	return Leap(easingStart,
		easingEnd,
		m_alphaRatio);
}

//レンダー関数
void PlayerStaminaUi::Render(RenderContext& rc)
{
	m_staminaBar.Draw(rc);

	m_staminaBase.Draw(rc);
}