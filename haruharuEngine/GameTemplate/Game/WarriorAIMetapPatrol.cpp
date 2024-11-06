#include "stdafx.h"
#include "WarriorAIMetapPatrol.h"
#include "Player.h"

//�萔��
namespace {
	/// <summary>
	/// �E�H���A�[�̍ő吔
	/// </summary>
	static const int WARRIOR_NUM = 3;
}

//���^AI�̏�����
void WarriorAIMetapPatrol::MetaAIInit()
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
}

//���^AI�̎��s
void WarriorAIMetapPatrol::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;
}

void WarriorAIMetapPatrol::WarriorRangeCalc()
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
		warriorPos = m_sharedWarriorDatas->m_warriorDatas[i]->GetEnemyPtr().GetPosition();

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
		m_warriorDistanceList + listSize, std::greater<float>());

	

}