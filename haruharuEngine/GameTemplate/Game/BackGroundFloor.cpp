#include "stdafx.h"
#include "BackGroundFloor.h"

//�R���X�g���N�^
BackGroundFloor::BackGroundFloor()
{

}

//�f�X�g���N�^
BackGroundFloor::~BackGroundFloor()
{

}

//�X�^�[�g�֐�
bool BackGroundFloor::Start()
{
	//���f����ݒ�
	m_modelRender.Init("Assets/modelData/BackGround/laboWall_1-4Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//�V���h�E�}�b�v�ɕ`�悵�Ȃ��悤�ɐݒ�
	m_modelRender.SetShadowChasterFlag(false);

	//���W��ݒ�
	m_modelRender.SetPosition(m_position);
	//��]��ݒ�
	m_modelRender.SetRotation(m_rotation);
	//�g�嗦��ݒ�
	m_modelRender.SetScale(m_scale);

	//�����蔻����쐬
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

//�A�b�v�f�[�g�֐�
void BackGroundFloor::Update()
{
	m_modelRender.Update();
}

//�h���[�֐�
void BackGroundFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}