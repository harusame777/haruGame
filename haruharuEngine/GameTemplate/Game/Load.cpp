#include "stdafx.h"
#include "Load.h"

//�����L���ɂ���ƃf�o�b�O���[�h�ɂȂ�
//#define DEBUG_MODE

//�萔��
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

	//�t�F�[�h�A�E�g��ݒ�
	m_loadTypeState[LoadOrder::en_FadeOut] = loadType.m_fadeOutLoad;
	//�t�F�[�h�C����ݒ�
	m_loadTypeState[LoadOrder::en_FadeIn] = loadType.m_fadeInLoad;
	//�X�e�[�g���t�F�[�h�A�E�g��
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
	//�t�F�[�h�A�E�g��ݒ�
	m_loadTypeState[LoadOrder::en_FadeOut] = loadType.m_fadeOutLoad;
	//�t�F�[�h�C����ݒ�
	m_loadTypeState[LoadOrder::en_FadeIn] = loadType.m_fadeInLoad;
	//���[�h���Ԃ�ݒ�
	m_loadTimer = time;
	//�X�e�[�g���t�F�[�h�A�E�g��
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

//�X�^�[�g�֐�
bool Load::Start()
{
	SpriteInitData loadBackSideInitData;

	//�摜��ݒ�
	loadBackSideInitData.m_ddsFilePath[0] = "Assets/modelData/load/game_load_sprite_1.DDS";
	//�V�F�[�_�[�t�@�C����ݒ�
	loadBackSideInitData.m_fxFilePath = "Assets/shader/haruharuLoadSpriteShader.fx";
	//���[�U�[�g���f�[�^��ݒ�
	loadBackSideInitData.m_expandConstantBuffer = &m_loadDatas;
	loadBackSideInitData.m_expandConstantBufferSize = sizeof(m_loadDatas);
	//�䗦��ݒ�
	loadBackSideInitData.m_width = static_cast<UINT>(LOADBACKSIDE_SPRITE_W_SIZE);
	loadBackSideInitData.m_height = static_cast<UINT>(LOADBACKSIDE_SPRITE_H_SIZE);
	//�u�����h���[�h��ݒ�
	loadBackSideInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//�ݒ肵���f�[�^���X�v���C�g�ɐݒ�
	m_loadBackSideSprite.Init(loadBackSideInitData);

	return true;
}

//�A�b�v�f�[�g�֐�
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

		//�ҋ@

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

//�����_�[�֐�
void Load::Render(RenderContext& rc)
{
	m_loadBackSideSprite.Draw(rc);
}