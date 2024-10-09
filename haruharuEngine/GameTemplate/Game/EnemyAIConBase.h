#pragma once

class EnemyBase;

class EnemyAIConBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyAIConBase() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EnemyAIConBase() 
	{

	};
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	virtual void Start()
	{

	};
	/// <summary>
	/// �������s
	/// </summary>
	/// <returns></returns>
	virtual bool Execution() 
	{
		return true;
	};
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
protected:
	/// <summary>
	/// ���̃v���O�����ɕR�Â��Ă���G�l�~�[
	/// </summary>
	EnemyBase* m_enemy = nullptr;
};

