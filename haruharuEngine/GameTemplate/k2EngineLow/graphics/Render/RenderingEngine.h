#pragma once
#include "graphics/Render/ShadowMapRender.h"
#include "graphics/Render/GBufferRender.h"
#include "graphics/Render/LuminnceRender.h"

namespace nsK2EngineLow {
	class RenderingEngine : Noncopyable //�R�s�[�s�̃N���X
	{
	public:

		//�R���X�g���N�^
		RenderingEngine();
		//�f�X�g���N�^
		~RenderingEngine();

		void Init();

		//�`��I�u�W�F�N�g��ǉ�
		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}

		//3D���f���̕`��
		void Render3DModel(RenderContext& rc);

		//2D�`��
		void Render2DSprite(RenderContext& rc);

		//���s
		void Execute(RenderContext& rc);

		Texture& GetShadowMapRenderBokeTexture(const int listNum)
		{
			return m_shadowMapRender.GetShadowMapBokeTexture(listNum);
		}

		RenderTarget* GetShadowMapRenderTarget(const int listNum)
		{
			return m_shadowMapRender.GetShadowMapRenderTarget(listNum);
		}

	private:
		//���C�������_�����O�^�[�Q�b�g
		RenderTarget mainRenderTargert;
		//�`��I�u�W�F�N�g�̃��X�g
		std::vector<IRenderer*> m_renderObjects;
		//�V���h�E�}�b�v�����_�[
		ShadowMapRender m_shadowMapRender;
		//GBuffer�����_�[
		GBufferRender m_gBufferRender;
		//�P�x���o�����_�[
		LuminnceRender m_luminnceRender;
		//�e�N�X�`���𒣂�t���邽�߂̃X�v���C�g
		Sprite m_copyToFrameBufferSprite;
	};
}

