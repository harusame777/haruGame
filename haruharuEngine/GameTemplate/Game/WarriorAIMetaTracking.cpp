#include "stdafx.h"
#include "WarriorAIMetaTracking.h"
#include "EnemySMBase.h"

//�萔��
namespace {
	/// <summary>
	/// �E�H���A�[�̍ő吔
	/// </summary>
	static const int WARRIOR_NUM = 3;
	/// <summary>
	/// ���a�v�Z�p�̂��
	/// </summary>
	static const float CALL_RANGE_CALC = 750.0f;
}

//���^AI������
void WarriorAIMetaTracking::MetaAIInit()
{

}

//���^AI���s
void WarriorAIMetaTracking::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	CallWarrior();
}

//���ӃE�H���A�[�ɌĂъ|��
void WarriorAIMetaTracking::CallWarrior()
{

	if (m_sharedWarriorDatas->m_warriorDatas[0] == nullptr)
	{
		return;
	}

	//�܂��Ăт������s�����E�H���A�[�̎��͂ɃE�H���A�[�����݂��邩
	//�𒲂ׂ�
	Vector3 callEnemyPos = m_MainCallWarrior->GetEnemyPtr().GetPosition();
	Vector3 enemyPos;
	Vector3 faceVector;
	float len;

	//�͈�for���ŉ�
	for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
	{
		//�����̃A�h���X�Ɠ�����������
		if (m_MainCallWarrior == ptr)
		{
			//�������΂�
			continue;
		}

		//�E�H���A�[�̈ʒu���擾
		enemyPos = ptr->GetEnemyPtr().GetPosition();

		//�Ăт����������E�H���A�[�̈ʒu�ƌ��Z���s����
		//�Ăт����������E�H���A�[������͂̃E�H���A�[�̍��W�Ɍ������ĐL�т�
		//�x�N�g�������
		faceVector = enemyPos - callEnemyPos;
		//������2��ɕϊ�
		len = faceVector.LengthSq();

		//����250.0f�����ɃE�H���A�[��������
		if (len < CALL_RANGE_CALC * CALL_RANGE_CALC)
		{
			ptr->SetCallMetaAI(true);
		}
	}

	//�G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����
	ChangeTrackingState();
}

void WarriorAIMetaTracking::ChangeTrackingState()
{

	//������荞�݃X�e�[�g�̃G�l�~�[�����݂��Ă��邩
	bool existsWrapAroundWarrior = false;

	//�͈�for���ŉ�
	for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
	{

		//�����̃A�h���X�Ɠ�����������
		if (m_MainCallWarrior == ptr)
		{
			ptr->SetTrackingState(WarriorTrackingState::en_chaseFromBehind);
			//�������΂�
			continue;
		}

		//�C�e���[�^�[�̃E�H���A�[���Ăт�����ꂽ�E�H���A�[��������
		if (ptr->GetCallMetaAI() == true)
		{
			//��荞�݃X�e�[�g�̃E�H���A�[�����݂��Ă�����
			if (existsWrapAroundWarrior == true)
			{
				//��납��ǂ킹��
				ptr->SetTrackingState(WarriorTrackingState::en_usually);
				ptr->SetState(EnemySM_Warrior::en_warrior_trackingMetaAI);
				continue;
			}
			//��荞�݃X�e�[�g�̃E�H���A�[���܂����݂��Ȃ�������

			//��荞�܂���
			ptr->SetTrackingState(WarriorTrackingState::en_wrapAround);
			ptr->SetState(EnemySM_Warrior::en_warrior_trackingMetaAI);

			//�t���O��true��
			existsWrapAroundWarrior = true;
		}

	}

}

//�����I������
const bool WarriorAIMetaTracking::ProcessEnd(EnemySMBase* initEnemy)
{
	
	//�����̒ǐՃX�e�[�g��������
	m_MainCallWarrior = initEnemy;

	int num = 0;

	for (auto & ptr : m_sharedWarriorDatas->m_warriorDatas)
	{
		if (&m_MainCallWarrior->GetEnemyPtr() == &ptr->GetEnemyPtr())
		{
			ptr->SetTrackingState(WarriorTrackingState::en_nonTracking);
		}

		if (ptr->GetEnemyPtr().GetTrackingStateNumber() == WarriorTrackingState::en_nonTracking)
		{
			num++;
		}
	}

	if (num >= 3)
	{
		//���ׂĂ̏������I�������ƕԂ�
		return true;
	}

	return false;

}