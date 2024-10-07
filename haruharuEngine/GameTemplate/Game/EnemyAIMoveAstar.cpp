#include "stdafx.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyBase.h"

//�A�b�v�f�[�g�֐�
void EnemyAIMoveAstar::Update()
{
	m_nvmMesh.Init("Assets/nvm/test.tkn");

	bool isEnd;

	//�������g�̈ʒu���擾
	Vector3 myPos = GetEnemyPtr().GetPosition();
	
	//�ړ���̈ʒu���擾
	Vector3 tarPos = GetEnemyPtr().GetMoveTargetPosition();

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

	//�p�X����ړ�����
	//�ړ�����v�Z
	Vector3 pathMovePos = m_path.Move(
		myPos,
		10.0f,
		isEnd
	);

	//�ړ��������W�𑗂�
	GetEnemyPtr().SetPosition(pathMovePos);
}