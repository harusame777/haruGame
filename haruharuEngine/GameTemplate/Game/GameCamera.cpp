#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

//�萔��
namespace {
	static const float FPSInitToCameraPos_Y = 55.0f;
	static const float FPSInitToCameraPos_Z = -250.0f;
	static const float TPSInitToCameraPos_Y = 125.0f;
	static const float TPSInitToCameraPos_Z = -450.0f;

	static const float CameraRotSpeed = 3.0f;
}

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
	m_toCameraPos.Set(0.0f, FPSInitToCameraPos_Y, FPSInitToCameraPos_Z);

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
#ifdef _DEBUG
	//�J�����̃��[�h�ؑւ̏���
	CamFPSorTPS();
	//TPS�J�����̏���
	TPSCam();
#endif // DEBUG_MODE
	//FPS�J�����̏���
	NewFPSCam();
}

//FPS�J�����̊֐�
void GameCamera::FPSCam()
{
#ifdef _DEBUG 
	if (m_camMode != en_camModeFPS)
	{
		return;
	}
#endif // DEBUG_MODE 

	//�����_���v�Z
	Vector3 target = m_player->GetPosition();

	target.y += 55.0f;
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
	qRot.SetRotationDeg(Vector3::AxisY, CameraRotSpeed * PadX);
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
		qRot.SetRotationDeg(axisX, -CameraRotSpeed * PadY);
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

void GameCamera::NewFPSCam()
{

	//���_���쐬
	Vector3 newCamPos = m_player->GetPosition();

	newCamPos.y += 55.0f;
	newCamPos.z -= 0.01f;

	//�Â��J�����̒����_���擾
	Vector3 oldCamPos = m_toCameraPos;

	//�p�b�h�̓��͂��擾
	//�p�b�h��X��
	float PadX = g_pad[0]->GetRStickXF();
	//�p�b�h��Y��
	float PadY = g_pad[0]->GetRStickYF();

	//�p�b�hY�̓��͂��Ȃ����
	if (PadY == 0.0f)
	{
		//���x�����Z�b�g
		m_velocityY = 0.0f;
	}

	//�p�b�hX�̓��͂��Ȃ����
	if (PadX == 0.0f)
	{
		//���x�����Z�b�g
		m_velocityX = 0.0f;
	}

	//Y�����̉�]
	
	//�������̉�]�����쐬
	//m_camRotation.SetRotationDeg(
	//	Vector3::AxisY,
	//	SmoothDamp(
	//		m_camRotation.y
	//		,m_camRotation.y + PadX * 3.0f,
	//		m_velocityX,
	//		1.0f));

	Quaternion rotX;
	Quaternion rotY;

	m_oldFramePadX = Leap(PadX, m_oldFramePadX, 0.5f);

	rotX.SetRotationDeg(Vector3::AxisY, 3.0f * m_oldFramePadX);

	//�������̉�]���ɒ����_���王�_�܂ł̃x�N�g�������Z
	rotX.Apply(m_toCameraPos);

	//X�����̉�]s
	Vector3 axisX;
	//�p�b�h�̓��͂������
	if (PadY != 0.0f)
	{
		//Y���ƒ����_���王�_�܂ł̃x�N�g���̊O�ς��v�Z
		axisX.Cross(Vector3::AxisY, m_toCameraPos);
		//���K��
		axisX.Normalize();
		//�c�����̉�]�����쐬
		//m_camRotation.SetRotationDeg(axisX, SmoothDamp(
		//	m_camRotation.x,
		//	m_camRotation.x - PadY * 3.0f,
		//	m_velocityY,
		//	1.0f));

		m_oldFramePadY = Leap(-PadY, m_oldFramePadY, 0.5f);

		rotY.SetRotationDeg(axisX, 3.0f * m_oldFramePadY);
	}
	//�c�����̉�]���ɒ����_���王�_�܂ł̃x�N�g�������Z
	rotY.Apply(m_toCameraPos);

	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	if (toPosDir.y < -0.7f) {
		//�J����������������B
		m_toCameraPos = oldCamPos;
	}
	else if (toPosDir.y > 0.7f) {
		//�J�����������������B
		m_toCameraPos = oldCamPos;
	}

	//�����_���v�Z����B
	Vector3 targetPos = newCamPos + m_toCameraPos;

	//���_���X�V
	g_camera3D->SetTarget(targetPos);
	g_camera3D->SetPosition(newCamPos);
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
	g_camera3D->Update();
}

//TPS�J�����̏���
void GameCamera::TPSCam()
{
	if (m_camMode != en_camModeTPS)
	{
		return;
	}

	//�J�������X�V�B
	//�����_���v�Z����B
	Vector3 target = m_player->GetPosition();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 250.0f;
	target += g_camera3D->GetForward() * 20.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.5f * x);
	qRot.Apply(m_toCameraPos);
	//X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.5f * y);
	qRot.Apply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J����������������B
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.95f) {
		//�J�����������������B
		m_toCameraPos = toCameraPosOld;
	}

	//���_���v�Z����B
	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
	g_camera3D->Update();
}

//�f�o�b�O���̃J�����̃��[�h�ؑւ̊֐�
void GameCamera::CamFPSorTPS()
{
	if (g_pad[0]->IsTrigger(enButtonLB1))
	{
		if (m_camMode == en_camModeFPS)
		{
			m_camMode = en_camModeTPS;

			//�����_���王�_�܂ł̃x�N�g����ݒ�
			m_toCameraPos.Set(0.0f, TPSInitToCameraPos_Y, TPSInitToCameraPos_Z);
		}
		else if(m_camMode == en_camModeTPS)
		{
			m_camMode = en_camModeFPS;

			//�����_���王�_�܂ł̃x�N�g����ݒ�
			m_toCameraPos.Set(0.0f, FPSInitToCameraPos_Y, FPSInitToCameraPos_Z);
		}
	}
}

void GameCamera::SetCameraTarget(const Vector3& position)
{
	Vector3 cameraToPosVec = g_camera3D->GetPosition() - position;
	
	cameraToPosVec.Normalize();
	cameraToPosVec.y = 0.0f;

	float radian = atan2(cameraToPosVec.x, cameraToPosVec.z);

	float degree = radian * (180.0f / Math::PI);

	Quaternion rotX;

	rotX.SetRotationDeg(Vector3::AxisY, degree);

	m_toCameraPos.Set(
		0.0f,
		position.y,
		FPSInitToCameraPos_Z
	);

	rotX.Apply(m_toCameraPos);

	//�����_���v�Z����B
	Vector3 targetPos = g_camera3D->GetPosition() + m_toCameraPos;

	//���_���X�V
	g_camera3D->SetTarget(targetPos);
}