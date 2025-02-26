#include "stdafx.h"
#include "ManagerCrystal.h"
#include <random>
#include <algorithm>

//�X�^�[�g�֐�
bool ManagerCrystal::Start()
{

	//���ʂ̃f�[�^�z���_�[��������
	m_crystalDataHolder = std::make_shared<CrystalDataHolder>();

	//�N���X�^��3�̏�����
	for (int CryNo = 0; CryNo < MAX_CRYSTAL_NUM; CryNo++)
	{
		CrystalManageData* newCrystalData = new CrystalManageData;

		Crystal* crystal = NewGO<Crystal>(0, "object");

		//���ʃz���_�[�ɓo�^
		m_crystalDataHolder->InitCrystalDataHolder(CryNo, crystal);

		newCrystalData->SetCrystalAddress(crystal);

		newCrystalData->SetCrystalRelocationState(CrystalRelocationState::en_notArrangement_State);

		m_crystalManageDatas[CryNo] = newCrystalData;
	}

	//�N���X�^���̔z�u�ʒu�̏�����
	m_crystalArrangementLevelRender.Init("Assets/mapLevel/testLevel5.tkl", [&](LevelObjectData_Render& objData)
	{
		if (objData.EqualObjectName(L"crystal01_Model") == true)
		{
			CrystalArrangementData* newPositionData = new CrystalArrangementData;

			newPositionData->SetPosition(objData.m_position);

			newPositionData->SetRotation(objData.m_rotation);

			newPositionData->SetIsCrystalUnderInstallation(false);

			m_crystalArrangementDatas.push_back(newPositionData);

			return true;
		}
		return true;
	});

	return true;
}

//�A�b�v�f�[�g�֐�
void ManagerCrystal::Update()
{
	
	//�����z��̒��ɍ̎悳��Ă���N���X�^���������
	if (IsCrystalsAppearance())
	{
		//�Ĕz�u�ݒ���s��
		InitRelocation();
	}

	//�Ĕz�u�^�C�}�[�̏���
	RelocationTimerProcess();

}

void ManagerCrystal::InitRelocation()
{

	//�N���X�^���̐��Ԃ��
	for (int CryNo = 0; CryNo < MAX_CRYSTAL_NUM; CryNo++)
	{

		//���ݐݒ蒆�̃N���X�^�����ݒu�X�e�[�g��������
		if (m_crystalManageDatas[CryNo]->GetCrystalRelocationState()
			!= CrystalRelocationState::en_notArrangement_State)
		{
			//�������΂�
			continue;
		}

		//�z�u�ʒu�����肷��
		RelocationPosDecision(m_crystalManageDatas[CryNo]);

	}

}

void ManagerCrystal::RelocationPosDecision(CrystalManageData* crystalData)
{
	//�o�^�ς݂��ǂ���
	bool isRegistered = true;
	//�ŏI����
	int rand = 0;

	int crystalColorRandNum = 0;

	//�z�u�ʒu���蒆�ɂ���
	crystalData->SetCrystalRelocationState(
		CrystalRelocationState::en_relocationPosDecision_State);

	do
	{

		//random���C�u�������g�p���ă����_���Ȓl�𐶐�����
		//�V�[�h����
		std::random_device rd;
		std::mt19937 gen(rd());
		//���x������擾�����z�u�ʒu�̐����͈̔͂̈�l���z�̐����𐶐�
		//�v�f�����擾
		int arrangementSize = m_crystalArrangementDatas.size();
		//�擾�������Ń����_���Ȓl�𐶐�
		std::uniform_int_distribution<> dist(0, arrangementSize - 1);
		rand = dist(gen);
		//�����擾���������̈ʒu�̐ݒu�ʒu���g�p����Ă��Ȃ�������
		if (m_crystalArrangementDatas[rand]->GetIsCrystalUnderInstallation() == false)
		{

			//�����_���Ȑ��̔z�u�ʒu�̃f�[�^�ɐݒu�N���X�^���̃A�h���X��ݒ�
			m_crystalArrangementDatas[rand]->InitAddress(crystalData->GetCrystalAddress());

			//�ړ���]���������Ă���
			crystalData->GetCrystalAddress()->SetPosition(
				m_crystalArrangementDatas[rand]->GetPosition());

			crystalData->GetCrystalAddress()->SetRotation(
				m_crystalArrangementDatas[rand]->GetRotation());

			//�N���X�^���J���[��ݒ�
			// ����������̃V�[�h�ݒ�
			std::random_device rd;
			std::mt19937 gen(rd());
			// 0 ���� 100
			std::uniform_int_distribution<int> dist(0, 100);
			// �����_���Ȑ��l�𐶐����ďo��
			crystalColorRandNum = dist(gen);

			if (crystalColorRandNum <= 5)
				crystalData->GetCrystalAddress()->CrystalSetColor(Crystal::en_crystal_Y);

			if (crystalColorRandNum > 5 && crystalColorRandNum <= 25)
				crystalData->GetCrystalAddress()->CrystalSetColor(Crystal::en_crystal_R);

			if (crystalColorRandNum > 25 && crystalColorRandNum <= 100)
				crystalData->GetCrystalAddress()->CrystalSetColor(Crystal::en_crystal_M);

			//�ݒu�^�C�}�[������������
			crystalData->InitCrystalRelocationTimer();

			//�z�u�^�C�}�[�����X�e�[�g�ɂ���
			crystalData->SetCrystalRelocationState(
				CrystalRelocationState::en_relocationTimerProcessing_State);

			//���[�v���甲����悤�ɂ���
			isRegistered = false;
		}

	} while (isRegistered);

}

void ManagerCrystal::RelocationTimerProcess()
{

	for (int CryNo = 0; CryNo < MAX_CRYSTAL_NUM; CryNo++)
	{

		//�Ĕz�u������Ȃ�������
		if (m_crystalManageDatas[CryNo]->GetCrystalRelocationState() 
			!= CrystalRelocationState::en_relocationTimerProcessing_State)
		{
			//�������΂�
			continue;
		}

		//���Ԃ����Z
		m_crystalManageDatas[CryNo]->SubtractionCrystalRelocationTimer(g_gameTime->GetFrameDeltaTime());

		//���Ԃ�0.0f�ȉ��Ȃ�
		if (m_crystalManageDatas[CryNo]->GetNowCrystalRelocationTimer() <= 0.0f)
		{
			//�Ĕz�u�������s��
			m_crystalManageDatas[CryNo]->GetCrystalAddress()->CrystalArrangement();

			//�X�e�[�g��ݒu����
			m_crystalManageDatas[CryNo]->SetCrystalRelocationState(
				CrystalRelocationState::en_arrangement_State);
		}
	}

}

//�N���X�^�����Ĕz�u�\�X�e�[�g�ɂ���֐�
void ManagerCrystal::ArrangementDataRefresh(Crystal* crystal)
{

	for (auto& ptr : m_crystalArrangementDatas)
	{

		if (ptr->GetAddress() == crystal)
		{

			//�A�h���X��������
			ptr->InitAddress(nullptr);

		}

	}
	
	for (int CryNo = 0; CryNo < MAX_CRYSTAL_NUM; CryNo++)
	{

		if (m_crystalManageDatas[CryNo]->GetCrystalAddress()
			== crystal)
		{

			m_crystalManageDatas[CryNo]->SetCrystalRelocationState(
				CrystalRelocationState::en_notArrangement_State);

		}

	}

}