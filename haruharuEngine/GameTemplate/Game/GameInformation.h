#pragma once
#include "GameWindow.h"

class GameWindow;

class GameInformation : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameInformation(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameInformation(){}
	/// <summary>
	/// �N���֐�
	/// </summary>
	/// <param name="text"></param>
	void InitAndGoInformation(const wchar_t* text)
	{
		if (m_gameInformationState != GameInformationState::en_standby)
		{
			return;
		}
		//�E�B���h�E���J����
		m_gameWindow->WindowOpen();
		//������text��m_externalInputFontList�ɃR�s�[
		swprintf_s(m_externalInputTextList, text);
		//�X�e�[�g��windowOpen�ɕύX
		StateChange(GameInformationState::en_windowOpen);
	}

private:
	/// <summary>
	/// ��i���̕����z��̃f�[�^
	/// </summary>
	struct TextOneParagraphData
	{

	};

	/// <summary>
	/// �C���t�H���[�V�����X�e�[�g
	/// </summary>
	enum GameInformationState
	{
		//�ҋ@
		en_standby,
		//�E�B���h�E�I�[�v��
		en_windowOpen,
		//�����\��
		en_textDraw,
		//�J������Ԃőҋ@
		en_openWait,
		//�E�B���h�E�N���[�Y
		en_windowClose,
	};
	/// <summary>
	/// �C���t�H���[�V�����X�e�[�g�ϐ�
	/// </summary>
	GameInformationState m_gameInformationState = GameInformationState::en_standby;
	/// <summary>
	/// �X�e�[�g�ύX
	/// </summary>
	/// <param name="changeState"></param>
	void StateChange(const GameInformationState changeState)
	{
		m_gameInformationState = changeState;
	}
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update(); 
	/// <summary>
	/// �C���t�H���[�V�����X�e�[�g�A�b�v�f�[�g
	/// </summary>
	void InformationStateUpdate();
	/// <summary>
	/// �x���֐�
	/// </summary>
	/// <returns></returns>
	bool Delay(const float delayTime);
	/// <summary>
	/// �\�������X�V
	/// </summary>
	void DisplayTextUpdate();
	/// <summary>
	/// �\�������z��X�V
	/// </summary>
	void DisplayTextListUpdate();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �E�B���h�E�̃C���X�^���X
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
	/// <summary>
	/// �t�H���g�����_�[
	/// </summary>
	FontRender m_mainFontRender;
	/// <summary>
	/// �O�����͕����z��
	/// </summary>
	wchar_t m_externalInputTextList[256] = {};
	/// <summary>
	/// ���C���t�H���g�̔z��
	/// </summary>
	wchar_t m_displayTextList[256] = {};
	/// <summary>
	/// ���݂̕����\����
	/// </summary>
	int m_nowTextNum = 0;
	/// <summary>
	/// �����\���x��
	/// </summary>
	float m_textDelayTime = 0.0f;
};

