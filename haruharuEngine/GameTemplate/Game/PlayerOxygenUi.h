#pragma once
#include "PlayerUIBase.h"

class Game;

class PlayerOxygenUi : public PlayerUIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerOxygenUi() {}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerOxygenUi(){}
	/// <summary>
	/// �O������^�C�}�[�̃|�C���^���i�[����֐�
	/// </summary>
	/// <param name="timerPtr"></param>
	void InitTimerPtr(float* timerPtr)
	{
		m_gameTimer = timerPtr;
	}
private:
	/// <summary>
	/// �_�f�Q�[�W�X�e�[�g
	/// </summary>
	enum OxygenGaugeState
	{
		en_oxygenHigh,

		en_oxygenLow,

		en_oxygenMin,
	};
	OxygenGaugeState m_oxygenGaugeState = OxygenGaugeState::en_oxygenHigh;
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
	/// �_�f�Q�[�W�X�e�[�g�X�V�֐�
	/// </summary>
	const OxygenGaugeState& OxygenGaugeStateUpdate();
	/// <summary>
	/// �_�f�Q�[�W�_�ŏ����֐�
	/// </summary>
	void BlinkingOxygenGaugeCalc();
	/// <summary>
	/// ���C�v�v�Z
	/// </summary>
	const float& WipeCalc();
	/// <summary>
	/// �A���t�@�l�C�[�W���O�֐�
	/// </summary>
	const float& AlphaEasing(const float& speed);
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �_�f�Q�[�W�̃f�[�^
	/// </summary>
	struct OxygenGaugeSpriteData
	{
	private:
		/// <summary>
		/// ���C�v����
		/// </summary>
		Vector2 m_wipeDir;
		/// <summary>
		/// ���C�v�T�C�Y
		/// </summary>
		float m_wipeSize = 0;
		/// <summary>
		/// �A���t�@�l
		/// </summary>
		float m_alpha = 0.7f;
		/// <summary>
		/// �J���[�X�e�[�g
		/// </summary>
		int m_colorState = OxygenGaugeState::en_oxygenHigh;
	public:
		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="value"></param>
		void SetDegree(const float value)
		{
			m_wipeSize = value;
		}
		/// <summary>
		/// �������Z
		/// </summary>
		/// <param name="addValue"></param>
		void AddDegree(const float addValue)
		{
			m_wipeSize += addValue;
		}
		/// <summary>
		/// �����擾
		/// </summary>
		/// <returns></returns>
		const float& GetDegree() const
		{
			return m_wipeSize;
		}
		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="value"></param>
		void SetDirction(const Vector2 value)
		{
			m_wipeDir = value;
		}
		/// <summary>
		/// �����擾
		/// </summary>
		/// <returns></returns>
		const Vector2& GetDirction() const
		{
			return m_wipeDir;
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
		/// �J���[�X�e�[�g�ݒ�
		/// </summary>
		/// <param name="value"></param>
		void SetColorState(const OxygenGaugeState value)
		{
			m_colorState = value;
		}
	};
	/// <summary>
	/// �_�f�Q�[�W�̃f�[�^
	/// </summary>
	OxygenGaugeSpriteData m_oxygenGaugeSpriteData;
	/// <summary>
	/// �Q�[���^�C�}�[
	/// </summary>
	float* m_gameTimer = nullptr;
	/// <summary>
	/// �^�C�}�[
	/// </summary>
	float m_mainOxygenIndex = 0.0f;
	/// <summary>
	/// �A���t�@�l�C�[�W���O����
	/// </summary>
	float m_alphaRatio = 0.0f;
	/// <summary>
	/// �A���t�@�l�C�[�W���O���]�t���O
	/// </summary>
	bool m_alphaEasingInversionFlag = true;
	/// <summary>
	/// UI�g
	/// </summary>
	SpriteRender m_oxygenUiBase;
	/// <summary>
	/// UI�Q�[�W
	/// </summary>
	SpriteRender m_oxygenUiGauge;
	/// <summary>
	/// �Q�[�W�̃A���t�@�l�����e�N�X�`��
	/// </summary>
	Texture m_m_oxygenGaugeAlphaTexture;
	/// <summary>
	/// �Q�[���̃C���X�^���X
	/// </summary>
	Game* m_game = nullptr;
	/// <summary>
	/// �f�o�b�N�p�̃t�H���g�����_�[
	/// </summary>
	FontRender m_debugFontRender;
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

