#pragma once
#include "EnemyAIBase.h"

class EnemyAIConBase;
class EnemyBase;

class EnemySMBase : public virtual EnemyAIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemySMBase(){};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EnemySMBase() {};
protected:
	/// <summary>
	/// ���ʃX�e�[�g�ύX�֐�
	/// </summary>
	virtual void ChangeState() {};
	/// <summary>
	/// �������X�g
	/// </summary>
	std::vector<EnemyAIConBase*> m_enemyConList;
	/// <summary>
	/// �G�l�~�[��AI�v���O�����̃��X�g
	/// </summary>
	std::vector<EnemyAIBase*> m_EnemyAIList;
};
