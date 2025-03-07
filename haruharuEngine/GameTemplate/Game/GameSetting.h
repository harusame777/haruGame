#pragma once

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
		/// <summary>
		/// �ݒ荀�ږ�
		/// </summary>
		wchar_t m_settingItemName[GameSettingConstant::MAX_TEXT_NUM] = {};
		/// <summary>
		/// �ݒ荀�ږ��`��v�t�H���g�����_�[
		/// </summary>
		FontRender m_settingItemNameFont;
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

