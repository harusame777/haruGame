#include "stdafx.h"
#include "Crystal.h"
#include "Player.h"

//�R���X�g���N�^
Crystal::Crystal()
{

}

//�f�X�g���N�^
Crystal::~Crystal()
{

}

//�X�^�[�g�֐�
bool Crystal::Start()
{

	//�N���X�^��01�����f���ɐݒ�
	m_mainModel.Init("Assets/modelData/objects/crystal/crystal01_Model.tkm", nullptr, 0, enModelUpAxisZ, true);

	//�V���h�E�}�b�v�ɕ`�悷��悤�ɂ���
	m_mainModel.SetShadowChasterFlag(true);

	//���W��ݒ�
	m_mainModel.SetPosition(m_position);
	//��]��ݒ�
	m_mainModel.SetRotation(m_rotation);
	//�g�嗦��ݒ�
	m_mainModel.SetScale(m_scale);
	//�����ݒ���m��
	m_mainModel.Update();

	//�v���C���[�̃C���X�^���X���擾����
	m_player = FindGO<Player>("player");

	//�R���C�_�[������������
	m_sphereCollider.Create(1.0f);

	return true;
}

//�A�b�v�f�[�g�֐�
void Crystal::Update()
{
	//�N���X�^���擾����
	GetCrystal();
	//�`��X�V
	m_mainModel.Update();
}

//�����_�[�֐�
void Crystal::Render(RenderContext& rc)
{
	//�擾����Ă��Ȃ�������
	if (m_isGetObject)
	{
		//�`�悵�Ȃ�
		m_mainModel.Draw(rc);
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

bool Crystal::RayTestWall()
{
	//�ǉz���Ɍ����Ȃ��悤�Ƀ��C���g�p���ĕǂ̔�������
	//�R���C�_�[�̎n�_�ƏI�_��������
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();

	//�n�_�ʒu����
	Vector3 startPos = GetPosition();
	startPos.y += 70.0f;
	start.setOrigin(btVector3(startPos.x, startPos.y, startPos.z));

	//�I�_�ʒu����
	Vector3 endPos = m_player->GetPosition();
	endPos.y += 70.0f;
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

void Crystal::GetCrystal()
{

}