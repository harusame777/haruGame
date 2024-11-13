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
	virtual void ProcessEnd() = 0;
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
		m_isOneTimeUpdateFlag = isalnum;
	}
	/// <summary>
	/// ���v���O�������N���������ǂ������擾
	/// </summary>
	/// <returns></returns>
	const bool GetOneTimeUpdateFlag() const
	{
		return m_isOneTimeUpdateFlag;
	}
	/// <summary>
	/// �������I���������ǂ����̃t���O
	/// </summary>
	bool m_isProcessEndFlag = false;
	/// <summary>
	/// �������I���������ǂ�����ݒ�
	/// </summary>
	/// <param name="is"></param>
	void SetProcessEndFlag(const bool is)
	{
		m_isProcessEndFlag = false;
	}
	/// <summary>
	/// �������I���������ǂ������擾
	/// </summary>
	/// <returns></returns>
	const bool GetProcessEndFlag() const
	{
		return m_isProcessEndFlag;
	}
};

