#pragma once

class EnemyBase;
class Load;
class GameSound;

class Gameover : public IGameObject
{
public:
	enum GameoverInitState
	{
		en_initKillEnemy,

		en_initKillOxygen,

		en_null
	};
private:
	GameoverInitState m_gameoverInitState = GameoverInitState::en_null;
	/// <summary>
	/// �Q�[���I�[�o�[�X�e�[�g
	/// </summary>
	enum GameoverState
	{
		en_standby,

		en_cameraEasing,

		en_enemyAnimation,

		en_gameoverDraw,
		
		en_gameoverEnd,
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

	void InitGameoverInitState(const GameoverInitState initState)
	{
		m_gameoverInitState = initState;
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
	/// �Q�[���I�[�o�[�X�e�[�g�A�b�v�f�[�g
	/// </summary>
	void GameoverStateUpdate();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �t�F�[�h�A�E�g�t���O
	/// </summary>
	bool m_fadeOutFlag = false;
	/// <summary>
	/// �Ó]������
	/// </summary>
	bool m_killEndFlag = false;
	/// <summary>
	/// ��둤�̃X�v���C�g
	/// </summary>
	SpriteRender  m_backSideSprite;
	/// <summary>
	/// ���C������
	/// </summary>
	FontRender m_mainFont;
	/// <summary>
	/// �T�u����
	/// </summary>
	FontRender m_subFont;
	/// <summary>
	/// gameover����
	/// </summary>
	FontRender m_gameoverFont;
	/// <summary>
	/// ��둤�̃X�v���C�g��`�悷�邩�ǂ���
	/// </summary>
	bool m_backSideSpriteDrawFlag = false;
	/// <summary>
	/// �U���G�l�~�[
	/// </summary>
	EnemyBase* m_attackEnemy = nullptr;
	/// <summary>
	/// ���[�h�C���X�^���X
	/// </summary>
	Load* m_load = nullptr;
	/// <summary>
	/// �Q�[���T�E���h
	/// </summary>
	GameSound* m_gameSound = nullptr;
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
	/// <summary>
	/// �Ó]���邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="flag"></param>
	void SetFadeOutFlag(const bool& flag)
	{
		m_fadeOutFlag = flag;
	}
	/// <summary>
	/// �Ó]���邩�ǂ������擾
	/// </summary>
	/// <returns></returns>
	const bool& GetFadeOutFlag() const
	{
		return m_fadeOutFlag;
	}
	/// <summary>
	/// �Q�[���I�[�o�[���I���������ǂ���
	/// </summary>
	/// <returns></returns>
	const bool& GetGameoverEnd() const
	{
		if (m_gameoverState == GameoverState::en_gameoverEnd)
		{
			return true;
		}

		return false;
	}
	/// <summary>
	/// ��둤�̃X�v���C�g��`�悷�邩�ǂ���
	/// </summary>
	/// <param name="flag"></param>
	void BackSideSpriteDraw(const bool& flag)
	{
		m_backSideSpriteDrawFlag = flag;
	}
};

