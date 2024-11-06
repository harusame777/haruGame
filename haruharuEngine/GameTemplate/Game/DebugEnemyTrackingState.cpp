#include "stdafx.h"
#include "DebugEnemyTrackingState.h"
#include "EnemyWarriorTrackingState.h"
#include "WarriorDataHolder.h"

//定数等
namespace {
	/// <summary>
	/// 文字サイズ
	/// </summary>
	static const float SPRITE_W_SIZE = 150.0f;
	static const float SPRITE_H_SIZE = 150.0f;
}

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
	//灰色マーカーを設定
	m_grayMarker.Init("Assets/modelData/debug/testWarriorTrackingStateGray.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	//赤色マーカーを設定
	m_redMarker.Init("Assets/modelData/debug/testWarriorTrackingStateRed.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	//黄色マーカーを設定
	m_yellowMarker.Init("Assets/modelData/debug/testWarriorTrackingStateYellow.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	//緑色マーカーを設定
	m_greenMarker.Init("Assets/modelData/debug/testWarriorTrackingStateGreen.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);


	//warriorの数は3体
	for (int i = 0; i < 3; i++)
	{
		m_stateMarkers[i].m_makerColor[WarriorTrackingState::en_nonTracking] = &m_grayMarker;
		m_stateMarkers[i].m_makerColor[WarriorTrackingState::en_chaseFromBehind] = &m_redMarker;
		m_stateMarkers[i].m_makerColor[WarriorTrackingState::en_wrapAround] = &m_yellowMarker;
		m_stateMarkers[i].m_makerColor[WarriorTrackingState::en_usually] = &m_greenMarker;
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
	int dataNum = 0;

	//ウォリアーの数ぶん回す
	for (const auto& ptr: m_warriorDataHolder->m_warriorDatas)
	{
		//ウォリアーの位置を取得
		m_stateMarkers[dataNum].m_warriorPosition = ptr->GetEnemyPtr().GetPosition();
		//オブジェクトの上の方に画像を表示したいので。
		//y座標を少し大きくする。
		m_stateMarkers[dataNum].m_warriorPosition.y += 80.0f;
		//ワールド座標からスクリーン座標を計算。
		//計算結果をm_spritePositionに格納する
		g_camera3D->CalcScreenPositionFromWorldPosition(m_stateMarkers[dataNum].m_spritePosition
			, m_stateMarkers[dataNum].m_warriorPosition);
		//配列を進める
		dataNum++;
	}

}

void DebugEnemyTrackingState::SpriteUpdate()
{
	int dataNum = 0;

	//ウォリアーの数ぶん回す
	for (const auto& ptr : m_warriorDataHolder->m_warriorDatas)
	{
		m_stateMarkers[dataNum].m_warriorTrackingStateNum = ptr->GetEnemyPtr().GetTrackingStateNumber();

		m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]
			->SetPosition(Vector3(m_stateMarkers[dataNum].m_spritePosition.x, m_stateMarkers[dataNum].m_spritePosition.y, 0.0f));

		m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]->Update();

		dataNum++;
	}

}

//ドロー関数
void DebugEnemyTrackingState::Render(RenderContext& rc)
{
	int dataNum = 0;

	for (const auto& ptr : m_warriorDataHolder->m_warriorDatas)
	{
		m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]->Draw(rc);

		dataNum++;
	}
}