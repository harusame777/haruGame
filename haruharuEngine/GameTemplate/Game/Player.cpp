#include "stdafx.h"
#include "Player.h"

//�萔��
namespace {
	//�������̃v���C���[�̃X�s�[�h
	const static float playerSpeedWalk = 150.0f;
	//���莞�̃v���C���[�̃X�s�[�h
	const static float playerSpeedRun = 300.0f;
}

//�R���X�g���N�^
Player::Player()
{

}

//�f�X�g���N�^
Player::~Player()
{

}

//�X�^�[�g�֐�
bool Player::Start()
{
	//�L�����N�^�[�R���g���[���[��������
	m_CController.Init(25.0f, 75.0f, m_position);

	//�ʒu�̏����ݒ�
	m_CController.SetPosition(m_position);

	return true;
}

//�A�b�v�f�[�g�֐�
void Player::Update()
{
	//�ړ��֐�
	Move();
}

//�ړ��֐�
void Player::Move()
{
	//�v���C���[��������Ԃ������ԉ��𒲂ׂ�
	//���x��I������
	IsWalkOrRun();

	//�ړ����x��������
	m_moveVector.x = 0.0f;
	m_moveVector.z = 0.0f;

	//���̃t���[���̈ړ��ʂ����߂�B
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveVector += cameraForward * lStick_y * m_moveSpeed;	//�������ւ̈ړ����x�����Z�B
	m_moveVector += cameraRight * lStick_x * m_moveSpeed;		//�E�����ւ̈ړ����x�����Z�B
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	m_position = m_CController.Execute(m_moveVector, g_gameTime->GetFrameDeltaTime());
}

//�v���C���[�������Ԃ�������ԉ��𒲂ׂ�֐�
void Player::IsWalkOrRun()
{
	if (g_pad[0]->IsPress(enButtonRB1))
	{
		m_moveSpeed = playerSpeedRun;
	}
	else
	{
		m_moveSpeed = playerSpeedWalk;
	}
}