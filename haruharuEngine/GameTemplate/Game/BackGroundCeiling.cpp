#include "stdafx.h"
#include "BackGroundCeiling.h"

//コンストラクタ
BackGroundCeiling::BackGroundCeiling()
{

}

//デストラクタ
BackGroundCeiling::~BackGroundCeiling()
{

}

//スタート関数
bool BackGroundCeiling::Start()
{
	//メイン床を設定
	m_mainModel.Init("Assets/modelData/BackGround/laboCeiling_MainModel.tkm", nullptr, 0, enModelUpAxisZ, false);

	//シャドウマップに描画しないようにする
	m_mainModel.SetShadowChasterFlag(true);

	//座標を設定
	m_mainModel.SetPosition(m_position);
	//回転を設定
	m_mainModel.SetRotation(m_rotation);
	//拡大率を設定
	m_mainModel.SetScale(m_scale);
	//初期設定を確定
	m_mainModel.Update();

	return true;
}

//アップデート関数
void BackGroundCeiling::Update()
{
	//mainModelのアップデートを実行
	m_mainModel.Update();
}

//描画関数
void BackGroundCeiling::Render(RenderContext& rc)
{
	//描画
	m_mainModel.Draw(rc);
}