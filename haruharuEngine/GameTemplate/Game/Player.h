#pragma once

class Game;
class PlayerStaminaUi;
class GameSound;

class Player : public IGameObject
{
public:

	enum PlayerState {

		en_move,

		en_lockerIn,
	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();
	/// <summary>
	/// �f�X�g���N�^�@
	/// </summary>
	~Player();
public:
	/// <summary>
	/// �ʒu�ݒ�
	/// </summary>
	/// <param name="pos = ���W"></param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// �ʒu�擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ��]�ݒ�
	/// </summary>
	/// <param name="rot = ��]"></param>
	void SetRotation(const Quaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]�擾
	/// </summary>
	/// <returns></returns>
	const Quaternion& GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// �g�嗦�ݒ�
	/// </summary>
	/// <param name="sca = �g�嗦"></param>
	void SetScale(const Vector3& sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// �g�嗦�擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetScale()
	{
		return m_scale;
	}
	/// <summary>
	/// ���ʃx�N�g���ݒ�
	/// </summary>
	/// <param name="forward = ���ʃx�N�g��"></param>
	void SetForward(const Vector3& forward)
	{
		m_forward = forward;
	}
	/// <summary>
	/// ���ʃx�N�g���擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetFoward()
	{
		return m_forward;
	}
	/// <summary>
	/// �L�����R�����擾
	/// </summary>
	/// <returns></returns>
	CharacterController& GetCharacterController()
	{
		return m_CController;
	}
	/// <summary>
	/// �v���C���[�̃X�e�[�g��ݒ�
	/// </summary>
	/// <param name="state"></param>
	void SetPlayerState(const PlayerState& state)
	{
		m_playerState = state;
	}
	/// <summary>
	/// �v���C���[�̃X�e�[�g���擾
	/// </summary>
	/// <returns></returns>
	const PlayerState GetPlayerState() const
	{
		return m_playerState;
	}
private:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �v���C���[�̃X�e�[�g�A�b�v�f�[�g
	/// </summary>
	void PlayerStateUpdate();
	/// <summary>
	/// �ړ��֐�
	/// </summary>
	void Move();
	/// <summary>
	/// �v���C���[�������Ԃ�������ԉ��𒲂ׂ�֐�
	/// </summary>
	void IsWalkOrRun();
	/// <summary>
	/// ��������
	/// </summary>
	void FootSteps();
	/// <summary>
	/// ���ݍ��W
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// ���݉�]�l
	/// </summary>
	Quaternion m_rotation;
	/// <summary>
	/// ���݊g��l
	/// </summary>
	Vector3 m_scale = Vector3::One;
	/// <summary>
	/// ���ݐ��ʃx�N�g��
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// ��{�ړ����x
	/// </summary>
	float m_moveSpeed;
	/// <summary>
	/// �X�^�~�i
	/// </summary>
	float m_stamina = 100.0f;
	/// <summary>
	/// �X�^�~�i�؂ꂩ�ǂ���
	/// </summary>
	bool m_isStaminaOut = false;
	/// <summary>
	/// �v���C���[�������Ă��邩�ǂ���
	/// </summary>
	bool m_isPlayerRun = false;
	/// <summary>
	/// �����̊��o�^�C�}�[
	/// </summary>
	float m_footStepsTimer = 0.0f;
	/// <summary>
	/// �ړ��x�N�g��
	/// </summary>
	Vector3 m_moveVector;
	/// <summary>
	/// �L�����R��
	/// </summary>
	CharacterController m_CController;
	/// <summary>
	/// �v���C���[�X�e�[�g
	/// </summary>
	PlayerState m_playerState = PlayerState::en_move;
	/// <summary>
	/// �v���C���[�̃X�^�~�iUI
	/// </summary>
	PlayerStaminaUi* m_playerStaminaUi = nullptr;
	/// <summary>
	/// �Q�[���̃C���X�^���X
	/// </summary>
	Game* m_game = nullptr;
	/// <summary>
	/// �Q�[���T�E���h
	/// </summary>
	GameSound* m_gameSound = nullptr;
};

