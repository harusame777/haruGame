#pragma once
class Result : public IGameObject
{
private:

	enum ResultState
	{
		en_standby,

		en_infoDrowTop,

		en_infoDrowMiddle,

		en_infoDrowBottom,

		en_infoIndexAdd
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

	void ResultStateUpdate();

	void FontUpdate();

	const bool& WaitTime(const float& time);

	float m_timer = 0.0f;

	float m_timerMax = 0.0f;

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

	float m_infoDrawIndex = 0.0f;
};

