#include "stdafx.h"
#include "WarriorAIMetaFootSteps.h"
#include "GameSound.h"
#include "Player.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"

//�萔��
namespace {

	static const float HIGH_VALUME_EXP = 3.0f;
	static const float MIDDLE_VALUME_EXP = 5.0f;
	static const float LOW_VALUME_EXP = 10.0f;
}

//���^AI�̏�����
void WarriorAIMetaFootSteps::MetaAIInit()
{
	m_player = FindGO<Player>("player");
	//�R���C�_�[��������
	m_sphereCollider.Create(1.0f);
}

//���^AI�̎��s
void WarriorAIMetaFootSteps::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	//�G�l�~�[�̐��擾
	m_enemyNum = m_sharedWarriorDatas->m_warriorDatas.size();

	if (m_enemyLengthDatas[0].m_enemyData == nullptr)
	{
		for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
		{
			m_enemyLengthDatas[enemyNo].m_enemyData
				= &m_sharedWarriorDatas->m_warriorDatas[enemyNo]->GetEnemyPtr();
		}

		return;
	}

	//�����f�[�^������
	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{
		m_enemyLengthDatas[enemyNo].m_length = 0.0f;

		m_enemyLengthDatas[enemyNo].m_priority = en_priority_non;
	}

	EnemyStateCheck();

	LengthCalc();

	DatasPriorityInit();

	DatasEnemyWallCheck();
}

void WarriorAIMetaFootSteps::EnemyStateCheck()
{

	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{

		m_enemyLengthDatas[enemyNo].m_warriorStateNum
			= m_enemyLengthDatas[enemyNo].m_enemyData->GetStateNumber();

		if (m_enemyLengthDatas[enemyNo].m_warriorStateNum
			!= EnemySM_Warrior::en_warrior_tracking &&
			m_enemyLengthDatas[enemyNo].m_warriorStateNum
			!= EnemySM_Warrior::en_warrior_trackingMetaAI)
		{
			m_enemyLengthDatas[enemyNo].m_enemyData
				->SetFootStepFlag(true);

			return;
		}
	}

}

//�����v�Z
void WarriorAIMetaFootSteps::LengthCalc()
{

	//�G�l�~�[�S�̂̃v���C���[�Ƃ̋����𑪂�
	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{
		
		Vector3 diff = m_player->GetPosition()
			- m_enemyLengthDatas[enemyNo].m_enemyData->GetPosition();

		m_enemyLengthDatas[enemyNo].m_length = diff.Length();

	}	

}

void WarriorAIMetaFootSteps::DatasPriorityInit()
{

	EnemyLength_Data* highData = nullptr;
	std::vector<EnemyLength_Data*> lowDatas;
	
	//�܂��擪�v�f�̃G�l�~�[����ԋ߂��G�l�~�[�Ɖے�����
	//�����Ċi�[�����f�[�^�Ƃق��̃f�[�^��
	//��ׂď���������high�ɑ������
	//low����̓�������
	highData = &m_enemyLengthDatas[0];
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{
		if (highData->m_length
			> m_enemyLengthDatas[enemyNo].m_length)
			highData = &m_enemyLengthDatas[enemyNo];
	}

	//�����Ă���ȊO�̃f�[�^��low�Ɏw��
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{
		if (&m_enemyLengthDatas[enemyNo] == highData)
			continue;
		else
			lowDatas.push_back(&m_enemyLengthDatas[enemyNo]);
	}

	//�ŏI�ݒ�
	highData->m_enemyData->SetFootStepFlag(true);

	for (auto& listData : lowDatas)
	{
		listData->m_enemyData->SetFootStepFlag(false);
	}
}


//�ǂ̔�������\����
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	/// <summary>
	/// �Ώۑ����Ƀ��C�������������ǂ���
	/// </summary>
	bool isHit = false;
	/// <summary>
	///	����
	/// </summary>
	/// <param name="covexResult"></param>
	/// <param name="normalInWorldSpace"></param>
	/// <returns></returns>
	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& covexResult,
		bool normalInWorldSpace)
	{
		//�ǂƂԂ����Ă��Ȃ�������
		if (covexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall)
		{
			//�Փ˂����͕̂ǂł͂Ȃ�
			return 0.0f;
		}

		//�ǂƂԂ����Ă���t���O��true�ɂ���
		isHit = true;
		return 0.0f;
	}
};

const bool& WarriorAIMetaFootSteps::RayTestWall(EnemyBase* initEnemy)
{
	//�ǉz���Ɍ����Ȃ��悤�Ƀ��C���g�p���ĕǂ̔�������
	//�R���C�_�[�̎n�_�ƏI�_��������
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();

	//�n�_�ʒu����
	Vector3 startPos = initEnemy->GetPosition();
	startPos.y += 70.0f;
	start.setOrigin(btVector3(startPos.x, startPos.y, startPos.z));

	//�I�_�ʒu����
	Vector3 endPos = m_player->GetPosition();
	endPos.y += 75.0f;
	end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));

	SweepResultWall callback;

	//�Փˌ��o
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(),
		start, end, callback);
	if (callback.isHit) {
		//��������
		return true;
	}

	//�������ĂȂ�
	return false;
}

const bool& WarriorAIMetaFootSteps::IsinCamera(EnemyBase* initEnemy)
{

	Vector3 diff = initEnemy->GetPosition() - g_camera3D->GetPosition();

	//�G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K��
	diff.Normalize();
	//�G�l�~�[�̐��ʃx�N�g���ƁA�G����v���C���[�Ɍ������x�N�g����
	//����(cos��)�����߂�B
	float cos = g_camera3D->GetForward().Dot(diff);
	if (cos >= 1)
	{
		cos = 1.0f;
	}
	//����(cos��)����p�x(��)�����߂�
	float angle = acosf(cos);
	//�p�x(��)��90��(����p)��菬�������
	if (angle <= (Math::PI / 180.0f) * 90.0f)
	{

		return true;

	}

	return false;

}

void WarriorAIMetaFootSteps::DatasEnemyWallCheck()
{
	
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{

		if (RayTestWall(m_enemyLengthDatas[enemyNo].m_enemyData))
		{
			m_enemyLengthDatas[enemyNo].m_enemyData->SetValumeCalcValue(LOW_VALUME_EXP);

			continue;
		}

		if (IsinCamera(m_enemyLengthDatas[enemyNo].m_enemyData))
		{
			m_enemyLengthDatas[enemyNo].m_enemyData->SetValumeCalcValue(HIGH_VALUME_EXP);

			continue;
		}

		m_enemyLengthDatas[enemyNo].m_enemyData->SetValumeCalcValue(MIDDLE_VALUME_EXP);

	}
}

//�����I��
const bool WarriorAIMetaFootSteps::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}
