#pragma once
#include "stdafx.h"
#include "Locker.h"

//定数等
namespace {
	/// <summary>
	/// クリスタルの最大数
	/// </summary>
	static const int MAX_LOCKER_NUM = 25;
}

class LockerDataHolder
{
private:
	/// <summary>
	/// ロッカーのデータホルダー
	/// </summary>
	Locker* m_lockerDataHolder[MAX_LOCKER_NUM];
public:
	/// <summary>
	/// データをホルダーに入れる
	/// </summary>
	/// <param name="indexNum"></param>
	/// <param name="initData"></param>
	void InitCrystalDataHolder(const int indexNum, Locker* initData)
	{
		if (MAX_LOCKER_NUM < indexNum)
		{
			return;
		}

		m_lockerDataHolder[indexNum] = initData;
	}
	/// <summary>
	/// データホルダーからロッカーのポインタを取得
	/// </summary>
	/// <param name="indexNum"></param>
	/// <returns></returns>
	Locker* GetLockerDataHolder(const int indexNum) const
	{
		return m_lockerDataHolder[indexNum];
	}
	Locker* GetLockerDataHolder(Locker& lockerAddress) const
	{
		for (auto& address : m_lockerDataHolder)
		{
			if (address == &lockerAddress)
			{
				return address;
			}
		}

		return nullptr;
	}
};

