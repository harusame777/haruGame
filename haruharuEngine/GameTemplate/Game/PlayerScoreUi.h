#pragma once
#include "PlayerUIBase.h"

class PlayerScoreUi : public PlayerUIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerScoreUi() {}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerScoreUi() {}
	/// <summary>
	/// �X�R�A�𑝂₷�֐�
	/// </summary>
	/// <param name="scoreAddIndex"></param>
	void ScoreAdd(int scoreAddIndex)
	{
		if (m_isScoreUpdate == true)
		{
			return;
		}

		m_isScoreUpdate = true;

		m_addScoreIndex = scoreAddIndex / 2.0f;

		m_newScoreIndex = m_mainScore + scoreAddIndex;
		
		return;
	}
	/// <summary>
	/// ���C���X�R�A��ݒ�
	/// </summary>
	/// <param name="ptr"></param>
	void InitMainScorePtr(float& ptr)
	{
		m_gameScore = &ptr;
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
	/// �X�R�A�i���o�[�̃A�b�v�f�[�g
	/// </summary>
	void ScoreNumUpdate();
	/// <summary>
	/// �X�R�A�̌v�Z
	/// </summary>
	const float ScoreCalc();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	void Render(RenderContext& rc);
	/// <summary>
	/// �X�R�A�x�[�X�X�v���C�g
	/// </summary>
	SpriteRender m_scoreBase;
	/// <summary>
	/// �X�R�A�̐��X�v���C�g
	/// </summary>
	FontRender m_scoreNum;
	/// <summary>
	/// �X�R�A
	/// </summary>
	FontRender m_socore;
	/// <summary>
	/// ���C���X�R�A
	/// </summary>
	float m_mainScore = 0;
	/// <summary>
	/// �Q�[���̃X�R�A
	/// </summary>
	float* m_gameScore = nullptr;
	/// <summary>
	/// �V�����X�R�A�̐��l
	/// </summary>
	float m_newScoreIndex = 0;
	/// <summary>
	/// ���Z�l
	/// </summary>
	float m_addScoreIndex = 0;
	/// <summary>
	/// �X�R�A�̃X�v���C�g�ɕ\�����镶��
	/// </summary>
	wchar_t wcsbuf[256];
	/// <summary>
	/// �X�R�A���X�V�����ǂ���
	/// </summary>
	bool m_isScoreUpdate = false;
};

