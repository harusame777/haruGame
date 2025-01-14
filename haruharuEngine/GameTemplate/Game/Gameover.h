#pragma once

class EnemyBase;
class Load;

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

		en_gameoverDraw,
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
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �Ó]������
	/// </summary>
	bool m_killEndFlag = false;
	/// <summary>
	/// ��둤�̃X�v���C�g
	/// </summary>
	SpriteRender  m_backSideSprite;
	/// <summary>
	/// �U���G�l�~�[
	/// </summary>
	EnemyBase* m_attackEnemy = nullptr;
	/// <summary>
	/// ���[�h�C���X�^���X
	/// </summary>
	Load* m_load = nullptr;
public:
	/// <summary>
	/// �Ó]�������ǂ�����ݒ�
	/// </summary>
	/// <param name="is"></param>
	void SetKillEndFlag(const bool& is)
	{
		m_killEndFlag = is;
	}
	/// <summary>
	/// �Ó]�������ǂ������擾
	/// </summary>
	/// <returns></returns>
	const bool& GetKillEndFlag() const
	{
		return m_killEndFlag;
	}
};

