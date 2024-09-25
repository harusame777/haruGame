#include "stdafx.h"
#include "BackGroundWalls.h"

//�R���X�g���N�^
BackGroundWalls::BackGroundWalls()
{

}

//�f�X�g���N�^
BackGroundWalls::~BackGroundWalls()
{
	delete m_mainModel;
}

//�X�^�[�g�֐�
bool BackGroundWalls::Start()
{
	//��1-4��ݒ�
	m_wall1_4.Init("Assets/modelData/BackGround/laboWall_1-4Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//�V���h�E�}�b�v�ɕ`�悷��悤�ɂ���
	m_wall1_4.SetShadowChasterFlag(true);

	//��2-4��ݒ�
	m_wall2_4.Init("Assets/modelData/BackGround/laboWall_2-4Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//�V���h�E�}�b�v�ɕ`�悷��悤�ɂ���
	m_wall2_4.SetShadowChasterFlag(true);

	//��4-4��ݒ�
	m_wall4_4.Init("Assets/modelData/BackGround/laboWall_4-4Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//�V���h�E�}�b�v�ɕ`�悷��悤�ɂ���
	m_wall4_4.SetShadowChasterFlag(true);

	//��4-6��ݒ�
	m_wall4_6.Init("Assets/modelData/BackGround/laboWall_4-6Model.tkm", nullptr, 0, enModelUpAxisZ, true);
	//�V���h�E�}�b�v�ɕ`�悷��悤�ɂ���
	m_wall4_6.SetShadowChasterFlag(true);

	//���W��ݒ�
	m_mainModel->SetPosition(m_position);
	//��]��ݒ�
	m_mainModel->SetRotation(m_rotation);
	//�g�嗦��ݒ�
	m_mainModel->SetScale(m_scale);

	return true;
}

//�A�b�v�f�[�g�֐�
void BackGroundWalls::Update()
{
	//�G���[�h�~
	if (IsSetWallType())
	{
		return;
	}
	//mainModel�̃A�b�v�f�[�g�����s
	m_mainModel->Update();
}

//�h���[�֐�
void BackGroundWalls::Draw(RenderContext& rc)
{
	//�G���[�h�~
	if (IsSetWallType())
	{
		//�`��
		m_mainModel->Draw(rc);
	}
}

void BackGroundWalls::SetWallType(const WallType& walltype)
{
	//�G���[�h�~
	if (IsSetWallType())
	{
		return;
	}

	//�ǂ̎�ނ�ݒ肷��
	m_wallType = walltype;

	//�ǂ̎�ނ��烂�f����I��
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

	//�����蔻����쐬
	m_physicsStaticObject.CreateFromModel(m_mainModel->GetModel(), m_mainModel->GetModel().GetWorldMatrix());
}