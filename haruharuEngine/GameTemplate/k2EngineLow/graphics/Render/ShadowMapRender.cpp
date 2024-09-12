#include "k2EngineLowPreCompile.h"
#include "ShadowMapRender.h"

namespace nsK2EngineLow {

	//����������
	void ShadowMapRender::Init()
	{
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };

		//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g���쐬
		m_shadowMap.Create(
			1024,
			1024,
			1,
			1,
			//DXGI_FORMAT_R32_FLOAT,�f�v�X�V���h�E�p�̐ݒ�
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	//�V���h�E�}�b�v�`��
	void ShadowMapRender::RenderShadowMap(
		RenderContext& renderContext,
		std::vector<IRenderer*>& renderObjects
	)
	{
		//�V���h�E�}�b�v�p�����_�����O�^�[�Q�b�g���g�p�\�ɂȂ�܂őҋ@
		renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		//�����_�����O�^�[�Q�b�g���V���h�E�}�b�v�ɕύX
		renderContext.SetRenderTargetAndViewport(m_shadowMap);
		//�����_�����O�^�[�Q�b�g���N���A
		renderContext.ClearRenderTargetView(m_shadowMap);

		Camera lightCamera;

		lightCamera.SetAspectOneFlag(true);

		lightCamera.SetViewAngle(Math::DegToRad(80.0f));

		//�J�����̈ʒu��ݒ�B(���C�g����l����K�v������̂Ń��C�g�Ɠ����ʒu)
		lightCamera.SetPosition(-2000, 2000, 2000);

		//�J�����̒����_��ݒ�B(���̕���)
		lightCamera.SetTarget(0.0f, 0.0f, 0.0f);

		// �������ݒ�B����̓��C�g���^���������Ă���̂ŁAX��������ɂ��Ă���
		//lightCamera.SetUp(1, 0, 0);

		//���C�g�r���[�v���W�F�N�V����
		lightCamera.Update();

		for (auto& renderObj : renderObjects)
		{
			renderObj->OnRenderShadowMap(renderContext, lightCamera.GetViewProjectionMatrix());
		}

		renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
	}
}