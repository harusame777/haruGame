#include "stdafx.h"
#include "BackGroundWalls.h"

//コンストラクタ
BackGroundWalls::BackGroundWalls()
{

}

//デストラクタ
BackGroundWalls::~BackGroundWalls()
{
	delete m_mainModel;
}

//スタート関数
bool BackGroundWalls::Start()
{
	//壁1-4を設定
	m_wall1_4.Init("Assets/modelData/BackGround/laboWall_1-4Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//シャドウマップに描画するようにする
	m_wall1_4.SetShadowChasterFlag(true);

	//壁2-4を設定
	m_wall2_4.Init("Assets/modelData/BackGround/laboWall_2-4Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//シャドウマップに描画するようにする
	m_wall2_4.SetShadowChasterFlag(true);

	//壁4-4を設定
	m_wall4_4.Init("Assets/modelData/BackGround/laboWall_4-4Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//シャドウマップに描画するようにする
	m_wall4_4.SetShadowChasterFlag(true);

	//壁4-6を設定
	m_wall4_6.Init("Assets/modelData/BackGround/laboWall_4-6Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//シャドウマップに描画するようにする
	m_wall4_6.SetShadowChasterFlag(true);

	//座標を設定
	m_mainModel->SetPosition(m_position);
	//回転を設定
	m_mainModel->SetRotation(m_rotation);
	//拡大率を設定
	m_mainModel->SetScale(m_scale);

	return true;
}

//アップデート関数
void BackGroundWalls::Update()
{
	//エラー防止
	if (IsSetWallType())
	{
		return;
	}
	//mainModelのアップデートを実行
	m_mainModel->Update();
}

//ドロー関数
void BackGroundWalls::Draw(RenderContext& rc)
{
	//エラー防止
	if (IsSetWallType())
	{
		//描画
		m_mainModel->Draw(rc);
	}
}

void BackGroundWalls::SetWallType(const WallType& walltype)
{
	//エラー防止
	if (IsSetWallType())
	{
		return;
	}

	//壁の種類を設定する
	m_wallType = walltype;

	//壁の種類からモデルを選ぶ
	switch (m_wallType)
	{
	case BackGroundWalls::en_wallType1_4:
		m_mainModel = &m_wall1_4;
		break;
	case BackGroundWalls::en_wallType2_4:
		m_mainModel = &m_wall2_4;
		break;
	case BackGroundWalls::en_wallType4_4:
		m_mainModel = &m_wall4_4;
		break;
	case BackGroundWalls::en_wallType4_6:
		m_mainModel = &m_wall4_6;
		break;
	}

	//当たり判定を作成
	m_physicsStaticObject.CreateFromModel(m_mainModel->GetModel(), m_mainModel->GetModel().GetWorldMatrix());
}