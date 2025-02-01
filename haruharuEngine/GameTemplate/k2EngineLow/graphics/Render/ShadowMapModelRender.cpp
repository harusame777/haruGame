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

	const Model& ShadowMapModelRender::InitShadowMapModelRender(
		const char* tkmfilePath,
		EnModelUpAxis enModelUpAxis,
		AnimationClip* animationClips,
		const Light& ligPtr 
	)
	{
		//�X�P���g���̃f�[�^��ǂݍ��݁B
		std::string skeletonFilePath = tkmfilePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());

		ModelInitData initData;
		initData.m_tkmFilePath = tkmfilePath;
		initData.m_modelUpAxis = enModelUpAxis;

		if (animationClips != nullptr)
		{
			//�X�P���g���w��
			initData.m_skeleton = &m_skeleton;
		}

		initData.m_fxFilePath = "Assets/shader/haruharuDrawShadowMap.fx";

		ShadowMapParam shadowMapParam;
		shadowMapParam.mLVP = ligPtr.m_directionalLight[0].GetLightVP();
		shadowMapParam.ligPos = ligPtr.m_directionalLight[0].GetVPCamPosition();

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

		return m_shadowMapModel;
	}

}