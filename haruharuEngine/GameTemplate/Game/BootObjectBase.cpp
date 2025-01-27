#include "stdafx.h"
#include "BootObjectBase.h"
#include "Player.h"

//�萔��
namespace {
	/// <summary>
	/// �擾�����̌v�Z�Ɏg�����
	/// </summary>
	static const float GET_RANGE_CALC = 90.0f;
}

//�������֐�
void BootObjectBase::InitBootObject(const char* filePath)
{
	//�R���C�_�[������������
	m_sphereCollider.Create(0.1f);

	m_bootPlayer = FindGO<Player>("player");

	m_getBootPosition.Init(filePath, [&](LevelObjectData_Render& objData)
		{
			if (objData.EqualObjectName(L"bootPosition") == true)
			{

				m_levelPosition = objData.m_position;

				return true;
			}
			return true;
		});

	m_bootPosition = m_levelPosition + m_position;
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

//�I�u�W�F�N�g���N���ł�������ɂ��邩�ǂ������ׂ�֐�
const bool BootObjectBase::IsObjectBootConditions()
{
	if (IsObjectBootingRange() == true &&
		IsObjectBootingCameraVector() == true &&
		IsRayTestWall() == false)
	{
		return true;
	}

	return false;
}

//�I�u�W�F�N�g���N���\�J�����x�N�^�[�������ɂ��邩�ǂ������ׂ�֐�
const bool BootObjectBase::IsObjectBootingCameraVector()
{
	//�J�����̐��ʃx�N�g�����擾
	Vector3 camForward = g_camera3D->GetForward();

	//�v���C���[�̍��W���擾
	Vector3 playerPos = g_camera3D->GetPosition();

	//�v���C���[�̍��W���玩�g�̍��W��������
	//���g����v���C���[�֐L�т�x�N�g�����v�Z����
	Vector3 diff = playerPos - GetBootPosition();

	//���K�����ĒP�ʃx�N�g���ɂ���
	diff.Normalize();

	//���ς��v�Z���A�������𑪂�
	float similarity = Dot(camForward, diff);

	//����-0.95������������������������
	if (similarity <= -0.95)
	{
		//true��Ԃ�
		return true;
	}

	return false;
}

//�I�u�W�F�N�g���N���\�Ȕ͈͓����W�ɂ��邩�ǂ����𒲂ׂ�֐�
const bool BootObjectBase::IsObjectBootingRange()
{
	//�v���C���[�̍��W���擾
	Vector3 playerPos = m_bootPlayer->GetPosition();

	//�v���C���[�̍��W���玩�g�̍��W��������
	//���g����v���C���[�֐L�т�x�N�g�����v�Z����
	Vector3 diff = playerPos - GetBootPosition();

	//���g����v���C���[�֐L�т�x�N�g���̂Q����v�Z����
	float range = diff.LengthSq();

	//�����擾�͈͓���������
	if (range <= GET_RANGE_CALC * GET_RANGE_CALC)
	{
		//true��Ԃ�
		return true;
	}

	return false;
}

const bool BootObjectBase::IsRayTestWall()
{
	//�ǉz���Ɍ����Ȃ��悤�Ƀ��C���g�p���ĕǂ̔�������
//�R���C�_�[�̎n�_�ƏI�_��������
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();

	//�n�_�ʒu����
	Vector3 startPos = m_bootPlayer->GetPosition();
	startPos.y += 70.0;
	start.setOrigin(btVector3(startPos.x, startPos.y, startPos.z));

	//�I�_�ʒu����
	Vector3 endPos = GetBootPosition();
	endPos.y += 5.0f;
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