#pragma once
#include <iostream>
#include <variant>

namespace GameSettingConstant {

	static const int MAX_TEXT_NUM = 256;

};

class GameWindow;

class GameSetting : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameSetting() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameSetting() {};
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
		/// �ݒ荀�ږ��`��v�t�H���g�����_�[
		/// </summary>
		FontRender m_settingItemNameFont;
		/// <summary>
		/// �Z�b�e�B���O�o�[
		/// </summary>
		SpriteRender m_settingBar;
		/// <summary>
		/// �Z�b�e�B���O�X���C�_�[
		/// </summary>
		SpriteRender m_settingSlider;
		/// <summary>
		/// �ݒ�l�A�h���X�ۑ��v�ϐ�
		/// </summary>
		std::variant<int*, float*> m_settingValue;
	public:
		/// <summary>
		/// �ݒ�l�A�h���X�ۑ��v�ϐ��AInt�ۑ�
		/// </summary>
		/// <param name="valueInt"></param>
		void SetSettingAddress(int& valueInt)
		{
			m_settingValue = &valueInt;
		}
		/// <summary>
		/// �ݒ�l�A�h���X�ۑ��v�ϐ��AFloat�ۑ�
		/// </summary>
		/// <param name="valueInt"></param>
		void SetSettingAddress(float& valueInt)
		{
			m_settingValue = &valueInt;
		}

	};
	/// <summary>
	/// �ݒ�f�[�^�\���̕ϐ�
	/// </summary>
	std::vector<SettingDatas> m_settingDatasList;
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
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �Q�[���E�B���h�E�̃C���X�^���X
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
};

