#pragma once

class GameWindow;
class GameSound;

//�萔��
namespace {

	static const int MAX_TEXTDATALIST_EXP = 8;

	static const int MAX_TEXT_SIZE = 256;

	static const Vector3 TEXT_FIXED_POS = { -850.0f,400.0f,0.0f };

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
		const wchar_t* menuName,
		const wchar_t* menuText,
		const MenuFunction& menuFunc
	)
	{

		for (int listNo = 0;
			listNo < MAX_TEXTDATALIST_EXP;
			listNo++)
		{

			if (m_menuDatas[listNo].m_isUse == false)
			{
				m_menuDatas[listNo].m_isUse = true;

				m_menuDatas[listNo].m_textPos = TEXT_FIXED_POS;

				m_menuDatas[listNo].m_textPos.y -= 100 * listNo;

				//������text��m_externalInputFontList�ɃR�s�[
				swprintf_s(m_menuDatas[listNo].m_externalInputTextList, menuText);

				//���j���[�̖��O��ݒ�
				swprintf_s(m_menuDatas[listNo].m_menuName, menuName);

				//�֐���ݒ�
				m_menuDatas->SetMenuFunction(menuFunc);

				break;
			}

		}
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
		MenuFunction m_menuFunction;
		/// <summary>
		/// ���j���[���ʎq
		/// </summary>
		wchar_t m_menuName[MAX_TEXT_SIZE] = {};
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
	public:
		/// <summary>
		/// �֐����Z�b�g
		/// </summary>
		/// <param name="func"></param>
		void SetMenuFunction(const MenuFunction& func)
		{
			m_menuFunction = func;
		}
	};
	/// <summary>
	/// �\���̕ϐ�
	/// </summary>
	MenuDatas m_menuDatas[MAX_TEXTDATALIST_EXP];
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
	/// �X�e�[�g�X�V
	/// </summary>
	void MenuStateUpdate();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �Q�[���T�E���h�̃C���X�^���X
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// �Q�[���E�B���h�E�̃C���X�^���X
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
};

