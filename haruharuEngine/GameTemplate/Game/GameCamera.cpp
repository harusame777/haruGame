#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

//�R���X�g���N�^
GameCamera::GameCamera()
{
}

//�f�X�g���N�^
GameCamera::~GameCamera()
{

}

//�X�^�[�g�֐�
bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�
	m_toCameraPos.Set(0.0f, 125.0f, -250.0f);

	//�v���C���[�̃C���X�^���X��ݒ�
	m_player = FindGO<Player>("player");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ�
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);

	return true;
}

//�A�b�v�f�[�g�֐�
void GameCamera::Update()
{
	//�����_���v�Z
	Vector3 target = m_player->GetPosition();

	target.y += 90.0f;
	target.z -= 0.01f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//�p�b�h�̓��͂��擾
	//�p�b�h��X��
	float PadX = g_pad[0]->GetRStickXF();
	//�p�b�h��Y��
	float PadY = g_pad[0]->GetRStickYF();

	//Y�����̉�]
	Quaternion qRot;
	//�������̉�]�����쐬
	qRot.SetRotationDeg(Vector3::AxisY, 1.6f * PadX);
	//�������̉�]���ɒ����_���王�_�܂ł̃x�N�g�������Z
	qRot.Apply(m_toCameraPos);

	//X�����̉�]
	Vector3 axisX;
	//�p�b�h�̓��͂������
	if (PadY != 0.0f)
	{
		//Y���ƒ����_���王�_�܂ł̃x�N�g���̊O�ς��v�Z
		axisX.Cross(Vector3::AxisY, m_toCameraPos);
		//���K��
		axisX.Normalize();
		//�c�����̉�]�����쐬
		qRot.SetRotationDeg(axisX, -1.6 * PadY);
	}
	//�c�����̉�]���ɒ����_���王�_�܂ł̃x�N�g�������Z
	qRot.Apply(m_toCameraPos);

	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	if (toPosDir.y < -0.7f) {
		//�J����������������B
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.7f) {
		//�J�����������������B
		m_toCameraPos = toCameraPosOld;
	}

	//���_���v�Z����
	Vector3 pos = target + m_toCameraPos;
	//���_���X�V
	g_camera3D->SetTarget(pos);
	g_camera3D->SetPosition(target);
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
	g_camera3D->Update();
}