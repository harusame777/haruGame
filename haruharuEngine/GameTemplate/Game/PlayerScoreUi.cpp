#include "stdafx.h"
#include "PlayerScoreUi.h"

//�����L���ɂ���ƃf�o�b�O���[�h�ɂȂ�
//#define DEBUG_MODE

//�萔��
namespace {
	static const float SCOREBASE_SPRITE_W_SIZE = 1600.0f;
	static const float SCOREBASE_SPRITE_H_SIZE = 900.0f;

	static const Vector3 SCOREBASE_SPRITE_POSITION = { -630.0f,350.0f,0.0f };
	static const Vector3 SCOREBASE_SPRITE_SIZE = { 0.2f,0.2f,0.0f };

	static const Vector3 SCORENUM_SPRITE_POSITION = { -920.0f,460.0f,0.0f };
	static const float SCORENUM_SPRITE_SIZE = 2.0f;
}

//�X�^�[�g�֐�
bool PlayerScoreUi::Start()
{
	//�X�R�A�g�̏�����
	m_scoreBase.Init("Assets/modelData/playerUI/PlayerScoreUi/Score_Base_1.DDS",
		SCOREBASE_SPRITE_W_SIZE,
		SCOREBASE_SPRITE_H_SIZE);

	m_scoreBase.SetPosition(SCOREBASE_SPRITE_POSITION);

	m_scoreBase.SetScale(SCOREBASE_SPRITE_SIZE);

	m_scoreNum.SetPosition(SCORENUM_SPRITE_POSITION);

	m_scoreNum.SetScale(SCORENUM_SPRITE_SIZE);

	m_scoreBase.Update();

	return true;
}

//�A�b�v�f�[�g�֐�
void PlayerScoreUi::Update()
{
#ifdef DEBUG_MODE
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		ScoreAdd(60);
	};
#endif

	//�X�R�A�i���o�[���X�V����
	ScoreNumUpdate();

	*m_gameScore = m_mainScore;

	m_scoreBase.Update();
}

//�X�R�A�i���o�[���X�V����֐�
void PlayerScoreUi::ScoreNumUpdate()
{
	if (m_gameScore == nullptr)
	{
		return;
	}

	m_mainScore = ScoreCalc();

	swprintf_s(wcsbuf, 256, L"%06.1fg",float(m_mainScore));

	m_scoreNum.SetText(wcsbuf);
}

const float PlayerScoreUi::ScoreCalc()
{
	float finalScoreNum = m_mainScore;

	if (m_isScoreUpdate == false)
	{
		return finalScoreNum;
	}

	//�����A���̃X�R�A�����V�����X�R�A�̕����傫��������
	if (m_mainScore < m_newScoreIndex)
	{
		//�X�R�A�𑝂₷
		finalScoreNum += m_addScoreIndex * g_gameTime->GetFrameDeltaTime();

		return finalScoreNum;
	}
	//�������
	else
	{
		finalScoreNum = m_newScoreIndex;
		//�X�R�A�̍X�V�������I������
		m_isScoreUpdate = false;

		return finalScoreNum;
	}
}

//�����_�[�֐�
void PlayerScoreUi::Render(RenderContext& rc)
{
	m_scoreBase.Draw(rc);

	m_scoreNum.Draw(rc);
}