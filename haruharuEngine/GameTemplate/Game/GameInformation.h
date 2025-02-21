#pragma once
#include "GameWindow.h"

class GameWindow;
class GameSound;

//�萔��
namespace {

	static const int MAX_TEXTDATALIST_EXP = 8;

	static const int MAX_TEXT_SIZE = 256;

	static const Vector3 TEXT_FIXED_POS = { -850.0f,400.0f,0.0f };

}

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
	///	�e�L�X�g���C���t�H���[�V�����ɐݒ�
	/// </summary>
	/// <param name="text"></param>
	void InitTextData(const wchar_t* text)
	{
		if (m_gameInformationState != GameInformationState::en_standby)
		{
			return;
		}

		for (int listNo = 0;
			listNo < MAX_TEXTDATALIST_EXP;
			listNo++)
		{

			if (m_textDataList[listNo].m_isUse == false)
			{
				m_textDataList[listNo].m_isUse = true;

				m_textDataList[listNo].m_textPos = TEXT_FIXED_POS;

				m_textDataList[listNo].m_textPos.y -= 100 * listNo;

				//������text��m_externalInputFontList�ɃR�s�[
				swprintf_s(m_textDataList[listNo].m_externalInputTextList, text);

				break;
			}

		}
	}
	/// <summary>
	/// �N���֐�
	/// </summary>
	/// <param name="text"></param>
	void GoInformation();
	/// <summary>
	/// �C���t�H���[�V�������N�������ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsInformationNow()const 
	{
		if (m_gameInformationState != GameInformationState::en_standby)
		{
			return true;
		}

		return false;
	}
	/// <summary>
	/// �C���t�H���[�V�������܂肾��������true
	/// </summary>
	/// <returns></returns>
	bool IsInformationCloseing()const
	{
		return m_isInformationCloseing;
	}
private:
	/// <summary>
	/// ��i���̕����z��̃f�[�^
	/// </summary>
	struct TextOneParagraphData
	{
	public:
		/// <summary>
		/// �t�H���g�����_�[
		/// </summary>
		FontRender m_mainFontRender;
		/// <summary>
		/// �O�����͕����z��
		/// </summary>
		wchar_t m_externalInputTextList[MAX_TEXT_SIZE] = {};
		/// <summary>
		/// ���C���t�H���g�̔z��
		/// </summary>
		wchar_t m_displayTextList[MAX_TEXT_SIZE] = {};
		/// <summary>
		/// ���̃R���e�i���g�p�����ǂ���
		/// </summary>
		bool m_isUse = false;
		/// <summary>
		/// ���̒i���̃e�L�X�g���o�͂��I�������
		/// </summary>
		bool m_isOneParagrapgTextEnd = false;
		/// <summary>
		/// �e�L�X�g�̈ʒu
		/// </summary>
		Vector3 m_textPos = Vector3::Zero;
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
		//�I������
		en_end
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
	/// ���݂̕����\����
	/// </summary>
	int m_nowTextNum = 0;
	/// <summary>
	/// �����\���x��
	/// </summary>
	float m_textDelayTime = 0.0f;
	/// <summary>
	/// �e�L�X�g�f�[�^�̔z��
	/// </summary>
	TextOneParagraphData m_textDataList[MAX_TEXTDATALIST_EXP];
	/// <summary>
	/// textDataList�̐ݒ肳��Ă��Ȃ��v�f�ԍ�
	/// </summary>
	int m_listEndNum = 0;
	/// <summary>
	/// ���݂�textDataList�̗v�f�ԍ�
	/// </summary>
	int m_listNowNum = 0;
	/// <summary>
	/// �C���t�H���[�V�������܂肾������
	/// </summary>
	bool m_isInformationCloseing = false;
	/// <summary>
	/// ����e�L�X�g
	/// </summary>
	FontRender m_closeButtonText;
	/// <summary>
	/// ����e�L�X�g��`�悷��t���O
	/// </summary>
	bool m_closeButtonTextDrawFlag = false;
	/// <summary>
	/// �E�B���h�E�̃C���X�^���X
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
	/// <summary>
	/// �Q�[���T�E���h�̃C���X�^���X
	/// </summary>
	GameSound* m_gameSound = nullptr;
};

