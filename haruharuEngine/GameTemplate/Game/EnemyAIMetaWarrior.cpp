#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"

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
	//���͂ɌĂт������s��
	CallWarrior(enemyPtr);
}

//���X�g�ɃE�H���A�[����
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//���X�g�ɃE�H���A�[��������
	m_enemyWarriorList.push_back(enemyPtr);
}

void EnemyAIMetaWarrior::CallWarrior(EnemySM_Warrior* enemyPtr)
{
	//�N���A����
	m_CallRespondWarriorList.clear();

	//�܂��Ăт������s�����E�H���A�[�̎��͂ɃE�H���A�[�����݂��邩
	//�𒲂ׂ�
	Vector3 callEnemyPos = enemyPtr->GetEnemyPtr().GetPosition();
	Vector3 enemyPos;
	Vector3 faceVector;
	float len;
	
	//�͈�for���ŉ�
	for (auto& ptr : m_enemyWarriorList)
	{
		//�������̃|�C���^��������������
		if (enemyPtr == ptr)
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
			//�Ăт�����A��p�̔z��Ƀ|�C���^���i�[
			m_CallRespondWarriorList.push_back(ptr);
		}
	}

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
