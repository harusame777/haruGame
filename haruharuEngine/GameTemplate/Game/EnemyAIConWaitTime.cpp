#include "stdafx.h"
#include "EnemyAIConWaitTime.h"
#include "EnemyBase.h"

//�X�^�[�g�֐�
void EnemyAIConWaitTime::Start()
{
	//�^�C�}�[��0.0f��
	m_timer = 0.0f;

	//�t���O��false��
	m_isTimerInit = false;
}

//�������s�֐�
bool EnemyAIConWaitTime::Execution()
{
	//����������Ă��Ȃ�������
	if (!m_isTimerInit)
	{
		//����������
		m_timer = m_timerMax;
		//�t���O��true��
		m_isTimerInit = true;
	}

	//�t���[���^�C���Ń^�C�}�[�����炷
	m_timer -= g_gameTime->GetFrameDeltaTime();
	
	//�����^�C�}�[��0.0f�ȉ���������
	if (m_timer <= 0.0f) 
	{
		//�^�C�}�[��0.0f��
		m_timer = 0.0f;

		//�t���O��false��
		m_isTimerInit = false;

		//����������
		m_timer = m_timerMax;

		//true��Ԃ�
		return true;
	}

	//false��Ԃ�
	return false;
}