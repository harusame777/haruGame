#include "stdafx.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"
#include "EnemyAIConSearch.h"
#include "EnemyAIMoveAstar.h"

//�X�^�[�g�֐�
void EnemySM_Warrior::Start()
{
	//AI��List�����̃G�l�~�[�ɕK�v�ȕ��ŏ���������
	//�o�H�T��
	m_EnemyAIList.push_back(new EnemyAIMoveAstar);

	//�R�Â��Ă���G�l�~�[�̃C���X�^���X��AIList�̃v���O�����ɓn��
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->BinedEnemy(m_enemy);
	}

	//AIList�̒��̃v���O�����̃X�^�[�g�֐����N������
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->Start();
	}

	//����̃v���O���������X�g�Ɋi�[���Ă���
	//���E�T��
	m_enemyConList.push_back(new EnemyAIConSearch);

	//�R�Â��Ă���G�l�~�[�̃C���X�^���X��ConList�̃v���O�����ɓn��
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->BinedEnemy(m_enemy);
	}

	//ConList�̒��̃v���O�����̃X�^�[�g�֐����N������
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->Start();
	}
}

//�A�b�v�f�[�g�֐�
void EnemySM_Warrior::Update()
{

}

//���ʃX�e�[�g�ύX�֐�
void EnemySM_Warrior::ChangeState()
{
	
}