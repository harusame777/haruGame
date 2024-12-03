#pragma once
#include "stdafx.h"
#include "Crystal.h"

//定数等
namespace {
	/// <summary>
	/// クリスタルの最大数
	/// </summary>
	static const int MAX_CRYSTAL_NUM = 3;
}

class CrystalDataHolder
{
private:
	/// <summary>
	/// クリスタルのデータホルダー
	/// </summary>
	Crystal* m_crystalDataHolder[MAX_CRYSTAL_NUM];
public:
	/// <summary>
	/// データをホルダーに入れる
	/// </summary>
	/// <param name="indexNum"></param>
	/// <param name="initData"></param>
	void InitCrystalDataHolder(const int indexNum, Crystal* initData)
	{
		if (MAX_CRYSTAL_NUM < indexNum)
		{
			return;
		}

		m_crystalDataHolder[indexNum] = initData;
	}
	/// <summary>
	/// データホルダーからクリスタルのポインタを取得
	/// </summary>
	/// <param name="indexNum"></param>
	/// <returns></returns>
	Crystal* GetCrystalDataHolder(const int indexNum) const 
	{
		return m_crystalDataHolder[indexNum];
	}
};

