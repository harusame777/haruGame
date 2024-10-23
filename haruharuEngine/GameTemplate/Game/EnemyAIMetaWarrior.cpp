#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"
#include "EnemyWarriorTrackingState.h"

//������
//
//1.�v���C���[��������
//
//2.�����̎���̃G�l�~�[�ɌĂт�����
//
//3.�Ăт����ɋC�Â��Ă��ꂽ�����ȊO�̃G�l�~�[�̌��݂̃X�e�[�g���擾����
//
//4.�����̃X�e�[�g�擾���A�����ȊO�̃G�l�~�[�̃X�e�[�g�ƌ���ׂ�
//
//5.���ʂɂ���ăX�e�[�g�̔ԍ���Ԃ�
//
//�ǂ̃^�C�~���O�ŒǐՃX�e�[�g��ύX���邩�H
//�G�l�~�[���v���C���[�ɋC�Â��Ď��͂ɌĂт������s�����^�C�~���O�Ŏ��s������
//�ǐՒ��ɂق��̃G�l�~�[���C�Â����肵����A�����I�Ɍ���ǂ��悤�ɂ���B

namespace {
	/// <summary>
	/// �E�H���A�[�̍ő吔
	/// </summary>
	static const int WARRIOR_NUM = 3;
	/// <summary>
	/// ���a�v�Z�p�̂��
	/// </summary>
	static const float CALL_RANGE_CALC = 250.0f;
}

//�X�^�[�g�֐�
bool EnemyAIMetaWarrior::Start()
{
	//���X�g�̃T�C�Y���E�H���A�[�̐��Ń��T�C�Y
	m_enemyWarriorList.resize(WARRIOR_NUM);

	return true;
}

//�E�H���A�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
void EnemyAIMetaWarrior::MetaAIExecution(EnemySM_Warrior* enemyPtr)
{
	//�܂��Ăт������G�l�~�[�̃|�C���^���i�[
	//�O�̂��ߏ�����
	m_MainCallWarrior = nullptr;
	m_MainCallWarrior = enemyPtr;
	//���͂ɌĂт������s��
	CallWarrior();
}

//���X�g�ɃE�H���A�[����
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//�f�[�^���쐬
	MetaAIWarriorData* initData = new MetaAIWarriorData;
	//�G�l�~�[�̃|�C���^���i�[
	initData->m_warriorPtr = enemyPtr;
	//���X�g�ɃE�H���A�[��������
	m_enemyWarriorList.push_back(initData);
}

void EnemyAIMetaWarrior::CallWarrior()
{
	//�܂��Ăт������s�����E�H���A�[�̎��͂ɃE�H���A�[�����݂��邩
	//�𒲂ׂ�
	Vector3 callEnemyPos = m_MainCallWarrior->GetEnemyPtr().GetPosition();
	Vector3 enemyPos;
	Vector3 faceVector;
	float len;

	//�Ă΂ꂽ�G�l�~�[�̃|�C���^��������
	m_subCalledWarriorFirst = nullptr;
	m_subCalledWarriorSecond = nullptr;
	
	//�͈�for���ŉ�
	for (auto& ptr : m_enemyWarriorList)
	{
		//�����̃A�h���X�Ɠ�����������
		if (m_MainCallWarrior == ptr->m_warriorPtr)
		{
			//�������΂�
			continue;
		}

		//�E�H���A�[�̈ʒu���擾
		enemyPos = ptr->m_warriorPtr->GetEnemyPtr().GetPosition();

		//�Ăт����������E�H���A�[�̈ʒu�ƌ��Z���s����
		//�Ăт����������E�H���A�[������͂̃E�H���A�[�̍��W�Ɍ������ĐL�т�
		//�x�N�g�������
		faceVector = enemyPos - callEnemyPos;
		//������2��ɕϊ�
		len = faceVector.LengthSq();

		//����250.0f�����ɃE�H���A�[��������
		if (len < CALL_RANGE_CALC * CALL_RANGE_CALC)
		{			
			//�z��̌Ăт����ɉ������G�l�~�[�̃|�C���^��ϐ��Ɋi�[
			if (m_subCalledWarriorFirst == nullptr)
			{
				m_subCalledWarriorFirst = ptr->m_warriorPtr;
			}
			else
			{
				m_subCalledWarriorSecond = ptr->m_warriorPtr;
			}
		}
	}

	//�G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����
	ChangeTrackingState();
}

void EnemyAIMetaWarrior::ChangeTrackingState()
{

	//�Z�R���h��null��������
	if (m_subCalledWarriorSecond == nullptr)
	{
		//�P�̏������s��
		if (m_subCalledWarriorFirst->GetEnemyPtr().GetTrackingStateNumber()
			== WarriorTrackingState::en_nonTracking)
		{
			//���g�̃E�H���A�[��ʏ�ǐՃX�e�[�g��
			m_MainCallWarrior->GetEnemyPtr().SetTrackingStateNumber(WarriorTrackingState::en_chaseFromBehind);
			//�t�@�[�X�g����荞�݃X�e�[�g��
			m_subCalledWarriorFirst->GetEnemyPtr().SetTrackingStateNumber(WarriorTrackingState::en_wrapAround);
		}
		else if(m_subCalledWarriorFirst->GetEnemyPtr().GetTrackingStateNumber()
			== WarriorTrackingState::en_chaseFromBehind)
		{
			
		}
	}
	//null����Ȃ�������
	else
	{
		//�����������s��

	}

	//�܂��Ăт����ɉ��������X�g�̃T�C�Y���擾����
	
	////�Ăт����ɉ������G�l�~�[��2�̈ȏゾ������
	//if (callWarriorNum >= 2)
	//{
	//	//2�̂̎��̔�����s��
	//	if (m_CallRespondWarriorList[0]->GetEnemyPtr().GetTrackingStateNumber() ==
	//		WarriorTrackingState::en_nonTracking && 
	//		m_CallRespondWarriorList[1]->GetEnemyPtr().GetTrackingStateNumber() ==
	//		WarriorTrackingState::en_nonTracking)
	//	{

	//	}
	//}
	////�������
	//else
	//{
	//	//1�̂̎��̔�����s��
	//	if (m_CallRespondWarriorList[0]->GetEnemyPtr().GetTrackingStateNumber() ==
	//		WarriorTrackingState::en_nonTracking)
	//	{
	//		m_MainCallWarrior->GetEnemyPtr().SetTrackingStateNumber(WarriorTrackingState::en_chaseFromBehind);
	//	}
	//}

}