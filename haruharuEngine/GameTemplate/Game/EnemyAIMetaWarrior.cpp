#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"
#include "Player.h"

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
	static const float CALL_RANGE_CALC = 100000.0f;
}

//�X�^�[�g�֐�
bool EnemyAIMetaWarrior::Start()
{
	//���x�������_�[���g�p���ď���n�_���擾����
	m_levelRender.Init("Assets/mapLevel/testLevel3.tkl", [&](LevelObjectData_Render& objData)
	{
		if (objData.ForwardMatchName(L"patrolroute") == true)
		{
			MetaAIPatrolRuteData* newData = new MetaAIPatrolRuteData;

			//���x������ʒu���擾����
			newData->m_patrolPos = objData.m_position;

			//�z��Ɋi�[����
			m_patrolRuteList.push_back(newData);

			return true;
		}
		return true;
	});

	//�v���C���[�̃C���X�^���X���擾����
	m_player = FindGO<Player>("player");

	return true;
}

//�E�H���A�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
void EnemyAIMetaWarrior::MetaAIExecution(EnemySM_Warrior* enemyPtr, const MetaAIMode setMode)
{

	//���݉�������̏�������������
	if (m_isCurrentlyProcessed == true)
	{
		return;
	}
	else
	{
		//�������ɂ���
		m_isCurrentlyProcessed = true;
	}

	//���̊֐����Ăяo�����G�l�~�[�̃|�C���^���i�[����
	m_MainCallWarrior = enemyPtr;

	switch (m_nowMetaAIMode)
	{
	case EnemyAIMetaWarrior::mode_trackingStateChange:
		//���͂ɌĂт������s��
		CallWarrior();
		break;
	case EnemyAIMetaWarrior::mode_patrolRouteSet:
		break;
	default:
		break;
	}

}

//���X�g�ɃE�H���A�[����
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//�f�[�^���쐬
	MetaAIWarriorData* initData = new MetaAIWarriorData;
	//�G�l�~�[�̃|�C���^���i�[
	initData->m_warriorPtr = enemyPtr;
	//���X�g�ɃE�H���A�[��������
	m_sharedWarriorDatas->m_warriorDatas.push_back(initData);
}

////////////////////////////////////////mode_trackingStateChange����

void EnemyAIMetaWarrior::CallWarrior()
{

	if (m_enemyWarriorList[0] == nullptr)
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
			ptr->m_isCallCompliedWarrior = true;
		}
	}

	//�G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����
	ChangeTrackingState();
}

void EnemyAIMetaWarrior::ChangeTrackingState()
{

	//������荞�݃X�e�[�g�̃G�l�~�[�����݂��Ă��邩
	bool existsWrapAroundWarrior = false;

	//��ꔭ���G�l�~�[�͂Ƃ肠������납��ǂ킹��
	m_MainCallWarrior->SetTrackingState(WarriorTrackingState::en_chaseFromBehind);

	//�͈�for���ŉ�
	for (auto& ptr : m_enemyWarriorList)
	{

		//�����̃A�h���X�Ɠ�����������
		if (m_MainCallWarrior == ptr->m_warriorPtr)
		{
			//�������΂�
			continue;
		}
		
		//�C�e���[�^�[�̃E�H���A�[���Ăт�����ꂽ�E�H���A�[��������
		if (ptr->m_isCallCompliedWarrior == true)
		{
			//��荞�݃X�e�[�g�̃E�H���A�[�����݂��Ă�����
			if (existsWrapAroundWarrior == true)
			{
				//��납��ǂ킹��
				ptr->m_warriorPtr->SetTrackingState(WarriorTrackingState::en_wrapAround);
				ptr->m_warriorPtr->SetState(EnemySM_Warrior::en_warrior_trackingMetaAI);
				continue;
			}
			//��荞�݃X�e�[�g�̃E�H���A�[���܂����݂��Ȃ�������

			//��荞�܂���
			ptr->m_warriorPtr->SetTrackingState(WarriorTrackingState::en_wrapAround);
			ptr->m_warriorPtr->SetState(EnemySM_Warrior::en_warrior_trackingMetaAI);

			//�t���O��true��
			existsWrapAroundWarrior = true;
		}

	}

}

////////////////////////////////////////

void EnemyAIMetaWarrior::WarriorRangeCalc()
{

	//�v���C���[�̈ʒu���擾
	Vector3 playerPos = m_player->GetPosition();
	//�E�H���A�[�̈ʒu���擾����ϐ���錾
	Vector3 warriorPos;
	//�E�H���A�[����v���C���[�ɐL�т�x�N�g��
	Vector3 warriorToPlayerVec;
	//�E�H���A�[�ƃv���C���[�̋���
	float warriorToPlayerDis;
	//������r�p�ϐ�
	float distanceComparisonMax = 0.0f;

	//�E�H���A�[�̑S�̂̋����𑪂�z��Ɋi�[����
	for (int i = 0; i < WARRIOR_NUM; i++)
	{
		
		//�E�H���A�[�̈ʒu���擾
		warriorPos = m_enemyWarriorList[i]->m_warriorPtr->GetEnemyPtr().GetPosition();

		//�܂��E�H���A�[����v���C���[�ɐL�т�x�N�g�����v�Z
		warriorToPlayerVec = playerPos - warriorPos;

		//�E�H���A�[����v���C���[�ɐL�т�x�N�g�����狗�����v�Z
		warriorToPlayerDis = warriorToPlayerVec.Length();

		m_warriorDistanceList[i] = warriorToPlayerDis;

	}

	//�������X�g�̒��g���~���ɕ��בւ���
	//�z��̃T�C�Y���擾����
	int listSize = sizeof(m_warriorDistanceList) / sizeof(m_warriorDistanceList[0]);
	
	//�~���ɕ��בւ���
	std::sort(m_warriorDistanceList,
		m_warriorDistanceList + listSize,std::greater<float>());



}

void EnemyAIMetaWarrior::ProcessEnd()
{
	//�����t���O���I���ɂ���
	m_isCurrentlyProcessed = false;

	//�S���̒ǐՃX�e�[�g���ǐՏ�Ԃɂ���
	for (auto& ptr : m_enemyWarriorList)
	{
		ptr->m_warriorPtr->SetTrackingState(WarriorTrackingState::en_nonTracking);
	}
}