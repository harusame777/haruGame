#pragma once
#include "PlayerUIBase.h"

//�萔��
namespace {
	/// <summary>
	/// �X�^�~�i�ő�l
	/// </summary>
	static const float MAX_STAMINA_INDEX = 100; 

	static const float INIT_DEGREE_VALUE = 2.7f;

	static const float MAX_DEGREE_VALUE = 3.6f;
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
	void InitPlayerStaminaPtr(float* staminaPtr)
	{
		m_playerStamina = staminaPtr;
	}
private:
	/// <summary>
	/// �X�^�~�iUi�̃X�e�[�g
	/// </summary>
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
	/// �X�^�~�i�X�e�[�g�A�b�v�f�[�g�֐�
	/// </summary>
	void StaminaStateUpdate();
	/// <summary>
	/// �X�^�~�i�o�[�_�Ŋ֐�
	/// </summary>
	void BlinkingBarCalc();
	/// <summary>
	/// �A���t�@�l�C�[�W���O�֐�
	/// </summary>
	const float& AlphaEasing();
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
		float m_alpha = 0.7f;
		//r�l
		bool m_redAddFlag = false;
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
		void AddDegree(const float addValue)
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
		/// <summary>
		/// �A���t�@�l������
		/// </summary>
		/// <param name="value"></param>
		void SetAlpha(const float value)
		{
			m_alpha = value;
		}
		/// <summary>
		/// �A���t�@�l���Z
		/// </summary>
		/// <param name="addValue"></param>
		void AddAlpha(const float addValue)
		{
			m_alpha += addValue;
		}
		/// <summary>
		/// �A���t�@�l�擾
		/// </summary>
		/// <returns></returns>
		const float& GetAlpha() const
		{
			return m_alpha;
		}
		/// <summary>
		/// �ԉ��Z�t���O�ݒ�
		/// </summary>
		/// <param name="setFlag"></param>
		void SetRedAddFlag(const bool setFlag)
		{
			m_redAddFlag = setFlag;
		}
	};
	StaminaBarData m_staminaBarData;
	/// <summary>
	/// �X�^�~�iUi�X�e�[�g
	/// </summary>
	StaminaUiState m_staminaState = StaminaUiState::en_staminaHigh;
	/// <summary>
	/// �v���C���[�̃X�^�~�i
	/// </summary>
	float* m_playerStamina = nullptr;
	/// <summary>
	/// Ui���̃X�^�~�i
	/// </summary>
	float m_mainStamina = 0;
	/// <summary>
	/// �A���t�@�l�C�[�W���O����
	/// </summary>
	float m_alphaRatio = 0.0f;
	/// <summary>
	/// �X�^�~�i����ɂȂ������̃t���O
	/// </summary>
	bool m_staminaOutFlag = false;
	/// <summary>
	/// �A���t�@�l�C�[�W���O���]�t���O
	/// </summary>
	bool m_alphaEasingInversionFlag = true;
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

