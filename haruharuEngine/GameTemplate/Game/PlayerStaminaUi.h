#pragma once
#include "PlayerUIBase.h"

//�萔��
namespace {
	/// <summary>
	/// �X�^�~�i�ő�l
	/// </summary>
	static const int MAX_STAMINA_INDEX = 100; 
}

class PlayerStaminaUi : public PlayerUIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerStaminaUi(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerStaminaUi(){}
	/// <summary>
	/// �v���C���[�̃X�^�~�i�̕ϐ��̃|�C���^�ŏ�����
	/// </summary>
	/// <param name="staminaPtr"></param>
	void InitPlayerStaminaPtr(int* staminaPtr)
	{
		m_playerStamina = staminaPtr;
	}
private:
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
	/// �X�^�~�i�o�[�̃f�[�^
	/// </summary>
	struct StaminaBarData
	{
	
	};
	StaminaBarData m_staminaBarData;
	/// <summary>
	/// �v���C���[�̃X�^�~�i
	/// </summary>
	int* m_playerStamina = nullptr;
	/// <summary>
	/// Ui���̃X�^�~�i
	/// </summary>
	int m_mainStamina = 0;
	/// <summary>
	/// �X�^�~�i�x�[�XUi
	/// </summary>
	SpriteRender m_staminaBase;
	/// <summary>
	/// �X�^�~�i�o�[Ui
	/// </summary>
	SpriteRender m_staminaBar;

};

