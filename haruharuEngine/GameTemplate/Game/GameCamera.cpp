#include "stdafx.h"
#include "GameCamera.h"
#include "Game.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	m_game = FindGO<Game>("game");

	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(0.0f, 150.0f, -400.0f);
	m_toCameraPos *= 0.5;


	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);

	return true;
}
void GameCamera::Update()
{
	//�J�������X�V�B
	//�����_���v�Z����B
	Vector3 target;
	target.x = m_game->m_modelTestPos.x;
	//y���W�������グ��B
	target.y = m_game->m_modelTestPos.y + 100.0f;
	target.z = m_game->m_modelTestPos.z;

	Vector3 toCameraPosOld = target;
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPos);
	//X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * y);
	qRot.Apply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	//if (toPosDir.y < -0.2f) {
	//	//�J����������������B
	//	m_toCameraPos = toCameraPosOld;
	//}
	//else if (toPosDir.y > 0.9f) {
	//	//�J�����������������B
	//	m_toCameraPos = toCameraPosOld;
	//}

	//���_���v�Z����B
	Vector3 pos = target + m_toCameraPos;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//�J�����̍X�V�B
	g_camera3D->Update();
}