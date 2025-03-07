#pragma once
#include "stdafx.h"
#include "Locker.h"

//�萔��
namespace {
	/// <summary>
	/// �N���X�^���̍ő吔
	/// </summary>
	static const int MAX_LOCKER_NUM = 25;
}

class LockerDataHolder
{
private:
	/// <summary>
	/// ���b�J�[�̃f�[�^�z���_�[
	/// </summary>
	Locker* m_lockerDataHolder[MAX_LOCKER_NUM];
public:
	/// <summary>
	/// �f�[�^���z���_�[�ɓ����
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
	/// �f�[�^�z���_�[���烍�b�J�[�̃|�C���^���擾
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

