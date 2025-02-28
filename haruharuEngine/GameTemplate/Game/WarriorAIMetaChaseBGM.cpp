#include "stdafx.h"
#include "WarriorAIMetaChaseBGM.h"
#include "GameSound.h"


//�N���֐�
void WarriorAIMetaChaseBGM::MetaAIInit()
{

	m_gameSound = FindGO<GameSound>("gameSound");

	m_gameBGM = &m_gameSound->ReturnPointerLocalSoundOrder(GameSound::en_chaseBGM, 0.5f);

}

//���s�֐�
void WarriorAIMetaChaseBGM::MetaAIExecution(EnemySMBase* initEnemy)
{
	//�ǐՏ�Ԃ̃G�l�~�[��T��
	SearchTrackingStateEnemy();

	//����BGM�����Ă���
	if (m_isBGMPlayBack == true)
	{
		//�����ǐՒ��̃G�l�~�[�����Ȃ�������
		if (m_isTrackingStateEnemy == false)
		{
			//BGM���~�߂�
			BGMEnd();
		}
	}
	else
	{
		//�����ǐՒ��̃G�l�~�[��������
		if (m_isTrackingStateEnemy == true)
		{
			//BGM���n�߂�
			BGMStart();
		}
	}

	if (m_isBGMFadeOut == true)
	{
		BGMFadeOut();
	}

}

//�ǐՏ�Ԃ̃G�l�~�[�����݂��邩�ǂ�����T��
void WarriorAIMetaChaseBGM::SearchTrackingStateEnemy()
{
	int enemyStateNum = 0;

	for (auto& enemyPtr : m_sharedWarriorDatas->m_warriorDatas)
	{
		enemyStateNum = enemyPtr->GetEnemyPtr().GetStateNumber();
		
		if (enemyStateNum == EnemyBase::en_tracking)
		{
			m_isTrackingStateEnemy = true;
			return;
		}
	}

	m_isTrackingStateEnemy = false;
}

//BGM�Đ��֐�
void WarriorAIMetaChaseBGM::BGMStart()
{

	m_gameBGM->Play(true);

	m_gameBGM->SetVolume(0.5f);

	m_isBGMPlayBack = true;

	m_volumeRatio = 0.0f;

}

void WarriorAIMetaChaseBGM::BGMEnd()
{

	m_isBGMFadeOut = true;

}

void WarriorAIMetaChaseBGM::BGMFadeOut()
{
	if (m_volumeRatio > 1.0f)
	{
		m_volumeRatio = 0.0f;

		m_gameBGM->Stop();

		m_isBGMPlayBack = false;

		m_isBGMFadeOut = false;
	}

	m_volumeRatio += g_gameTime->GetFrameDeltaTime();

	m_gameBGM->SetVolume(Leap(0.5f, 0.0f, m_volumeRatio));
}

//�I���֐�
const bool WarriorAIMetaChaseBGM::ProcessEnd(EnemySMBase* initEnemy)
{
	m_gameBGM->Stop();

	m_isBGMPlayBack = false;

	return true;
}
