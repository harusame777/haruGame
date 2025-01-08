#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"


namespace nsK2EngineLow {


	//�R���X�g���N�^
	ModelRender::ModelRender()
	{

	}

	//�f�X�g���N�^
	ModelRender::~ModelRender()
	{

	}

	//����������
	void ModelRender::Init(
		const char* tkmfilePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool isRecieveShadow
	)
	{
		//�X�P���g���̏�����
		InitSkeleton(tkmfilePath);

		//�A�j���[�V�����̏�����
		InitAnimation(animationClips, numAnimationClips);

		// GBuffer�`��p�̃��f�����������B
		// Gbuffer�͍�肩��
		//InitModelOnRenderGBuffer(*g_renderingEngine,tkmfilePath,enModelUpAxis,isRecieveShadow);

		//��{�̃��f��������
		InitNormalModel(tkmfilePath, animationClips, numAnimationClips, enModelUpAxis, isRecieveShadow);

		//�V���h�E�}�b�v�`��p���f���̏�����
		InitShadowModel(tkmfilePath, enModelUpAxis);
	}

	//GBuffer�`��p�̃��f����������
	void ModelRender::InitModelOnRenderGBuffer(
		RenderingEngine& renderingEngine,
		const char* tkmFilePath,
		EnModelUpAxis enModelUpAxis,
		bool isShadowReciever
	)
	{
		//��{���f���̏������\���̂��쐬
		ModelInitData initData;
		initData.m_fxFilePath = "";
		
	}

	//��{���f���̏�����
	void ModelRender::InitNormalModel(
		const char* tkmfilePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool isRecieveShadow
	)
	{
		//��{���f���̏������\���̂��쐬
		ModelInitData initData;

		//�t�@�C���p�X��o�^
		initData.m_tkmFilePath = tkmfilePath;

		if (isRecieveShadow)
		{
			initData.m_fxFilePath = "Assets/shader/haruharuShadowReceiverModel.fx";

			m_light = *g_sceneLight->GetLightData();

			initData.m_expandConstantBuffer = &m_light;
			initData.m_expandConstantBufferSize = sizeof(m_light);

			//�V���h�E�}�b�v���g��SRV�ɐݒ肷��
			initData.m_expandShaderResoruceView[0] = &(g_renderingEngine
				->GetShadowMapRenderTarget()->GetRenderTargetTexture());
		}
		else
		{
			//�`��V�F�[�_�[��o�^
			initData.m_fxFilePath = "Assets/shader/haruharuModel.fx";

			//���C�g�̏���o�^
			initData.m_expandConstantBuffer = g_sceneLight->GetLightData();
			initData.m_expandConstantBufferSize = sizeof(Light);


		}

		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		initData.m_vsEntryPointFunc = "VSMain";

		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		//�X�P���g��������������Ă�����
		if (m_skeleton.IsInited())
		{
			initData.m_skeleton = &m_skeleton;
		}

		//���f���̏�������
		initData.m_modelUpAxis = enModelUpAxis;

		//�쐬�����������f�[�^�����ƂɃ��f����������
		m_model.Init(initData);
	}

	//�V���h�E�}�b�v�ɕ\�����郂�f���̍쐬
	void ModelRender::InitShadowModel(const char* tkmFilePath, EnModelUpAxis modelUpAxis)
	{
		ModelInitData initData;
		initData.m_tkmFilePath = tkmFilePath;
		initData.m_modelUpAxis = modelUpAxis;

		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		//initData.m_vsEntryPointFunc = "VSMain";
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		//initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		if (m_animationClips != nullptr)
		{
			//�X�P���g���w��
			initData.m_skeleton = &m_skeleton;
		}

		initData.m_fxFilePath = "Assets/shader/haruharuDrawShadowMap.fx";

		//initData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;�f�v�X�V���h�E�p�̐ݒ�

		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		initData.m_vsEntryPointFunc = "VSMain";
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		m_shadowModel.Init(initData);
	}

	//�X�P���g���̓o�^����
	//tkm�t�@�C���̃p�X��.tkm�̕�����.tks�ɂ��ēǂݍ��ގ���
	//��������tkm�t�@�C���p�X��tks�t�@�C���p�X��������͂���K�v�������Ȃ�
	//�����tkm�t�@�C��������t�@�C����tks�t�@�C�����Ȃ��Ɠǂݍ��߂Ȃ��B
	void ModelRender::InitSkeleton(const char* tkmFilePath)
	{
		//�X�P���g���̃f�[�^��ǂݍ��݁B
		std::string skeletonFilePath = tkmFilePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	//�A�j���[�V�����̓o�^����
	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr)
		{
			m_animation.Init(
				m_skeleton,
				m_animationClips,
				numAnimationClips //����Ȃ��m_numAnimationClips����Ȃ��񂾂�
			);
		}
	}

	//���f�������_�[�̍X�V����
	void ModelRender::Update()
	{
		//���[���h�s��X�V
		m_model.UpdateWorldMatrix(m_position,m_rotation, m_scale);

		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		//�X�P���g�����������ς݂̏ꍇ�A�X�P���g���̍X�V
		if (m_skeleton.IsInited())
		{
			m_skeleton.Update(m_model.GetWorldMatrix());
		}

		//�A�j���[�V������i�߂�
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	//�`�揈��
	void ModelRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
	}

	//3D���f���̕`�揈��
	void ModelRender::OnRenderModel(RenderContext& rc)
	{
		m_model.Draw(rc);
	}

	void ModelRender::OnRenderToGBuffer(RenderContext& rc)
	{
		//����������Ă�����
		if (m_gBufferModel.IsInited()){
			//�`��
			m_gBufferModel.Draw(rc, 1);
		}
	}

	//�e�̕`�揈��
	void ModelRender::OnRenderShadowMap(RenderContext& rc)
	{
		if (m_isShadowChaster)
		{
			for(auto& dirLigPtr : m_light.m_directionalLight)
			{
				if (dirLigPtr.GetUse() == false)
				{
					continue;
				}

				m_shadowModel.Draw(
					rc,
					g_matIdentity,
					dirLigPtr.GetLightVP(),
					1
				);
			}

		}
	}
}