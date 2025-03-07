#include "stdafx.h"
#include "ManagerLocker.h"
#include "Player.h"
#include "GameCamera.h"
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

		newLocker->SetManegerInstance(*this);

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

			newArrangementData->SetIsLockerUnderInstallation(false);

			m_lockerArrangementDatas.push_back(newArrangementData);

			return true;
		}
		return true;
	});

	//�����ݒ�z��
	InitArrangement();

	m_player = FindGO<Player>("player");

	m_gameCamera = FindGO<GameCamera>("camera");

	return true;
}

void ManagerLocker::SetPlayerInLocker()
{
	m_player->SetPlayerState(Player::en_lockerIn);
}

void ManagerLocker::SetPlayerOutLocker()
{
	m_player->SetPlayerState(Player::en_move);
}

void ManagerLocker::SetCameraTarget(const Vector3& pos)
{

	m_gameCamera->SetCameraTarget(pos);

}

//�A�b�v�f�[�g�֐�
void ManagerLocker::Update()
{

}

//�z�u�֐�
void ManagerLocker::InitArrangement()
{

	for (int LocNo = 0; LocNo < MAX_LOCKER_NUM; LocNo++)
	{
		Locker* arrangementLocker = nullptr;

		int maxArrangementPointNum;

		int arrengementPointListNum;

		bool arrengementConflict = true;

		do {

			for (auto& locAddress : m_lockerManageDatas)
			{

				if (locAddress.GetLockerRelocationState()
					== LockerManageState::en_standby)
				{
					arrangementLocker = locAddress.GetLockerAddress();

					break;
				}

			}

			maxArrangementPointNum = m_lockerArrangementDatas.size();

			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_int_distribution<int> dist(0, maxArrangementPointNum - 1);
			
			arrengementPointListNum = dist(gen);

			if (m_lockerArrangementDatas[arrengementPointListNum]
				->GetIsCrystalUnderInstallation() == false)
			{
				arrengementConflict = false;
			}

		} while (arrengementConflict);

		m_lockerArrangementDatas[arrengementPointListNum]->InitAddress(arrangementLocker);

		//�ʒu��]�X�V
		m_lockerArrangementDatas[arrengementPointListNum]->LockerPosAndRotUpdate();

		//�X�e�[�^�X��ݒu����
		m_lockerArrangementDatas[arrengementPointListNum]->SetIsLockerUnderInstallation(true);

		m_lockerManageDatas[LocNo].SetLockerRelocationState(LockerManageState::en_underplacement);
	}
}

const bool ManagerLocker::IsWholeLockersInUse()
{
	for (auto& locNo : m_lockerManageDatas)
	{
		if (locNo.GetLockerRelocationState()
			!= LockerManageState::en_underplacement)
			continue;

		if (locNo.GetLockerAddress()->IsLockerInUse() == true)
		{
			return true;
		}
	}

	return false;
}