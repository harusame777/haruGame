#pragma once

class Load;

class Result : public IGameObject
{
private:

	enum ResultState
	{
		en_standby,

		en_infoDrowTop,

		en_infoDrowMiddle,

		en_infoDrowBottom,

		en_infoIndexAdd,

		en_infoResultEnd,
	};
	ResultState m_resultState = ResultState::en_standby;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Result(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Result(){}
	/// <summary>
	/// �ŏI�X�R�A�ݒ�
	/// </summary>
	/// <param name="score"></param>
	void SetFinalScore(const float& score)
	{
		m_scoreIndex = score;
	}
	/// <summary>
	/// ���U���g���I���������ǂ���
	/// </summary>
	/// <returns></returns>
	const bool& IsResultEnd()
	{
		return m_isResultEnd;
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
	/// ���U���g�X�e�[�g�̃A�b�v�f�[�g
	/// </summary>
	void ResultStateUpdate();
	/// <summary>
	/// �t�H���g�A�b�v�f�[�g
	/// </summary>
	void FontUpdate();
	/// <summary>
	/// ���Ԏw��ҋ@�X�e�[�g
	/// </summary>
	/// <param name="time"></param>
	/// <returns></returns>
	const bool& WaitTime(const float& time);
	/// <summary>
	/// �^�C�}�[
	/// </summary>
	float m_timer = 0.0f;
	/// <summary>
	/// �^�C�}�[�ő�l
	/// </summary>
	float m_timerMax = 0.0f;
	/// <summary>
	/// �X�R�A�l�̃C�[�W���O�֐�
	/// </summary>
	void ScoreEasing();
	/// <summary>
	/// �X�R�A���Z�l
	/// </summary>
	float m_scoreAddIndex = 0.0f;
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ������
	/// </summary>
	FontRender m_resultInfoTop;
	FontRender m_resultInfoBottom;
	FontRender m_resultInfoMiddle;
	/// <summary>
	/// ��둤�̃X�v���C�g
	/// </summary>
	SpriteRender  m_backSideSprite;
	/// <summary>
	/// �X�R�A���l
	/// </summary>
	float m_scoreIndex = 0.0f;
	/// <summary>
	/// �C���t�H���[�V�����ɏ������܂�鐔�l
	/// </summary>
	float m_infoDrawIndex = 0.0f;
	/// <summary>
	/// ���U���g���I���������ǂ���
	/// </summary>
	bool m_isResultEnd = false;
	/// <summary>
	/// ���[�h�̃C���X�^���X
	/// </summary>
	Load* m_load = nullptr;
};

