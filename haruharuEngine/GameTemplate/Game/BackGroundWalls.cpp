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
	return true;
}

//アップデート関数
void BackGroundWalls::Update()
{

}

//ドロー関数
void BackGroundWalls::Draw(RenderContext& rc)
{
	m_mainModel->Draw(rc);
}