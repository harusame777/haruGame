#include "k2EngineLowPreCompile.h"
#include "ShadowMapRender.h"
#include "graphics/light/SceneLight.h"

namespace nsK2EngineLow {


	//����������
	void ShadowMapRender::Init()
	{
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };


		//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g���쐬
		//�߉e�p�̃V���h�E�}�b�v
		m_shadowMap[0].Create(
			2048,
			2048,
			1,
			1,
			//DXGI_FORMAT_R32_FLOAT,�f�v�X�V���h�E�p�̐ݒ�
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);

		//���e�p
		m_shadowMap[1].Create(
			1024,
			1024,
			1,
			1,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);

		//���e�p
		m_shadowMap[2].Create(
			512,
			512,
			1,
			1,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
		
		for (int No = 0; No < NUM_SHADOW_MAP; No++)
		{
			m_shadowMapModelGaussianBlur[No].Init(
				&m_shadowMap[No].GetRenderTargetTexture()
			);
		}

	}

	//�V���h�E�}�b�v�`��
	void ShadowMapRender::RenderShadowMap(
		RenderContext& renderContext,
		std::vector<IRenderer*>& renderObjects
	)
	{
		//�J�����̊e����v�Z
		//�J�����̃r���[�v���W�F�N�V�������擾����
		const auto& lvpMatrix = g_sceneLight->m_light.m_directionalLight[0].GetLightVP();
		//�O�����Ɖ������͂��łɌv�Z�ς݂Ȃ̂ŁA��������������Ă���
		const auto& cameraForward = g_camera3D->GetForward();
		const auto& cameraRight = g_camera3D->GetForward();

		//�J�����̏�����͑O�����ƉE�����̊O�ςŋ��߂�
		Vector3 cameraUp;
		cameraUp.Cross(cameraForward, cameraRight);

		// nearDepth�̓G���A�̍ŏ��[�x�l��\��
		// ��ԋ߂��G���A�̍ŏ��[�x�l�̓J�����̃j�A�N���b�v
		float nearDepth = g_camera3D->GetNear();
		for (int areaNo = 0; areaNo < NUM_SHADOW_MAP; areaNo++)
		{
			// �G���A�̋ߕ��ʂ̒��S����̏�ʁA���ʂ܂ł̋��������߂�
			float nearY = tanf(g_camera3D->GetViewAngle() * 0.5f) * nearDepth;

			// �G���A�̋ߕ��ʂ̒��S����̉E�ʁA���ʂ܂ł̋��������߂�
			float nearX = nearY * g_camera3D->GetAspect();

			// �G���A�̉����ʂ̒��S����̏�ʁA���ʂ܂ł̋��������߂�
			float farY = tanf(g_camera3D->GetViewAngle() * 0.5f) * cascadeAreaTbl[areaNo];

			// �G���A�̉����ʂ̒��S����̉E�ʁA���ʂ܂ł̋��������߂�
			float farX = farY * g_camera3D->GetAspect();

			// �G���A�̋ߕ��ʂ̒��S���W�����߂�
			Vector3 nearPos = g_camera3D->GetPosition() + cameraForward * nearDepth;

			// �G���A�̉����ʂ̒��S���W�����߂�
			Vector3 farPos = g_camera3D->GetPosition() + cameraForward * cascadeAreaTbl[areaNo];

			//8���_�����߂�
			Vector3 vertex[8];

			// �ߕ��ʂ̉E��̒��_
			vertex[0] += nearPos + cameraUp * nearY + cameraRight * nearX;

			// �ߕ��ʂ̍���̒��_
			vertex[1] += nearPos + cameraUp * nearY + cameraRight * -nearX;

			// �ߕ��ʂ̉E���̒��_
			vertex[2] += nearPos + cameraUp * -nearY + cameraRight * nearX;

			// �ߕ��ʂ̍����̒��_
			vertex[3] += nearPos + cameraUp * -nearY + cameraRight * -nearX;

			// �����ʂ̉E��̒��_
			vertex[4] += farPos + cameraUp * farY + cameraRight * farX;

			// �����ʂ̍���̒��_
			vertex[5] += farPos + cameraUp * farY + cameraRight * -farX;

			// �����ʂ̉E���̒��_
			vertex[6] += farPos + cameraUp * -farY + cameraRight * farX;

			// �����ʂ̍����̒��_
			vertex[7] += farPos + cameraUp * -farY + cameraRight * -farX;

			//���_��ϊ����čő�l�A�ŏ��l�����߂�
			Vector3 vMax, vMin;
			vMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
			vMin = { FLT_MAX,  FLT_MAX,  FLT_MAX };
			for (auto& v : vertex)
			{
				lvpMatrix.Apply(v);
				vMax.Max(v);
				vMin.Min(v);
			}

			//�N���b�v�s������߂�
			float xScale = 2.0f / (vMax.x - vMin.x);
			float yScale = 2.0f / (vMax.y - vMin.y);
			float xOffset = (vMax.x + vMin.x) * -0.5f * xScale;
			float yOffset = (vMax.y + vMin.y) * -0.5f * yScale;
			Matrix clopMatrix;
			clopMatrix.m[0][0] = xScale;
			clopMatrix.m[1][1] = yScale;
			clopMatrix.m[3][0] = xOffset;
			clopMatrix.m[3][1] = yOffset;

			//���C�g�r���[�v���W�F�N�V�����s��ɃN���b�v�s�����Z����
			g_sceneLight->m_light.m_lvpcMatrix[areaNo] = lvpMatrix * clopMatrix;

			//�V���h�E�}�b�v�p�����_�����O�^�[�Q�b�g���g�p�\�ɂȂ�܂őҋ@
			renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap[areaNo]);
			//�����_�����O�^�[�Q�b�g���V���h�E�}�b�v�ɕύX
			renderContext.SetRenderTargetAndViewport(m_shadowMap[areaNo]);
			//�����_�����O�^�[�Q�b�g���N���A
			renderContext.ClearRenderTargetView(m_shadowMap[areaNo]);

			//�e���f���`��
			for (auto& renderObj : renderObjects)
			{
				renderObj->OnRenderShadowMap(renderContext);
			}

			//�������ݏI���҂�
			renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap[areaNo]);
			//�V���h�E�}�b�v�Ƀu���[������
			ShadouMapBlurExecute(renderContext,areaNo);

			//���̃G���A�̋ߕ��ʂ܂ł̋�����������
			nearDepth = cascadeAreaTbl[areaNo];
		}


		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
	}
}