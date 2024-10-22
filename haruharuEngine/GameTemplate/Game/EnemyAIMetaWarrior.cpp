#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"

namespace {
	/// <summary>
	/// �G�l�~�[�̍ő吔
	/// </summary>
	static const int WARRIOR_NUM = 3;
}

//�X�^�[�g�֐�
bool EnemyAIMetaWarrior::Start()
{
	//���X�g�̃T�C�Y���G�l�~�[�̐��Ń��T�C�Y
	m_enemyWarriorList.resize(WARRIOR_NUM);
}

//�A�b�v�f�[�g�֐�
void EnemyAIMetaWarrior::Update()
{

	//�G�l�~�[���P�̂ł��ǐՒ���������
	if (SearchEnemyTracking())
	{
		//�G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����
		ChangeTrackingState();
	}

}

//�G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
void EnemyAIMetaWarrior::ChangeTrackingState()
{

}

//���X�g�ɃG�l�~�[����
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//���X�g�ɃG�l�~�[��������
	m_enemyWarriorList.push_back(enemyPtr);
}

const bool EnemyAIMetaWarrior::SearchEnemyTracking() const
{
	for (auto& ptr: m_enemyWarriorList)
	{
		if (ptr->IsTracking())
		{
			return true;
		}
	}

	return false;
}
