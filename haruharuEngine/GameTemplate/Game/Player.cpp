#include "stdafx.h"
#include "Player.h"

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

}