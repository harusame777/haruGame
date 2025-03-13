#pragma once
#include <iostream>
#include <variant>

namespace GameSettingConstant {

	static const int MAX_TEXT_NUM = 256; 

	static const int MAX_SETTING_SPRITE_DRAW_NUM = 2;

	static const float SETTING_BAR_SPRITE_W_SIZE = 1002.0f;
	static const float SETTING_BAR_SPRITE_H_SIZE = 12.0f;

	static const float SETTING_BAR_SLIDER_SPRITE_W_SIZE = 26.0f;
	static const float SETTING_BAR_SLIDER_SPRITE_H_SIZE = 117.0f;

	static const Vector3 SETTING_SPRITE_POS = { 0.0f,200.0f,0.0f };

	static const float MOUSECORSOR_SPRITE_W_SIZE = 34.0f;
	static const float MOUSECORSOR_SPRITE_H_SIZE = 38.0f;

	static const Vector4 MAINTEXT_COLOR = { 1.0f,1.0f,1.0f,1.0f };
};

class GameWindow;
class GameSound;

class GameSetting : public IGameObject
{
public:
	enum SettingState
	{
		//�ҋ@
		en_standby,
		//�E�B���h�E���J��
		en_windowOpen,
		//�ݒ�I�����֐����s
		en_settingEndFuncBoot,
		//���j���[�I��
		en_settingSelection,
		//�ݒ蒆
		en_setting,
		//�E�B���h�E�N���[�Y
		en_windowClose,
		//���j���[���鎞�̊֐����N��
		en_closeMenuFuntionGo,
		//�I��
		en_end
	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameSetting() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameSetting() {};
	/// <summary>
	/// ������`�A�֐����ꕨ
	/// </summary>
	using SettingFunction = std::function<bool(bool)>;
	/// <summary>
	/// �ݒ�쐬
	/// </summary>
	/// <param name="settingName"></param>
	/// <param name="address"></param>
	void InitSetting(
		const wchar_t* settingName,
		int& address,
		const SettingFunction& settingEndFunc
	);
	void InitSetting(
		const wchar_t* settingName,
		float& address,
		const SettingFunction& settingEndFunc
	);
	/// <summary>
	/// �ݒ胁�j���[���鎞�Ɏ��s����֐�
	/// </summary>
	void InitMenuEndFunc(const SettingFunction& menuFunc)
	{
		m_isInitCloseFunc = true;

		m_settingCloseFunction = menuFunc;
	}
	/// <summary>
	/// �ݒ胁�j���[���J��
	/// </summary>
	void GoSettingMenuOpen();
	/// <summary>
	/// �X�e�[�g�ύX
	/// </summary>
	/// <param name="changeState"></param>
	void StateChange(const SettingState changeState)
	{
		m_settingState = changeState;
	}
	/// <summary>
	/// �ݒ肪�N�������ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsSettingOpenNow()const
	{
		if (m_settingState != SettingState::en_standby)
		{
			return true;
		}

		return false;
	}
private:
	/// <summary>
	/// �ݒ�f�[�^�\����
	/// </summary>
	struct SettingDatas
	{
	private:
		/// <summary>
		/// �ݒ荀�ږ�
		/// </summary>
		wchar_t m_settingItemName[GameSettingConstant::MAX_TEXT_NUM] = {};
		/// <summary>
		/// �ݒ�l�A�h���X�ۑ��v�ϐ�
		/// </summary>
		std::variant<int*, float*> m_settingValue;
		/// <summary>
		/// �ݒ���������ɋN������֐�
		/// </summary>
		SettingFunction m_settingEndBootFunc;
	public:
		/// <summary>
		/// �Z�b�e�B���O�o�[
		/// </summary>
		SpriteRender m_settingBar;
		/// <summary>
		/// �Z�b�e�B���O�X���C�_�[
		/// </summary>
		SpriteRender m_settingSlider;
		/// <summary>
		/// �ݒ荀�ږ��`��v�t�H���g�����_�[
		/// </summary>
		FontRender m_settingItemNameFontRender;
		/// <summary>
		/// �ݒ�l�A�h���X�ۑ��v�ϐ��AInt�ۑ�
		/// </summary>
		/// <param name="valueInt"></param>
		void SetSettingAddress(int& valueInt)
		{
			m_settingValue = &valueInt;
		}
		void SetSettingAddress(float& valueInt)
		{
			m_settingValue = &valueInt;
		}
		/// <summary>
		/// �ݒ�l�ύX
		/// </summary>
		/// <param name="settingNum"></param>
		void SetSettingValue(int& valueInt)
		{
			if (auto* valuePtr = std::get_if<int*>(&m_settingValue)) {
				**valuePtr = valueInt;
			}
		}
		void SetSettingValue(float& valueInt)
		{
			if (auto* valuePtr = std::get_if<float*>(&m_settingValue)) {
				**valuePtr = valueInt;
			}
		}
		/// <summary>
		/// �A�h���X�l���擾
		/// </summary>
		/// <returns></returns>
		std::variant<int, double> GetAddressNum()
		{
			if (auto valuePtr = std::get_if<int*>(&m_settingValue)){
				return **valuePtr;
			}
			else if(auto valuePtr = std::get_if<float*>(&m_settingValue)){
				return **valuePtr;
			}
		}
		/// <summary>
		/// �ݒ薼��ݒ�
		/// </summary>
		/// <param name="settingName"></param>
		void SettingName(const wchar_t* settingName)
		{
			swprintf_s(m_settingItemName,settingName);
		}
		wchar_t* GetSettingName()
		{
			return m_settingItemName;
		}
		/// <summary>
		/// �֐���ݒ�
		/// </summary>
		/// <param name="func"></param>
		void SetSettingEndFunction(const SettingFunction& func)
		{
			m_settingEndBootFunc = func;
		}
	};
	/// <summary>
	/// �ݒ�f�[�^�\���̕ϐ�
	/// </summary>
	std::vector<SettingDatas*> m_settingDatasList;
	/// <summary>
	/// �`��ݒ�f�[�^
	/// </summary>
	struct DrawSettingData
	{
	public:
		/// <summary>
		/// �ݒ�f�[�^�A�h���X
		/// </summary>
		SettingDatas* m_settingDataAddress = nullptr;
		/// <summary>
		/// �X�v���C�g���_�ʒu
		/// </summary>
		Vector3 m_spriteOriginPos = Vector3::Zero;
		/// <summary>
		/// �X�v���C�g�t�H���g�ʒu
		/// </summary>
		Vector3 m_spriteFontPos = Vector3::Zero;
	};
	/// <summary>
	/// �`��ݒ�f�[�^�ϐ�
	/// </summary>
	DrawSettingData m_settingDrawDatasList[GameSettingConstant
		::MAX_SETTING_SPRITE_DRAW_NUM];
	/// <summary>
	/// �ݒ�X�e�[�g
	/// </summary>
	SettingState m_settingState = SettingState::en_standby;
	/// <summary>
	/// �ݒ胁�j���[�I�������s�֐�
	/// </summary>
	SettingFunction m_settingCloseFunction;
	/// <summary>
	/// ���j���[�I�������s�֐�������������Ă��邩�ǂ���
	/// </summary>
	bool m_isInitCloseFunc = false;
	/// <summary>
	/// �ݒ荀�ڐ�
	/// </summary>
	int m_settingItemNum = 0;
	/// <summary>
	/// ���ݑI�𒆂̐ݒ荀��
	/// </summary>
	int m_settingItemSelectionNum = 0;
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
	/// �ݒ�X�e�[�g�X�V
	/// </summary>
	void SettingStateUpdate();
	/// <summary>
	/// �ݒ�X�v���C�g�X�V
	/// </summary>
	void SettingSpriteUpdate();
	/// <summary>
	/// �`��f�[�^�̍X�V
	/// </summary>
	void UpdateDrawSettingData(const int initNum);
	/// <summary>
	/// �Z�b�e�B���O�I�Ԋ֐�
	/// </summary>
	void SettingSelection();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �}�E�X�J�[�\��
	/// </summary>
	SpriteRender m_mouseCursor;
	/// <summary>
	/// �Q�[���E�B���h�E�̃C���X�^���X
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
	/// <summary>
	/// �Q�[���T�E���h�̃C���X�^���X
	/// </summary>
	GameSound* m_gameSound = nullptr;
};

