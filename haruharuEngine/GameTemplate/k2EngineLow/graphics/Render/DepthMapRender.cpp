#include "k2EngineLowPreCompile.h"
#include "DepthMapRender.h"

namespace nsK2EngineLow {

	void DepthMapRender::Init(RenderTarget& rt)
	{
		//�t���[���o�b�t�@�[�̉����A�������擾
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();

		//�V�[���̃J������Ԃł�Z�l���������ރ����_�����O�^�[�Q�b�g���쐬
		m_depthMap.Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);

		m_depthMapModelGaussianBlur.Init(
			&rt.GetRenderTargetTexture()
		);

		//�{�P�摜�����p�̃X�v���C�g������������
		SpriteInitData combineBokeImageSpriteInitData;

		//�g�p����e�N�X�`���͓�
		//�������̓K�E�V�A���u���[
		combineBokeImageSpriteInitData.m_textures[0] 
			= &m_depthMapModelGaussianBlur.GetBokeTexture();
		//�������̓f�v�X
		combineBokeImageSpriteInitData.m_textures[1]
			= &m_depthMap.GetRenderTargetTexture();

		//�������w��
		combineBokeImageSpriteInitData.m_width = frameBuffer_w;
		combineBokeImageSpriteInitData.m_height = frameBuffer_h;

		//�����p�̃V�F�[�_�[���w�肷��
		combineBokeImageSpriteInitData.m_fxFilePath 
			= "Assets/shader/haruharuDepthMapPostEffect.fx";
		combineBokeImageSpriteInitData.m_colorBufferFormat[0] 
			= DXGI_FORMAT_R32G32B32A32_FLOAT;

		//�����𗘗p���ă{�P�摜���A���t�@�u�����f�B���O����̂ŁA�������������[�h�ɂ���
		combineBokeImageSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

		//�������I�u�W�F�N�g�𗘗p���ăX�v���C�g������������
		m_depthCombineBokeImageSprite.Init(combineBokeImageSpriteInitData);

		//�}���`�����_�����O�^�[�Q�b�g������
		m_depthMapMRT[0] = &rt;
		m_depthMapMRT[1] = &m_depthMap;
	} 

	//�P�x���o
	void DepthMapRender::DepthExtraction(RenderContext& rc, std::vector<IRenderer*>& renderObjects)
	{

		//�g�p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTargets(MAX_MRT, m_depthMapMRT);

		//�����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetsAndViewport(MAX_MRT, m_depthMapMRT);

		//�����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetViews(MAX_MRT, m_depthMapMRT);

		for (auto& renderObj : renderObjects)
		{
			renderObj->OnRenderModel(rc);
		}

		rc.WaitUntilFinishDrawingToRenderTargets(MAX_MRT, m_depthMapMRT);

		m_depthMapModelGaussianBlur.ExecuteOnGPU(rc, 5);
	}

}