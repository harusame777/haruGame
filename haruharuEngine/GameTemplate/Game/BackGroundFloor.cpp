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
	//���C������ݒ�
	m_mainModel.Init("Assets/modelData/BackGround/laboFloor_MainModel.tkm", nullptr, 0, enModelUpAxisZ, true);

	//�V���h�E�}�b�v�ɕ`�悵�Ȃ��悤�ɂ���
	m_mainModel.SetShadowChasterFlag(false);

	//���W��ݒ�
	m_mainModel.SetPosition(m_position);
	//��]��ݒ�
	m_mainModel.SetRotation(m_rotation);
	//�g�嗦��ݒ�
	m_mainModel.SetScale(m_scale);
	//�����ݒ���m��
	m_mainModel.Update();

	return true;
}

//�A�b�v�f�[�g�֐�
void BackGroundFloor::Update()
{
	//mainModel�̃A�b�v�f�[�g�����s
	m_mainModel.Update();
}

//�`��֐�
void BackGroundFloor::Render(RenderContext& rc)
{
	//�`��
	m_mainModel.Draw(rc);
}

