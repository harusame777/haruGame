#include "stdafx.h"
#include "Player.h"
#include "PlayerStaminaUi.h"
#include "Game.h"
#include "GameSound.h"

//�萔��
namespace {
	//�������̃v���C���[�̃X�s�[�h
	const static float playerSpeedWalk = 150.0f;
	//���莞�̃v���C���[�̃X�s�[�h
	const static float playerSpeedRun = 300.0f;

	const static float TIMER_MAX = 0.5;
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
	m_CController.Init(10.0f, 20.0f, m_position);

	//�ʒu�̏����ݒ�
	m_CController.SetPosition(m_position);

	m_playerStaminaUi = FindGO<PlayerStaminaUi>("StaminaUI");

	m_game = FindGO<Game>("game");

	m_gameSound = FindGO<GameSound>("gameSound");
	
	m_playerStaminaUi->InitPlayerStaminaPtr(&m_stamina);

	return true;
}

//�A�b�v�f�[�g�֐�
void Player::Update()
{
	//�ړ��֐�
	Move();
	//���ʒl��ݒ�
	SetForward(g_camera3D->GetForward());
	//������炷
	FootSteps();
}

//�ړ��֐�
void Player::Move()
{
	if (m_game->GetGameInState() == Game::en_gameOver)
	{
		return;
	}

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
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();

	bool stick_move = false;

	if (lStick_x > 0.0f ||
		lStick_x < 0.0f ||
		lStick_y > 0.0f ||
		lStick_y < 0.0f)
	{
		stick_move = true;
	}
	
	if (stick_move == true &&
		g_pad[0]->IsPress(enButtonRB1) && 
		m_isStaminaOut == false)
	{
		m_moveSpeed = playerSpeedRun;
		m_isPlayerRun = true;

		m_stamina--;

		if (0 >= m_stamina)
		{
			m_stamina = 0;

			m_isStaminaOut = true;
		}
	}
	else
	{
		m_moveSpeed = playerSpeedWalk;
		m_isPlayerRun = false;

		if (m_isStaminaOut == true)
			m_stamina += 0.5f;
		else
			m_stamina++;

		if (100 <= m_stamina)
		{
			m_stamina = 100;

			m_isStaminaOut = false;
		}
	}
}

//��������
void Player::FootSteps()
{
	//�X�e�B�b�N�̓��͒l���擾
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();

	//�X�e�B�b�N�����͂���Ă��Ȃ�������
	if (lStick_x <= 0.0f &&
		lStick_x >= 0.0f &&
		lStick_y <= 0.0f &&
		lStick_y >= 0.0f)
	{
		//�^�C�}�[��������
		m_footStepsTimer = TIMER_MAX;
		//�Ԃ�
		return;
	}

	//�v���C���[�������Ă�����
	if (m_isPlayerRun == true)
		m_footStepsTimer -= g_gameTime->GetFrameDeltaTime() * 2;
	else
		m_footStepsTimer -= g_gameTime->GetFrameDeltaTime();

	//�^�C�}�[��0�b�ȉ��ł�������
	if (m_footStepsTimer < 0.0f)
	{
		//�^�C�}�[��������
		m_footStepsTimer = TIMER_MAX;
		//������炷
		m_gameSound->LocalSoundOrder(GameSound::en_playerWalkSound,false,0.5f);
	}
}