#include "stdafx.h"
#include "BackGroundWalls.h"

//コンストラクタ
BackGroundWalls::BackGroundWalls()
{

}

//デストラクタ
BackGroundWalls::~BackGroundWalls()
{

}

//スタート関数
bool BackGroundWalls::Start()
{

	switch (m_wallType)
	{
	case BackGroundWalls::en_wallType1_4:
		//壁1-4を設定
		m_mainModel.Init("Assets/modelData/BackGround/laboWall_1-4Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallType2_4:
		//壁2-4を設定
		m_mainModel.Init("Assets/modelData/BackGround/laboWall_2-4Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallType4_4:
		//壁4-4を設定
		m_mainModel.Init("Assets/modelData/BackGround/laboWall_4-4Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallType4_6:
		//壁4-6を設定
		m_mainModel.Init("Assets/modelData/BackGround/laboWall_4-6Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallTypeDoorWay4_4:
		//壁ドア付き4_4を設定
		m_mainModel.Init("Assets/modelData/BackGround/laboDoorWay_4-4Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallOnes:
		//壁一体化モデル
		m_mainModel.Init("Assets/modelData/BackGround/laboWal_lOnesModel.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_usuallyShader);
		break;
	}

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

	//当たり判定を作成
	m_physicsStaticObject.CreateFromModel(m_mainModel.GetModel(), m_mainModel.GetModel().GetWorldMatrix());

	////当たり判定を可視化する。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//属性を設定
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);

	return true;
}

//アップデート関数
void BackGroundWalls::Update()
{
	//エラー防止
	if (IsSetWallType())
	{
		//mainModelのアップデートを実行
		m_mainModel.Update();
	}
}

//ドロー関数
void BackGroundWalls::Render(RenderContext& rc)
{
	//エラー防止
	if (IsSetWallType())
	{
		//描画
		m_mainModel.Draw(rc);
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
}