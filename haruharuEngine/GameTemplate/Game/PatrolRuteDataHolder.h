#pragma once
#include "stdafx.h"
#include "vector"
#include "EnemySMBase.h"

class PatrolRuteDataHolder
{
public:
	/// <summary>
	/// メタAIの巡回ルートのデータ
	/// </summary>
	struct PatrolRuteData
	{
	private:
		/// <summary>
		/// このルートを使用しているウォリアーが存在するか
		/// </summary>
		bool m_isUse = false;
		/// <summary>
		/// 終了地点
		/// </summary>
		Vector3 m_patrolPos;
		/// <summary>
		/// このポイントを使用中のエネミー
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
	/// パトロールルートのリスト
	/// </summary>
	std::vector<PatrolRuteData*> m_patrolRuteList;
	/// <summary>
	/// ルートデータの初期化
	/// </summary>
	/// <param name="data"></param>
	void InitRuteData(PatrolRuteData* data)
	{
		m_patrolRuteList.push_back(data);
	}
	/// <summary>
	/// ルートデータの取得
	/// </summary>
	PatrolRuteData* GetRuteData(const int& num)
	{
		return m_patrolRuteList[num];
	}
};

