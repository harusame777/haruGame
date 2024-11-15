#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"

class EnemyAIConBase;
class EnemyBase;

class EnemyAIMetaBase : public EnemyAIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyAIMetaBase() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EnemyAIMetaBase(){}
	/// <summary>
	/// ���^AI�̏�����
	/// </summary>
	virtual void MetaAIInit() = 0;
	/// <summary>
	/// ���^AI���s
	/// </summary>
	virtual void MetaAIExecution(EnemySMBase* initEnemy) = 0;
	/// <summary>
	///	�����I��
	/// </summary>
	virtual const bool ProcessEnd(EnemySMBase* initEnemy) = 0;
	/// <summary>
	/// ���N���������ǂ����̃t���O
	/// </summary>
	bool m_isOneTimeUpdateFlag = false;
	/// <summary>
	/// ���v���O�������N���������ǂ�����ݒ�
	/// </summary>
	/// <param name="is"></param>
	void SetOneTimeUpdateFlag(const bool is)
	{
		m_isOneTimeUpdateFlag = is;
	}
	/// <summary>
	/// ���v���O�������N���������ǂ������擾
	/// </summary>
	/// <returns></returns>
	const bool GetOneTimeUpdateFlag() const
	{
		return m_isOneTimeUpdateFlag;
	}
};

