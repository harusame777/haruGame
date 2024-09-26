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
	//モデルを設定
	m_modelRender.Init("Assets/modelData/BackGround/laboWall_1-4Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//シャドウマップに描画しないように設定
	m_modelRender.SetShadowChasterFlag(false);

	//座標を設定
	m_modelRender.SetPosition(m_position);
	//回転を設定
	m_modelRender.SetRotation(m_rotation);
	//拡大率を設定
	m_modelRender.SetScale(m_scale);

	//当たり判定を作成
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

//アップデート関数
void BackGroundFloor::Update()
{
	m_modelRender.Update();
}

//ドロー関数
void BackGroundFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}