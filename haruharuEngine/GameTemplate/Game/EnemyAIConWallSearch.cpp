#include "stdafx.h"
#include "EnemyAIConWallSearch.h"
#include "EnemyBase.h"
#include "Player.h"

//�X�^�[�g�֐�
void EnemyAIConWallSearch::InitData()
{
	//�v���C���[�̃C���X�^���X���擾
	m_player = FindGO<Player>("player");
	//�R���C�_�[��������
	m_sphereCollider.Create(1.0f);
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

bool EnemyAIConWallSearch::RayTestWall()
{
	//�ǉz���Ɍ����Ȃ��悤�Ƀ��C���g�p���ĕǂ̔�������
	//�R���C�_�[�̎n�_�ƏI�_��������
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();

	//�n�_�ʒu����
	Vector3 startPos = GetEnemyPtr().GetPosition();
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

//�������s
bool EnemyAIConWallSearch::Execution()
{
	if (RayTestWall())
	{
		return true;
	}

	return false;
}