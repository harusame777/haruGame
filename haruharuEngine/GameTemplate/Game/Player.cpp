#include "stdafx.h"
#include "Player.h"

//�萔��
namespace {
	const static float playerSpeed = 250.0f;
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
	//�ړ����x��������
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

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
	m_moveSpeed += cameraForward * lStick_y * playerSpeed;	//�������ւ̈ړ����x�����Z�B
	m_moveSpeed += cameraRight * lStick_x * playerSpeed;		//�E�����ւ̈ړ����x�����Z�B
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	m_position = m_CController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
}