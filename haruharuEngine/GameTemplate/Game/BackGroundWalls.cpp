#include "stdafx.h"
#include "BackGroundWalls.h"

//�R���X�g���N�^
BackGroundWalls::BackGroundWalls()
{

}

//�f�X�g���N�^
BackGroundWalls::~BackGroundWalls()
{

}

//�X�^�[�g�֐�
bool BackGroundWalls::Start()
{
	return true;
}

//�A�b�v�f�[�g�֐�
void BackGroundWalls::Update()
{

}

//�h���[�֐�
void BackGroundWalls::Draw(RenderContext& rc)
{
	m_mainModel->Draw(rc);
}