#include "stdafx.h"
#include "ManagerLocker.h"
#include <iostream>
#include <random>

//�X�^�[�g�֐�
bool ManagerLocker::Start()
{

	//���ʂ̃f�[�^�z���_�[��������
	m_lockerDataHolder = std::make_shared<LockerDataHolder>();

	//���b�J�[25�̏�����
	for (int LocNo = 0; LocNo < MAX_LOCKER_NUM; LocNo++)
	{
		Locker* newLocker = NewGO<Locker>(0, "locker");

		m_lockerDataHolder->InitCrystalDataHolder(LocNo, newLocker);

		m_lockerManageDatas[LocNo].SetLockerAddress(newLocker);

		m_lockerManageDatas[LocNo].SetLockerRelocationState(LockerManageState::en_standby);
	}

	//���b�J�[�̔z�u�ʒu�̏�����
	m_lockerArrangementLevelRender.Init("Assets/mapLevel/testLevel8.tkl", [&](LevelObjectData_Render& objData)
	{
		if (objData.EqualObjectName(L"locker") == true)
		{
			LockerArrangementData* newArrangementData = new LockerArrangementData;

			newArrangementData->SetPosition(objData.m_position);

			newArrangementData->SetRotation(objData.m_rotation);

			newArrangementData->SetIsCrystalUnderInstallation(false);

			m_lockerArrangementDatas.push_back(newArrangementData);

			return true;
		}
		return true;
	});

	InitArrangement();

	return true;
}

//�A�b�v�f�[�g�֐�
void ManagerLocker::Update()
{

}

//�z�u�֐�
void ManagerLocker::InitArrangement()
{
	Locker* arrangementLocker = nullptr;

	int maxArrangementPointNum;

	int arrengementPointListNum;

	bool arrengementConflict = true;

	do {
	
		for (auto& locAddress : m_lockerManageDatas)
		{

			if (locAddress.GetCrystalRelocationState()
				== LockerManageState::en_standby)
			{
				arrangementLocker = locAddress.GetCrystalAddress();

				break;
			}

		}

		maxArrangementPointNum = m_lockerArrangementDatas.size();

		std::random_device rd;  
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dist(0, maxArrangementPointNum);

		arrengementPointListNum = dist(gen);

		if (m_lockerArrangementDatas[arrengementPointListNum]
			->GetIsCrystalUnderInstallation() == false)
		{
			arrengementConflict = false;
		}

	} while (arrengementConflict);
}