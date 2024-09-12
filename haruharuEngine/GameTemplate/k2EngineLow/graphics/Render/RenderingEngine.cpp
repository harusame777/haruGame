#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	//�R���X�g���N�^
	RenderingEngine::RenderingEngine()
	{

	}

	//�f�X�g���N�^
	RenderingEngine::~RenderingEngine()
	{

	}

	//�o�^����
	void RenderingEngine::Init()
	{
		//�t���[���o�b�t�@�[�̉����A�������擾
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();

		//���C�������_�����O�^�[�Q�b�g
		mainRenderTargert.Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//�e�N�X�`���𒣂�t���邽�߂̃X�v���C�g��������
		//�������I�u�W�F�N�g���쐬
		SpriteInitData spriteInitData;

		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
		spriteInitData.m_textures[0] = &mainRenderTargert.GetRenderTargetTexture();
		spriteInitData.m_width = frameBuffer_w;
		spriteInitData.m_height = frameBuffer_h;

		//�X�v���C�g�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		spriteInitData.m_fxFilePath = "Assets/shader/haruharuSprite.fx";

		//�������I�u�W�F�N�g���g�p���ăX�v���C�g��������
		m_copyToFrameBufferSprite.Init(spriteInitData);

		//GBuffer�̏�����
		//m_gBufferRender.Init();
		//�P�x���o������
		m_luminnceRender.Init(&mainRenderTargert);
		//�V���h�E�}�b�v�̏�����
		m_shadowMapRender.Init();
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		//�V���h�E�}�b�v�`�揈��
		m_shadowMapRender.RenderShadowMap(
			rc,
			m_renderObjects
		);

		//G-Buffer�ւ̃����_�����O
		//m_gBufferRender.RenderGBuffer(
		//	rc,
		//	m_renderObjects
		//);

		//�����_�����O�^�[�Q�b�g�����C�������_�����O�^�[�Q�b�g�ɕύX
		renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTargert);

		//�����_�����O�^�[�Q�b�g��ݒ�
		renderContext.SetRenderTargetAndViewport(mainRenderTargert);

		//�����_�����O�^�[�Q�b�g���N���A
		renderContext.ClearRenderTargetView(mainRenderTargert);

		Render3DModel(rc);

		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTargert);

		//�R�R����P�x���o
		m_luminnceRender.LuminnceExtraction(rc);

		Render2DSprite(rc);

		// �o�^����Ă���`��I�u�W�F�N�g���N���A
		m_renderObjects.clear();
	}

	//3D���f���`�揈��
	void RenderingEngine::Render3DModel(RenderContext& rc)
	{
		for (auto& renderObj : m_renderObjects)
		{
			renderObj->OnRenderModel(rc);
		}
	}

	//2D�`�揈��
	void RenderingEngine::Render2DSprite(RenderContext& rc)
	{
		for (auto& renderObj : m_renderObjects)
		{
			renderObj->OnRender2D(rc);
		}
	}

}