#include "stdafx.h"
#include "Load.h"

//�����L���ɂ���ƃf�o�b�O���[�h�ɂȂ�
//#define DEBUG_MODE

//�萔��
namespace 
{
	//���[�h�w�i�T�C�Y
	static const float LOADBACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float LOADBACKSIDE_SPRITE_H_SIZE = 900.0f;
	//���[�h���邮�邷���̃T�C�Y
	static const float LOADOPTION_SPRITE_W_SIZE = 100.0f;
	static const float LOADOPTION_SPRITE_H_SIZE = 100.0f;
	//���[�h���邮�邷���̈ʒu
	static const Vector3 LOADOPTION_SPRITE_POSITION = { 690.0f,-350.0f,0.0f };
	//�ʏ탍�[�h�t�F�[�h�C�[�W���O���l
	static const float ORDINARYLOAD_EASING_MAX = 1.0f;
	static const float ORDINARYLOAD_EASING_MIN = 0.0f;
	//�~�`���[�h�t�F�[�h�C�[�W���O���l
	static const float CIRCULRLOAD_EASING_MAX = 1.0f;
	static const float CIRCULRLOAD_EASING_MIN = 0.0f;
	//���[�h�t�F�[�h�X�s�[�h
	static const float ORDINARYLOAD_EASING_ATTENUATIONRATE = 1.0f;
	static const float CIRCULRLOAD_EASING_ATTENUATIONRATE_A = 1.0f;
	static const float CIRCULRLOAD_EASING_ATTENUATIONRATE_B = 0.2f;
}

void Load::LoadExecutionFadeOut(const LoadOrderData& loadType)
{
	//���[�h���������ł���΁@
	if (m_loadProccesState != LoadProccesState::en_loadStandby)
	{
		//�������Ȃ�
		return;
	}
	//���[�h�t���O���I�����Ă��Ȃ���
	m_loadCompletionFlag = false;

	//�t�F�[�h�A�E�g��ݒ�
	m_loadTypeState[LoadOrder::en_FadeOut] = loadType.m_fadeOutLoad;
	//�t�F�[�h�C����ݒ�
	m_loadTypeState[LoadOrder::en_FadeIn] = loadType.m_fadeInLoad;
	//�������[�h��ނ������t�F�[�h����Ȃ�������
	if (m_loadTypeState[LoadOrder::en_FadeOut] != LoadTypeState::en_loadImmediately)
	{
		//�����I����̃v���Z�X�X�e�[�g���t�F�[�h���s����
		m_loadProccesState = LoadProccesState::en_loadExecutionFadeOut;
	}
	//�������[�h��ނ������t�F�[�h��������
	else
	{
		//�����I����̃v���Z�X�X�e�[�g���Ó]�ҋ@��
		m_loadProccesState = LoadProccesState::en_loadBlackoutStandby;
	}
	//�C�[�W���O������������
	m_loadRatio = 0.0f;
	//���[�h��ނŕ���
	switch (m_loadTypeState[LoadOrder::en_FadeOut])
	{
		//�ʏ탍�[�h
	case Load::en_loadOrdinary:
		//�ʏ탍�[�h�̃C�[�W���O���l��ݒ�
		m_loadEasingMax = ORDINARYLOAD_EASING_MIN;

		m_loadEasingMin = ORDINARYLOAD_EASING_MAX;
		//�ʏ탍�[�h�̃t�F�[�h�X�s�[�h��ݒ�
		m_loadSpeedAttenuationRate[LoadOrder::en_FadeOut]
			= ORDINARYLOAD_EASING_ATTENUATIONRATE;

		break;
		//�~�`���[�h
	case Load::en_loadCircular:
		//�~�`���[�h�̃C�[�W���O���l��ݒ�
		m_loadEasingMax = CIRCULRLOAD_EASING_MAX;

		m_loadEasingMin = CIRCULRLOAD_EASING_MIN;
		//�~�`���[�h�̃t�F�[�h�X�s�[�h��ݒ�
		m_loadSpeedAttenuationRate[LoadOrder::en_FadeOut]
			= CIRCULRLOAD_EASING_ATTENUATIONRATE_A;

		break;
	case Load::en_loadImmediately:

		m_loadDatas.SetLoadIndex(1.0f);

		return;

		break;
	default:
		break;
	}

	m_loadDatas.SetLoadIndex(0.0f);
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

	if (m_loadTypeState[LoadOrder::en_FadeIn] != LoadTypeState::en_loadImmediately)
	{
		m_loadProccesState = LoadProccesState::en_loadExecutionFadeIn;
	}
	else
	{
		m_loadProccesState = LoadProccesState::en_loadCompletion;
	}

	m_loadRatio = 0.0f;

	switch (m_loadTypeState[LoadOrder::en_FadeIn])
	{
	case Load::en_loadOrdinary:

		m_loadEasingMin = ORDINARYLOAD_EASING_MIN;

		m_loadEasingMax = ORDINARYLOAD_EASING_MAX;

		m_loadDatas.SetLoadIndex(ORDINARYLOAD_EASING_MAX);

		m_loadSpeedAttenuationRate[LoadOrder::en_FadeIn]
			= ORDINARYLOAD_EASING_ATTENUATIONRATE;

		break;
	case Load::en_loadCircular:

		m_loadEasingMin = CIRCULRLOAD_EASING_MAX;

		m_loadEasingMax = CIRCULRLOAD_EASING_MIN;

		m_loadDatas.SetLoadIndex(CIRCULRLOAD_EASING_MAX);

		m_loadSpeedAttenuationRate[LoadOrder::en_FadeIn]
			= CIRCULRLOAD_EASING_ATTENUATIONRATE_B;

		break;
	case Load::en_loadImmediately:

		m_loadDatas.SetLoadIndex(0.0f);

		break;
	default:
		break;
	}
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

	m_loadOptionSpriteLarge.Init("Assets/modelData/load/load_object_2.DDS",
		LOADOPTION_SPRITE_W_SIZE,
		LOADOPTION_SPRITE_H_SIZE);

	m_loadOptionSpriteLarge.SetPivot({ 0.5f,0.5f });

	m_loadOptionSpriteLarge.SetPosition(LOADOPTION_SPRITE_POSITION);

	m_loadOptionSpriteLarge.Update();

	m_loadOptionSpriteSmall.Init("Assets/modelData/load/load_object_2.DDS",
		LOADOPTION_SPRITE_W_SIZE,
		LOADOPTION_SPRITE_H_SIZE);

	m_loadOptionSpriteSmall.SetPivot({ 0.5f,0.5f });

	m_loadOptionSpriteSmall.SetPosition(LOADOPTION_SPRITE_POSITION);

	m_loadOptionSpriteSmall.SetScale({ 0.5f,0.5f,0.0f });

	m_loadOptionSpriteSmall.Update();

	return true;
}

//�A�b�v�f�[�g�֐�
void Load::Update()
{
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

	LoadOptionSpriteUpdate();

	m_loadBackSideSprite.Update();

	if (m_loadProccesState == LoadProccesState::en_loadBlackoutStandby)
	{
		m_loadOptionSpriteLarge.Update();

		m_loadOptionSpriteSmall.Update();
	}
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
		m_loadDatas.SetLoadTypeState(m_loadTypeState[LoadOrder::en_FadeOut]);

		break;
	case Load::en_loadCompletion:

		m_loadCompletionFlag = true;

		m_loadProccesState = LoadProccesState::en_loadStandby;

		break;
	default:
		break;
	}

}

const float& Load::LoadCalc(const float& index)
{
	m_loadRatio += g_gameTime->GetFrameDeltaTime() * index;

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

void Load::LoadOptionSpriteUpdate()
{
	if (m_loadProccesState != LoadProccesState::en_loadBlackoutStandby)
	{
		return;
	}

	m_loadOptionLargeRotation.AddRotationDegZ(-10.0f);

	m_loadOptionSpriteLarge.SetRotation(m_loadOptionLargeRotation);

	m_loadOptionSmallRotation.AddRotationDegZ(10.0f);

	m_loadOptionSpriteSmall.SetRotation(m_loadOptionSmallRotation);
}

//�����_�[�֐�
void Load::Render(RenderContext& rc)
{
	m_loadBackSideSprite.Draw(rc);

	if (m_loadProccesState == LoadProccesState::en_loadBlackoutStandby)
	{
		m_loadOptionSpriteLarge.Draw(rc);

		m_loadOptionSpriteSmall.Draw(rc);
	}
}