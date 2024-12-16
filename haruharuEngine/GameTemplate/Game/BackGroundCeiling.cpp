#include "stdafx.h"
#include "BackGroundCeiling.h"

//�R���X�g���N�^
BackGroundCeiling::BackGroundCeiling()
{

}

//�f�X�g���N�^
BackGroundCeiling::~BackGroundCeiling()
{

}

//�X�^�[�g�֐�
bool BackGroundCeiling::Start()
{
	//���C������ݒ�
	m_mainModel.Init("Assets/modelData/BackGround/laboCeiling_MainModel.tkm", nullptr, 0, enModelUpAxisZ, false);

	//�V���h�E�}�b�v�ɕ`�悵�Ȃ��悤�ɂ���
	m_mainModel.SetShadowChasterFlag(true);

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
void BackGroundCeiling::Update()
{
	//mainModel�̃A�b�v�f�[�g�����s
	m_mainModel.Update();
}

//�`��֐�
void BackGroundCeiling::Render(RenderContext& rc)
{
	//�`��
	m_mainModel.Draw(rc);
}