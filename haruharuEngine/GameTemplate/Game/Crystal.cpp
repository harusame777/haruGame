#include "stdafx.h"
#include "Crystal.h"

//�R���X�g���N�^
Crystal::Crystal()
{

}

//�f�X�g���N�^
Crystal::~Crystal()
{

}

//�X�^�[�g�֐�
bool Crystal::Start()
{

	//�N���X�^��01�����f���ɐݒ�
	m_mainModel.Init("Assets/modelData/objects/crystal/crystal01_Model.tkm", nullptr, 0, enModelUpAxisZ, true);

	//�V���h�E�}�b�v�ɕ`�悷��悤�ɂ���
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
void Crystal::Update()
{
	m_mainModel.Update();
}

//�����_�[�֐�
void Crystal::Render(RenderContext& rc)
{
	m_mainModel.Draw(rc);
}