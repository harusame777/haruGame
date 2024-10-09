#include "stdafx.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyBase.h"

//�����L���ɂ���ƃf�o�b�O���[�h�ɂȂ�
#define DEBUG_MODE

//�X�^�[�g�֐�
void EnemyAIMoveAstar::Start()
{
	m_nvmMesh.Init("Assets/nvm/test.tkn");
}

//�A�b�v�f�[�g�֐�
void EnemyAIMoveAstar::Update()
{

	bool isEnd;

	//�������g�̈ʒu���擾
	Vector3 myPos = GetEnemyPtr().GetPosition();
	
	//�ړ���̈ʒu���擾
	Vector3 tarPos = GetEnemyPtr().GetMoveTargetPosition();

#ifdef DEBUG_MODE
	if (g_pad[0]->IsPress(enButtonA))
	{
#endif
		//�p�X����������
		m_pathFiding.Execute(
			m_path,							//�\�z���ꂽ�p�X�̊i�[��
			m_nvmMesh,						//�i�r���b�V��
			myPos,							//�J�n���W
			tarPos,							//�ړ�����W
			PhysicsWorld::GetInstance(),	//�����G���W��
			50.0f,							//AI�G�[�W�����g�̔��a
			200.0f							//AI�G�[�W�F���g�̍���
		);
#ifdef DEBUG_MODE
	}
#endif

		//�p�X����ړ�����
		//�ړ�����v�Z
		Vector3 pathMovePos = m_path.Move(
			myPos,
			10.0f,
			isEnd
		);

		//��]����������̌v�Z
		Vector3 atan2CalcVec = pathMovePos - myPos;
		//���K������
		atan2CalcVec.Normalize();
		//Y�l��0�ɂ���
		atan2CalcVec.y = 0.0f;

		float angle = atan2(atan2CalcVec.x, atan2CalcVec.z);

		Quaternion finalRot;
		finalRot.SetRotation(Vector3::AxisY, angle);

		//�ړ��������W�𑗂�
		GetEnemyPtr().SetPosition(pathMovePos);

		//��]�l�𑗂�
		GetEnemyPtr().SetRotation(finalRot);

		//���ʒl
		Vector3 newForward = Vector3::AxisZ;

		GetEnemyPtr().GetRotation().Apply(newForward);

		GetEnemyPtr().SetForward(newForward);
}