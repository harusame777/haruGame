#pragma once

class GameWindow;
class GameSound;

//�萔��
namespace GameMenuNS_H{

	static const int MAX_TEXTDATALIST_EXP = 8;

	static const int MAX_TEXT_SIZE = 256;

	static const Vector3 TEXT_FIXED_POS = { -200.0f,400.0f,0.0f };

}

class GameMenu : public IGameObject
{
public:
	enum GameMenuState
	{
		//�ҋ@
		en_standby,
		//�E�B���h�E���J��
		en_windowOpen,
		//�����\��
		en_textDraw,
		//���j���[�I��
		en_menuSelection,
		//�E�B���h�E�N���[�Y
		en_windowClose,
		//���j���[���鎞�̊֐����N��
		en_closeMenuFuntionGo,
		//���肵�����j���[�̊֐����N��
		en_selectionMenuFunctionGo,
		//�I��
		en_end
	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameMenu() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameMenu() {};
	/// <summary>
	/// ������`�A�֐����ꕨ
	/// </summary>
	using MenuFunction = std::function<bool()>;
	/// <summary>
	/// ���j���[�쐬
	/// </summary>
	/// <param name="func"></param>
	void InitMenuDatas(
		const wchar_t* menuText,
		const MenuFunction& menuFunc
	)
	{

		for (int listNo = 0;
			listNo < GameMenuNS_H::MAX_TEXTDATALIST_EXP;
			listNo++)
		{

			if (m_menuDatas[listNo].m_isUse == false)
			{
				m_menuDatas[listNo].m_isUse = true;

				m_menuDatas[listNo].m_textPos = GameMenuNS_H::TEXT_FIXED_POS;

				m_menuDatas[listNo].m_textPos.y -= 100 * listNo;

				//������text��m_externalInputFontList�ɃR�s�[
				swprintf_s(m_menuDatas[listNo].m_externalInputTextList, menuText);

				//�֐���ݒ�
				m_menuDatas[listNo].SetMenuFunction(menuFunc);

				//���j���[�̍ő吔���L�^
				m_maxMenuNum++;

				break;
			}

		}
	}
	/// <summary>
	/// ���j���[���鎞�Ɏ��s����֐�
	/// </summary>
	void InitMenuEndFunc(const MenuFunction& menuFunc)
	{
		m_isInitCloseFunc = true;

		m_menuCloseFunction = menuFunc;
	}
	/// <summary>
	/// ���j���[���J���ċN������
	/// </summary>
	void GoMenuOpen();
	/// <summary>
	/// �X�e�[�g�ύX
	/// </summary>
	/// <param name="changeState"></param>
	void StateChange(const GameMenuState changeState)
	{
		m_gameMenuState = changeState;
	}
	/// <summary>
	/// �C���t�H���[�V�������N�������ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsMenuOpenNow()const
	{
		if (m_gameMenuState != GameMenuState::en_standby)
		{
			return true;
		}

		return false;
	}
	/// <summary>
	/// �C���t�H���[�V�������܂肾��������true
	/// </summary>
	/// <returns></returns>
	bool IsMenuCloseing()const
	{
		return m_isMenuClose;
	}
private:
	/// <summary>
	/// �Q�[�����j���[�̃X�e�[�g
	/// </summary>
	GameMenuState m_gameMenuState = GameMenuState::en_standby;
	/// <summary>
	/// ���j���[�̃f�[�^�̍\����
	/// </summary>
	struct MenuDatas
	{
	public:
		/// <summary>
		/// �t�H���g�����_�[
		/// </summary>
		FontRender m_fontRender;
		/// <summary>
		/// ���j���[���s�֐����ꕨ
		/// </summary>
		MenuFunction m_menuBootFunction;
		/// <summary>
		/// �O�����͕����z��
		/// </summary>
		wchar_t m_externalInputTextList[GameMenuNS_H::MAX_TEXT_SIZE] = {};
		/// <summary>
		/// ���C���t�H���g�̔z��
		/// </summary>
		wchar_t m_displayTextList[GameMenuNS_H::MAX_TEXT_SIZE] = {};
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
		/// <summary>
		/// �Z���N�g���ɕ\�����邩���Ȃ���
		/// </summary>
		bool m_isTextSelectionDraw = false;
	public:
		/// <summary>
		/// �֐����Z�b�g
		/// </summary>
		/// <param name="func"></param>
		void SetMenuFunction(const MenuFunction& func)
		{
			m_menuBootFunction = func;
		}
	};
	/// <summary>
	/// �\���̕ϐ�
	/// </summary>
	MenuDatas m_menuDatas[GameMenuNS_H::MAX_TEXTDATALIST_EXP];
	/// <summary>
	/// ���j���[�I�������s�֐�
	/// </summary>
	MenuFunction m_menuCloseFunction;
	/// <summary>
	/// ���j���[�I�������s�֐�������������Ă��邩�ǂ���
	/// </summary>
	bool m_isInitCloseFunc = false;
	/// <summary>
	/// �֐����N�����邩�ǂ���
	/// </summary>
	bool m_isFuncBoot = false;
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
	/// �����`��X�V
	/// </summary>
	void TextDrawUpdate();
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
	/// ���݂̕����\����
	/// </summary>
	int m_nowTextNum = 0;
	/// <summary>
	/// �����\���x��
	/// </summary>
	float m_textDelayTime = 0.0f;
	/// <summary>
	/// textDataList�̐ݒ肳��Ă��Ȃ��v�f�ԍ�
	/// </summary>
	int m_listEndNum = 0;
	/// <summary>
	/// ���݂�textDataList�̗v�f�ԍ�
	/// </summary>
	int m_listNowNum = 0;
	/// <summary>
	/// ���j���[�Z���N�g�A�b�v�f�[�g
	/// </summary>
	void MenuSelectionUpdate();
	/// <summary>
	/// �����I�����̍X�V
	/// </summary>
	void TextSelectionUpdate();
	/// <summary>
	/// �X�e�[�g�X�V
	/// </summary>
	void MenuStateUpdate();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �����j���[�I�����Ă���ԍ�
	/// </summary>
	int m_nowMenuSelectionNum = 0;
	/// <summary>
	/// ���j���[�̍ő吔
	/// </summary>
	int m_maxMenuNum = -1;
	/// <summary>
	/// �ǂ̃��j���[���N�����邩���m�肷��
	/// </summary>
	int m_confirmedMenuSelectionNum = -1;
	/// <summary>
	/// �}�E�X�J�[�\���X�v���C�g�̍X�V
	/// </summary>
	void MouseCursorSpriteUpdate();
	/// <summary>
	/// �}�E�X�J�[�\��
	/// </summary>
	SpriteRender m_mouseCursor;
	/// <summary>
	/// �}�E�X�J�[�\����`�悷�邩
	/// </summary>
	bool m_isMouseCorsorDraw = false;
	/// <summary>
	/// ���j���[���܂��Ă��邩�ǂ���
	/// </summary>
	bool m_isMenuClose = false;
	/// <summary>
	/// ������
	/// </summary>
	void InitMenuDetasList();
	/// <summary>
	/// �Q�[���T�E���h�̃C���X�^���X
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// �Q�[���E�B���h�E�̃C���X�^���X
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
};

