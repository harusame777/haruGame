#include "stdafx.h"
#include "ManagerCrystal.h"
#include <random>
#include <algorithm>

//スタート関数
bool ManagerCrystal::Start()
{

	//共通のデータホルダーを初期化
	m_crystalDataHolder = std::make_shared<CrystalDataHolder>();

	//クリスタル3つの初期化
	for (int CryNo = 0; CryNo < MAX_CRYSTAL_NUM; CryNo++)
	{
		CrystalManageData* newCrystalData = new CrystalManageData;

		Crystal* crystal = NewGO<Crystal>(0, "object");

		//共通ホルダーに登録
		m_crystalDataHolder->InitCrystalDataHolder(CryNo, crystal);

		newCrystalData->SetCrystalAddress(crystal);

		newCrystalData->SetCrystalRelocationState(CrystalRelocationState::en_notArrangement_State);

		m_crystalManageDatas[CryNo] = newCrystalData;
	}

	//クリスタルの配置位置の初期化
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

//アップデート関数
void ManagerCrystal::Update()
{
	
	//もし配列の中に採取されているクリスタルがあれば
	if (IsCrystalsAppearance())
	{
		//再配置設定を行う
		InitRelocation();
	}

	//再配置タイマーの処理
	RelocationTimerProcess();

}

void ManagerCrystal::InitRelocation()
{

	//クリスタルの数ぶん回す
	for (int CryNo = 0; CryNo < MAX_CRYSTAL_NUM; CryNo++)
	{

		//現在設定中のクリスタルが設置ステートだったら
		if (m_crystalManageDatas[CryNo]->GetCrystalRelocationState()
			!= CrystalRelocationState::en_notArrangement_State)
		{
			//処理を飛ばす
			continue;
		}

		//配置位置を決定する
		RelocationPosDecision(m_crystalManageDatas[CryNo]);

	}

}

void ManagerCrystal::RelocationPosDecision(CrystalManageData* crystalData)
{
	//登録済みかどうか
	bool isRegistered = true;
	//最終乱数
	int rand = 0;

	int crystalColorRandNum = 0;

	//配置位置決定中にする
	crystalData->SetCrystalRelocationState(
		CrystalRelocationState::en_relocationPosDecision_State);

	do
	{

		//randomライブラリを使用してランダムな値を生成する
		//シード生成
		std::random_device rd;
		std::mt19937 gen(rd());
		//レベルから取得した配置位置の数分の範囲の一様分布の整数を生成
		//要素数を取得
		int arrangementSize = m_crystalArrangementDatas.size();
		//取得した数でランダムな値を生成
		std::uniform_int_distribution<> dist(0, arrangementSize - 1);
		rand = dist(gen);
		//もし取得した乱数の位置の設置位置が使用されていなかったら
		if (m_crystalArrangementDatas[rand]->GetIsCrystalUnderInstallation() == false)
		{

			//ランダムな数の配置位置のデータに設置クリスタルのアドレスを設定
			m_crystalArrangementDatas[rand]->InitAddress(crystalData->GetCrystalAddress());

			//移動回転だけさせておく
			crystalData->GetCrystalAddress()->SetPosition(
				m_crystalArrangementDatas[rand]->GetPosition());

			crystalData->GetCrystalAddress()->SetRotation(
				m_crystalArrangementDatas[rand]->GetRotation());

			//クリスタルカラーを設定
			// 乱数生成器のシード設定
			std::random_device rd;
			std::mt19937 gen(rd());
			// 0 から 100
			std::uniform_int_distribution<int> dist(0, 100);
			// ランダムな数値を生成して出力
			crystalColorRandNum = dist(gen);

			if (crystalColorRandNum <= 5)
				crystalData->GetCrystalAddress()->CrystalSetColor(Crystal::en_crystal_Y);

			if (crystalColorRandNum > 5 && crystalColorRandNum <= 25)
				crystalData->GetCrystalAddress()->CrystalSetColor(Crystal::en_crystal_R);

			if (crystalColorRandNum > 25 && crystalColorRandNum <= 100)
				crystalData->GetCrystalAddress()->CrystalSetColor(Crystal::en_crystal_M);

			//設置タイマーを初期化する
			crystalData->InitCrystalRelocationTimer();

			//配置タイマー処理ステートにする
			crystalData->SetCrystalRelocationState(
				CrystalRelocationState::en_relocationTimerProcessing_State);

			//ループから抜けるようにする
			isRegistered = false;
		}

	} while (isRegistered);

}

void ManagerCrystal::RelocationTimerProcess()
{

	for (int CryNo = 0; CryNo < MAX_CRYSTAL_NUM; CryNo++)
	{

		//再配置中じゃなかったら
		if (m_crystalManageDatas[CryNo]->GetCrystalRelocationState() 
			!= CrystalRelocationState::en_relocationTimerProcessing_State)
		{
			//処理を飛ばす
			continue;
		}

		//時間を減算
		m_crystalManageDatas[CryNo]->SubtractionCrystalRelocationTimer(g_gameTime->GetFrameDeltaTime());

		//時間が0.0f以下なら
		if (m_crystalManageDatas[CryNo]->GetNowCrystalRelocationTimer() <= 0.0f)
		{
			//再配置処理を行う
			m_crystalManageDatas[CryNo]->GetCrystalAddress()->CrystalArrangement();

			//ステートを設置中に
			m_crystalManageDatas[CryNo]->SetCrystalRelocationState(
				CrystalRelocationState::en_arrangement_State);
		}
	}

}

//クリスタルを再配置可能ステートにする関数
void ManagerCrystal::ArrangementDataRefresh(Crystal* crystal)
{

	for (auto& ptr : m_crystalArrangementDatas)
	{

		if (ptr->GetAddress() == crystal)
		{

			//アドレスを初期化
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