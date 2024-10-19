#include "stdafx.h"
#include "BackGroundFloor.h"

//コンストラクタ
BackGroundFloor::BackGroundFloor()
{

}

//デストラクタ
BackGroundFloor::~BackGroundFloor()
{

}

//スタート関数
bool BackGroundFloor::Start()
{
	//メイン床を設定
	m_mainModel.Init("Assets/modelData/BackGround/laboFloor_MainModel.tkm", nullptr, 0, enModelUpAxisZ, true);

	//シャドウマップに描画しないようにする
	m_mainModel.SetShadowChasterFlag(false);

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
void BackGroundFloor::Update()
{
	//mainModelのアップデートを実行
	m_mainModel.Update();
}

//描画関数
void BackGroundFloor::Render(RenderContext& rc)
{
	//描画
	m_mainModel.Draw(rc);
}

