#include "stdafx.h"
#include "Load.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//定数等
namespace 
{
	static const float LOADBACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float LOADBACKSIDE_SPRITE_H_SIZE = 900.0f;

	static const float ORDINARYLOAD_EASING_MAX = 1.0f;
	static const float ORDINARYLOAD_EASING_MIN = 0.0f;

	static const float CIRCULRLOAD_EASING_MAX = 5.0f;
	static const float CIRCULRLOAD_EASING_MIN = 0.0f;

	static const float ORDINARYLOAD_EASING_ATTENUATIONRATE = 1.0f;
	static const float CIRCULRLOAD_EASING_ATTENUATIONRATE = 15.0f;

}

void Load::LoadExecutionFadeOut(const LoadOrderData& loadType)
{
	if (m_loadProccesState != LoadProccesState::en_loadStandby)
	{
		return;
	}

	//フェードアウトを設定
	m_loadTypeState[LoadOrder::en_FadeOut] = loadType.m_fadeOutLoad;
	//フェードインを設定
	m_loadTypeState[LoadOrder::en_FadeIn] = loadType.m_fadeInLoad;
	//ステートをフェードアウトに
	m_loadProccesState = LoadProccesState::en_loadExecutionFadeOut;

	switch (m_loadTypeState[LoadOrder::en_FadeOut])
	{
	case Load::en_loadOrdinary:

		m_loadEasingMax = ORDINARYLOAD_EASING_MIN;

		m_loadEasingMin = ORDINARYLOAD_EASING_MAX;

		m_loadSpeedAttenuationRate[LoadOrder::en_FadeOut]
			= ORDINARYLOAD_EASING_ATTENUATIONRATE;

		break;
	case Load::en_loadCircular:

		m_loadEasingMax = CIRCULRLOAD_EASING_MAX;

		m_loadEasingMin = CIRCULRLOAD_EASING_MIN;

		m_loadSpeedAttenuationRate[LoadOrder::en_FadeOut]
			= CIRCULRLOAD_EASING_ATTENUATIONRATE;

		break;
	default:
		break;
	}

	m_loadDatas.SetLoadIndex(0.0f);

	m_loadRatio = 0.0f;
}

void Load::LoadExecutionFadeOut(const LoadOrderData& loadType, const float& time)
{
	//フェードアウトを設定
	m_loadTypeState[LoadOrder::en_FadeOut] = loadType.m_fadeOutLoad;
	//フェードインを設定
	m_loadTypeState[LoadOrder::en_FadeIn] = loadType.m_fadeInLoad;
	//ロード時間を設定
	m_loadTimer = time;
	//ステートをフェードアウトに
	m_loadProccesState = LoadProccesState::en_loadExecutionTimeLapse;
}

void Load::LoadExecutionFadeIn()
{
	if (m_loadProccesState != LoadProccesState::en_loadBlackoutStandby)
	{
		return;
	}

	m_loadProccesState = LoadProccesState::en_loadExecutionFadeIn;

	switch (m_loadTypeState[LoadOrder::en_FadeIn])
	{
	case Load::en_loadOrdinary:

		m_loadEasingMin = ORDINARYLOAD_EASING_MIN;

		m_loadEasingMax = ORDINARYLOAD_EASING_MAX;

		m_loadDatas.SetLoadIndex(1.0f);

		m_loadSpeedAttenuationRate[LoadOrder::en_FadeIn]
			= ORDINARYLOAD_EASING_ATTENUATIONRATE;

		break;
	case Load::en_loadCircular:

		m_loadEasingMin = CIRCULRLOAD_EASING_MAX;

		m_loadEasingMax = CIRCULRLOAD_EASING_MIN;

		m_loadDatas.SetLoadIndex(6.0f);

		m_loadSpeedAttenuationRate[LoadOrder::en_FadeIn]
			= CIRCULRLOAD_EASING_ATTENUATIONRATE;

		break;
	default:
		break;
	}

	m_loadRatio = 0.0f;
}

//スタート関数
bool Load::Start()
{
	SpriteInitData loadBackSideInitData;

	//画像を設定
	loadBackSideInitData.m_ddsFilePath[0] = "Assets/modelData/load/game_load_sprite_1.DDS";
	//シェーダーファイルを設定
	loadBackSideInitData.m_fxFilePath = "Assets/shader/haruharuLoadSpriteShader.fx";
	//ユーザー拡張データを設定
	loadBackSideInitData.m_expandConstantBuffer = &m_loadDatas;
	loadBackSideInitData.m_expandConstantBufferSize = sizeof(m_loadDatas);
	//比率を設定
	loadBackSideInitData.m_width = static_cast<UINT>(LOADBACKSIDE_SPRITE_W_SIZE);
	loadBackSideInitData.m_height = static_cast<UINT>(LOADBACKSIDE_SPRITE_H_SIZE);
	//ブレンドモードを設定
	loadBackSideInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//設定したデータをスプライトに設定
	m_loadBackSideSprite.Init(loadBackSideInitData);

	return true;
}

//アップデート関数
void Load::Update()
{
	if (m_loadProccesState == LoadProccesState::en_loadCompletion)
	{
		m_loadProccesState = LoadProccesState::en_loadStandby;
	}

#ifdef DEBUG_MODE

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		LoadExecutionFadeOut({LoadTypeState::en_loadOrdinary,LoadTypeState::en_loadCircular});
	}
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		LoadExecutionFadeIn();
	}

#endif

	LoadStateUpdate();

	m_loadBackSideSprite.Update();
}

void Load::LoadStateUpdate()
{

	switch (m_loadProccesState)
	{
	case Load::en_loadStandby:
		break;
	case Load::en_loadExecutionFadeIn:

		m_loadDatas.SetLoadTypeState(m_loadTypeState[LoadOrder::en_FadeIn]);

		m_loadDatas.SetLoadIndex(LoadCalc(m_loadSpeedAttenuationRate[LoadOrder::en_FadeIn]));

		break;
	case Load::en_loadExecutionFadeOut:

		m_loadDatas.SetLoadTypeState(m_loadTypeState[LoadOrder::en_FadeOut]);

		m_loadDatas.SetLoadIndex(LoadCalc(m_loadSpeedAttenuationRate[LoadOrder::en_FadeOut]));

		break;
	case Load::en_loadExecutionTimeLapse:
		break;
	case Load::en_loadBlackoutStandby:

		//待機

		break;
	default:
		break;
	}

}

const float& Load::LoadCalc(const float& index)
{
	m_loadRatio += g_gameTime->GetFrameDeltaTime() / index;

	if (m_loadRatio > 1.0f)
	{
		m_loadRatio = 1.0f;

		if (m_loadProccesState == LoadProccesState::en_loadExecutionFadeOut)
		{
			m_loadProccesState = LoadProccesState::en_loadBlackoutStandby;
		}
		else if(m_loadProccesState == LoadProccesState::en_loadExecutionFadeIn)
		{
			m_loadProccesState = LoadProccesState::en_loadCompletion;
		}
	}

	return Leap(m_loadEasingMax, m_loadEasingMin, m_loadRatio);
}

//レンダー関数
void Load::Render(RenderContext& rc)
{
	m_loadBackSideSprite.Draw(rc);
}