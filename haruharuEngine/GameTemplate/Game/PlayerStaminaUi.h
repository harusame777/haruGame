#pragma once
#include "PlayerUIBase.h"

//�萔��
namespace {
	/// <summary>
	/// �X�^�~�i�ő�l
	/// </summary>
	static const float MAX_STAMINA_INDEX = 100; 

	static const float INIT_DEGREE_VALUE = 0.7f;

	static const float MAX_DEGREE_VALUE = 5.6f;
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
	enum StaminaUiState
	{
		en_staminaHigh,

		en_staminaLow,

		en_staminaOut,
	};
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
	/// ���C�v�v�Z�֐�
	/// </summary>
	/// <returns></returns>
	const float& WipeCalc();
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
	private:
		//����
		float m_degree = INIT_DEGREE_VALUE;
		//���l
		float m_alpha = 1.0f;
	public:
		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="value"></param>
		void SetDegree(const float value)
		{
			m_degree = value;
		}
		/// <summary>
		/// �������Z
		/// </summary>
		/// <param name="addValue"></param>
		void AddDegree(const float& addValue)
		{
			m_degree += addValue;
		}
		/// <summary>
		/// �����擾
		/// </summary>
		/// <returns></returns>
		const float& GetDegree() const
		{
			return m_degree;
		}
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
	/// �C�[�W���O����
	/// </summary>
	float m_ratio = 0.0f;
	/// <summary>
	/// �X�^�~�i�x�[�XUi
	/// </summary>
	SpriteRender m_staminaBase;
	/// <summary>
	/// �X�^�~�i�o�[Ui
	/// </summary>
	SpriteRender m_staminaBar;
	/// <summary>
	/// �X�^�~�i�o�[Ui�̃A���t�@����p�e�N�X�`��
	/// </summary>
	Texture m_staminaBarAlphaTexture;

	/// <summary>
	/// flaot�p���`���
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}

};

