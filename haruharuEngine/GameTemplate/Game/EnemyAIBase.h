#pragma once

class EnemyBase;

class EnemyAIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyAIBase(){};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EnemyAIBase(){};
public:
	/// <summary>
	/// �G�l�~�[��R�Â�
	/// </summary>
	/// <param name="enemy"></param>
	void BinedEnemy(EnemyBase* enemypt)
	{
		m_enemy = enemypt;
	}
	/// <summary>
	/// �R�Â��Ă���G�l�~�[���擾
	/// </summary>
	/// <returns></returns>
	EnemyBase& GetEnemyPtr()
	{
		return *m_enemy;
	}
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	virtual void Start() {};
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	virtual void Update() {};
	/// <summary>
	/// ���̃v���O�����ɕR�Â��Ă���G�l�~�[
	/// </summary>
	EnemyBase* m_enemy = nullptr;
};

