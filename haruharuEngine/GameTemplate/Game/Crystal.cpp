#include "stdafx.h"
#include "Crystal.h"

//コンストラクタ
Crystal::Crystal()
{

}

//デストラクタ
Crystal::~Crystal()
{

}

//スタート関数
bool Crystal::Start()
{

	//クリスタル01をモデルに設定
	m_mainModel.Init("Assets/modelData/objects/crystal/crystal01_Model.tkm", nullptr, 0, enModelUpAxisZ, true);

	//シャドウマップに描画するようにする
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
void Crystal::Update()
{
	m_mainModel.Update();
}

//レンダー関数
void Crystal::Render(RenderContext& rc)
{
	m_mainModel.Draw(rc);
}