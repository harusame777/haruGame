#pragma once
#include "stdafx.h"
#include "Crystal.h"

//�萔��
namespace {
	/// <summary>
	/// �N���X�^���̍ő吔
	/// </summary>
	static const int MAX_CRYSTAL_NUM = 3;
}

class CrystalDataHolder
{
private:
	/// <summary>
	/// �N���X�^���̃f�[�^�z���_�[
	/// </summary>
	Crystal* m_crystalDataHolder[MAX_CRYSTAL_NUM];
public:
	/// <summary>
	/// �f�[�^���z���_�[�ɓ����
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
	/// �f�[�^�z���_�[����N���X�^���̃|�C���^���擾
	/// </summary>
	/// <param name="indexNum"></param>
	/// <returns></returns>
	Crystal* GetCrystalDataHolder(const int indexNum) const 
	{
		return m_crystalDataHolder[indexNum];
	}
};

