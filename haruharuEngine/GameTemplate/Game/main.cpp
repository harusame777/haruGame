#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
//�ŏ��͌���k2�G���W���ƌ���ׂĂ���Ȃ������𑫂��Ă݂悤�I

// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g�B
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// �Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	
	// k2EngineLow�̏������B
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 100.0f, -200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });

	//�ǉ��R�[�h
	//�����_�����O�G���W����������
	RenderingEngine m_renderingEngine;
	m_renderingEngine.Init();
	g_renderingEngine = &m_renderingEngine;

	//�V�[�����C�g�̏�����
	SceneLight m_sceneLight;
	m_sceneLight.Init();
	g_sceneLight = &m_sceneLight;
	
	NewGO<Game>(0,"game");

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�ǉ��R�[�h
		auto& RenderContext = g_graphicsEngine->GetRenderContext();

		// �t���[���̊J�n���ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->BeginFrame();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�������Ăяo���B
		g_k2EngineLow->ExecuteUpdate();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
		g_k2EngineLow->ExecuteRender();

		//�ǉ��R�[�h
		//���C�g�̍X�V����
		m_sceneLight.Update();

		//�����_�����O�G���W���̕`�揈��
		m_renderingEngine.Execute(RenderContext);

		// �f�o�b�O�`�揈�������s����B
		g_k2EngineLow->DebubDrawWorld();

		// �t���[���̏I�����ɌĂяo���K�v�����鏈�������s�B
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}
