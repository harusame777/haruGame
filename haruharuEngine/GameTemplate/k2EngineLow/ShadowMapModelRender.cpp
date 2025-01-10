#include "k2EngineLowPreCompile.h"
#include "ShadowMapModelRender.h"

namespace nsK2EngineLow {

	//�R���X�g���N�^
	ShadowMapModelRender::ShadowMapModelRender()
	{

	}

	//�f�X�g���N�^
	ShadowMapModelRender::~ShadowMapModelRender()
	{
		
	}

	void ShadowMapModelRender::InitShadowMapModelRender(
		const char* tkmfilePath,
		EnModelUpAxis enModelUpAxis
	)
	{
		ModelInitData initData;
		initData.m_tkmFilePath = tkmfilePath;
		initData.m_modelUpAxis = enModelUpAxis;

		if (m_animationClips != nullptr)
		{
			//�X�P���g���w��
			initData.m_skeleton = &m_skeleton;
		}

		initData.m_fxFilePath = "Assets/shader/haruharuDrawDeaphShadowMap.fx";

		ShadowMapParam shadowMapParam;
		shadowMapParam.mLVP = m_light.m_directionalLight[0].GetLightVP();
		shadowMapParam.ligPos = m_light.m_directionalLight[0].GetVPCamPosition();

		initData.m_expandConstantBuffer = (void*)&shadowMapParam;
		initData.m_expandConstantBufferSize = sizeof(shadowMapParam);

		initData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32_FLOAT;/*�f�v�X�V���h�E�p�̐ݒ�*/

		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		initData.m_vsEntryPointFunc = "VSMain";
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		m_shadowMapModel.Init(initData);

		m_shadowMapModel.UpdateWorldMatrix(
			m_position,
			m_rotation,
			m_scale
		);
	}

}