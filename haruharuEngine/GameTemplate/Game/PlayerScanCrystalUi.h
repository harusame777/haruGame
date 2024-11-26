#pragma once
#include "PlayerUIBase.h"
//�ꎞ�I�ȃ��m����Ŏ��ԏ�������������
#include "EnemyAIConBase.h"

class Player;

class PlayerScanCrystalUi : public PlayerUIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerScanCrystalUi() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerScanCrystalUi() {};
private:
	enum ScanState
	{
		/// <summary>
		/// �ҋ@���
		/// </summary>
		en_scanStandby,
		/// <summary>
		/// ��������`��
		/// </summary>
		en_scanLineEasing,
		/// <summary>
		/// �A���t�@�l���C�[�W���O
		/// </summary>
		en_scanAEasing,
		/// <summary>
		/// �}�[�J�[��`��
		/// </summary>
		en_scanMarkerDraw,
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
	/// �X�v���C�g�X�V
	/// </summary>
	void SpriteUpdate();
	/// <summary>
	/// �A���t�@�l�̃C�[�W���O
	/// </summary>
	/// <returns></returns>
	const float AlphaEasing();
	/// <summary>
	/// ���C�v�̃C�[�W���O�֐�
	/// </summary>
	/// <returns></returns>
	const float WipeEasing();
	/// <summary>
	/// �h���[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �X�L�����X�e�[�g
	/// </summary>
	ScanState m_scanState = ScanState::en_scanStandby;
	/// <summary>
	/// �������̃X�v���C�g
	/// </summary>
	SpriteRender m_scanlineSprite;
	/// <summary>
	/// �������̃f�[�^
	/// </summary>
	struct ScanLineSpriteData
	{
		/// <summary>
		/// ���C�v����
		/// </summary>
		Vector2 m_wipeDir;
		/// <summary>
		/// ���C�v�T�C�Y
		/// </summary>
		float m_wipeSize;
		/// <summary>
		/// �A���t�@�l
		/// </summary>
		float m_paramA = 1.0f;
	};
	/// <summary>
	/// �������̃f�[�^�ϐ�
	/// </summary>
	ScanLineSpriteData m_scanLineData;
	/// <summary>
	/// �A���t�@�l����
	/// </summary>
	float m_alphaRatio = 0.0f;
	/// <summary>
	/// �C�[�W���O����ւ�
	/// </summary>
	bool m_swapEasing = true;
	/// <summary>
	/// ���C�v����
	/// </summary>
	float m_wipeRatio = 1.0f;
	/// <summary>
	/// �X�L�����t���O
	/// </summary>
	bool m_scanFlag = false;
	/// <summary>
	/// �X�L�����J�n
	/// </summary>
	void ScanStart()
	{
		//�X�L�����t���O��true�ɂ���
		m_scanFlag = true;
		//�X�L�����X�e�[�g���A���t�@�l�C�[�W���O�ɕύX����
		m_scanState = ScanState::en_scanLineEasing;
		//�C�[�W���O����������������
		//�A���t�@�l�C�[�W���O
		m_swapEasing = true;
		m_scanLineData.m_paramA = 0.3;
		m_alphaRatio = 0.0f;
		//���C�v�C�[�W���O
		m_scanLineData.m_wipeSize = 0.0f;
		m_wipeRatio = 0.0f;
	}
	/// <summary>
	/// �X�L�����I��
	/// </summary>
	void ScanEnd()
	{
		m_scanFlag = false;
	}
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

	//�����ԏ���
	EnemyAIConBase* m_waitTime = nullptr;
};

