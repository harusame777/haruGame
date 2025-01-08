#pragma once
class Gameover : public IGameObject
{
private:
	/// <summary>
	/// �Q�[���I�[�o�[�X�e�[�g
	/// </summary>
	enum GameoverState
	{
		en_standby,

		en_cameraEasing,

		en_enemyAnimation,
	};
	GameoverState m_gameoverState = GameoverState::en_standby;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Gameover() {}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Gameover(){}
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
	/// �Q�[���I�[�o�[�X�e�[�g�A�b�v�f�[�g
	/// </summary>
	void GameoverStateUpdate();
	/// <summary>
	/// �J�����̃C�[�W���O����
	/// </summary>
	/// <returns></returns>
	const bool& CameraEasing();
	/// <summary>
	/// �J�����̃C�[�W���O�Ɏg���֐�
	/// </summary>
	Vector3 m_cameraToTargetDir;
	Vector3 m_cameraToWarriorDir;
	Quaternion m_startRotation;
	Quaternion m_endRotation;
	Quaternion m_finalQu;
	Vector3 m_startPos;
	Vector3 m_endPos;
	float m_cameraEasingRatio;
	Vector3 m_finalVector;
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ��둤�̃X�v���C�g
	/// </summary>
	SpriteRender  m_backSideSprite;
};

