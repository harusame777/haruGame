#include "stdafx.h"
#include "ManagerLocker.h"
#include <iostream>
#include <random>

//スタート関数
bool ManagerLocker::Start()
{

	//共通のデータホルダーを初期化
	m_lockerDataHolder = std::make_shared<LockerDataHolder>();

	//ロッカー25つの初期化
	for (int LocNo = 0; LocNo < MAX_LOCKER_NUM; LocNo++)
	{
		Locker* newLocker = NewGO<Locker>(0, "locker");

		m_lockerDataHolder->InitCrystalDataHolder(LocNo, newLocker);

		m_lockerManageDatas[LocNo].SetLockerAddress(newLocker);

		m_lockerManageDatas[LocNo].SetLockerRelocationState(LockerManageState::en_standby);
	}

	//ロッカーの配置位置の初期化
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

//アップデート関数
void ManagerLocker::Update()
{

}

//配置関数
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