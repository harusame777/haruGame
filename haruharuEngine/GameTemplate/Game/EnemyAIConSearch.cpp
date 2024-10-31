#include "stdafx.h"
#include "EnemyAIConSearch.h"
#include "EnemyBase.h"
#include "Player.h"

//�X�^�[�g�֐�
void EnemyAIConSearch::Start()
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

bool EnemyAIConSearch::RayTestWall()
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

//����p
bool EnemyAIConSearch::AngleCheck()
{
	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����v�Z
	Vector3 diff = m_player->GetPosition() - GetEnemyPtr().GetPosition();

	//�v���C���[�ɂ�����x�߂�������
	//�G�l�~�[�̍��G�͈́A���݂�500*500
	if (diff.LengthSq() <= m_enemySearchRad * m_enemySearchRad)
	{
		 //�G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K��
		diff.Normalize();
		//�G�l�~�[�̐��ʃx�N�g���ƁA�G����v���C���[�Ɍ������x�N�g����
		//����(cos��)�����߂�B
		float cos = GetEnemyPtr().GetFoward().Dot(diff);
		if (cos >= 1)
		{
			cos = 1.0f;
		}
		//����(cos��)����p�x(��)�����߂�
		float angle = acosf(cos);
		//�p�x(��)��90��(����p)��菬�������
		if (angle <= (Math::PI / 180.0f) * m_viewingAngle)
		{
			//�ǂ�����������
			if (!RayTestWall())
			{
				//���������I
				return true;
			}
		}
	}

	//������Ȃ������c
	return false;
}

//�������s
bool EnemyAIConSearch::Execution()
{
	if (AngleCheck())
	{
		return true;
	}

	return false;
}

