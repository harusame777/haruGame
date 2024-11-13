#include "stdafx.h"
#include "DebugEnemyTrackingState.h"
#include "EnemyWarriorTrackingState.h"
#include "WarriorDataHolder.h"
#include "EnemySM_Warrior.h"


//コンストラクタ
DebugEnemyTrackingState::DebugEnemyTrackingState()
{

}

//デストラクタ
DebugEnemyTrackingState::~DebugEnemyTrackingState()
{

}

//スタート関数
bool DebugEnemyTrackingState::Start()
{

	

	//warriorの数は3体
	for (auto& ptr : m_warriorDataHolder->m_warriorDatas)
	{

		EnemyDebugStruct* newList = new EnemyDebugStruct;

		newList->InitColor();

		newList->m_enemySM = ptr;

		m_enemyDebugSpriteList.push_back(newList);

	}

	return true;
}

//アップデート関数
void DebugEnemyTrackingState::Update()
{
	if (m_warriorDataHolder == nullptr)
	{
		return;
	}

	//マーカーの位置を更新する
	MarkerPositionUpdate();
	//描画更新
	SpriteUpdate();
}

void DebugEnemyTrackingState::MarkerPositionUpdate()
{
	//int dataNum = 0;

	////ウォリアーの数ぶん回す
	//for (const auto& ptr: m_warriorDataHolder->m_warriorDatas)
	//{
	//	//ウォリアーの位置を取得
	//	m_stateMarkers[dataNum].m_warriorPosition = ptr->GetEnemyPtr().GetPosition();
	//	//オブジェクトの上の方に画像を表示したいので。
	//	//y座標を少し大きくする。
	//	m_stateMarkers[dataNum].m_warriorPosition.y += 80.0f;
	//	//ワールド座標からスクリーン座標を計算。
	//	//計算結果をm_spritePositionに格納する
	//	g_camera3D->CalcScreenPositionFromWorldPosition(m_stateMarkers[dataNum].m_spritePosition
	//		, m_stateMarkers[dataNum].m_warriorPosition);
	//	//配列を進める
	//	dataNum++;
	//}

	for (auto& ptr : m_enemyDebugSpriteList)
	{
		//ウォリアーの位置を取得
		ptr->m_warriorPosition = ptr->m_enemySM->GetEnemyPtr().GetPosition();
		//オブジェクトの上の方に画像を表示したいので。
		//y座標を少し大きくする。
		ptr->m_warriorPosition.y += 80.0f;
		//ワールド座標からスクリーン座標を計算。
		//計算結果をm_spritePositionに格納する
		g_camera3D->CalcScreenPositionFromWorldPosition(ptr->m_spritePosition, ptr->m_warriorPosition);
	}

}

void DebugEnemyTrackingState::SpriteUpdate()
{
	//int dataNum = 0;

	////ウォリアーの数ぶん回す
	//for (const auto& ptr : m_warriorDataHolder->m_warriorDatas)
	//{
	//	m_stateMarkers[dataNum].m_warriorTrackingStateNum = ptr->GetEnemyPtr().GetTrackingStateNumber();

	//	m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]
	//		->SetPosition(Vector3(m_stateMarkers[dataNum].m_spritePosition.x, m_stateMarkers[dataNum].m_spritePosition.y, 0.0f));

	//	m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]->Update();

	//	dataNum++;
	//}

	for (auto& ptr : m_enemyDebugSpriteList)
	{
		ptr->m_warriorTrackingStateNum = ptr->m_enemySM->GetEnemyPtr().GetTrackingStateNumber();

		ptr->m_colorList[ptr->m_warriorTrackingStateNum]->m_makerColor.SetPosition(Vector3(ptr->m_spritePosition.x , ptr->m_spritePosition.y , 0.0f));

		ptr->m_colorList[ptr->m_warriorTrackingStateNum]->m_makerColor.Update();
	}

}

//ドロー関数
void DebugEnemyTrackingState::Render(RenderContext& rc)
{
	//int dataNum = 0;

	//for (const auto& ptr : m_warriorDataHolder->m_warriorDatas)
	//{
	//	m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]->Draw(rc);

	//	dataNum++;
	//}

	for (auto& ptr : m_enemyDebugSpriteList)
	{
		if (IsInCamera(ptr))
		{
			ptr->m_colorList[ptr->m_warriorTrackingStateNum]->m_makerColor.Draw(rc);
		}
	}
}

const bool DebugEnemyTrackingState::IsInCamera(EnemyDebugStruct* ptr)
{

	Vector3 diff = ptr->m_enemySM->GetEnemyPtr().GetPosition() - g_camera3D->GetPosition();

	//エネミーからプレイヤーに向かうベクトルを正規化
	diff.Normalize();
	//エネミーの正面ベクトルと、敵からプレイヤーに向かうベクトルの
	//内積(cosθ)を求める。
	float cos = g_camera3D->GetForward().Dot(diff);
	if (cos >= 1)
	{
		cos = 1.0f;
	}
	//内積(cosθ)から角度(θ)を求める
	float angle = acosf(cos);
	//角度(θ)が90°(視野角)より小さければ
	if (angle <= (Math::PI / 180.0f) * 90.0f)
	{

		return true;

	}

	return false;
}