#pragma once
#include "stdafx.h"
#include "vector"
#include "EnemySMBase.h"

class PatrolRuteDataHolder
{
public:
	/// <summary>
	/// ���^AI�̏��񃋁[�g�̃f�[�^
	/// </summary>
	struct PatrolRuteData
	{
	private:
		/// <summary>
		/// ���̃��[�g���g�p���Ă���E�H���A�[�����݂��邩
		/// </summary>
		bool m_isUse = false;
		/// <summary>
		/// �I���n�_
		/// </summary>
		Vector3 m_patrolPos;
		/// <summary>
		/// ���̃|�C���g���g�p���̃G�l�~�[
		/// </summary>
		EnemySMBase* m_useEnemy = nullptr;
	public:
		void SetPosition(const Vector3& pos)
		{
			m_patrolPos = pos;
		}
		const Vector3& GetPosition()
		{
			return m_patrolPos;
		}
		void SetIsUse(const bool& is)
		{
			m_isUse = is;
		}
		const bool GetIsUse() const
		{
			return m_isUse;
		}
		void SetUseEnemyPtr(EnemySMBase* enemyPtr)
		{
			m_useEnemy = enemyPtr;
		}
		EnemySMBase* GetUseEnemyPtr()
		{
			return m_useEnemy;
		}
	};
	/// <summary>
	/// �p�g���[�����[�g�̃��X�g
	/// </summary>
	std::vector<PatrolRuteData*> m_patrolRuteList;
	/// <summary>
	/// ���[�g�f�[�^�̏�����
	/// </summary>
	/// <param name="data"></param>
	void InitRuteData(PatrolRuteData* data)
	{
		m_patrolRuteList.push_back(data);
	}
	/// <summary>
	/// ���[�g�f�[�^�̎擾
	/// </summary>
	PatrolRuteData* GetRuteData(const int& num)
	{
		return m_patrolRuteList[num];
	}
};

