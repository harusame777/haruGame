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
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	virtual void EnemyAIStart() {};
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	virtual void EnemyAIUpdate() {};
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

