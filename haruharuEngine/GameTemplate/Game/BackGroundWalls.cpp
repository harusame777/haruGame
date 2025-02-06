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

	switch (m_wallType)
	{
	case BackGroundWalls::en_wallType1_4:
		//��1-4��ݒ�
		m_mainModel.Init("Assets/modelData/BackGround/laboWall_1-4Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallType2_4:
		//��2-4��ݒ�
		m_mainModel.Init("Assets/modelData/BackGround/laboWall_2-4Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallType4_4:
		//��4-4��ݒ�
		m_mainModel.Init("Assets/modelData/BackGround/laboWall_4-4Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallType4_6:
		//��4-6��ݒ�
		m_mainModel.Init("Assets/modelData/BackGround/laboWall_4-6Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallTypeDoorWay4_4:
		//�ǃh�A�t��4_4��ݒ�
		m_mainModel.Init("Assets/modelData/BackGround/laboDoorWay_4-4Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_shadowShader);
		break;
	case BackGroundWalls::en_wallOnes:
		//�ǈ�̉����f��
		m_mainModel.Init("Assets/modelData/BackGround/laboWal_lOnesModel.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_usuallyShader);
		break;
	}

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

	//�����蔻����쐬
	m_physicsStaticObject.CreateFromModel(m_mainModel.GetModel(), m_mainModel.GetModel().GetWorldMatrix());

	////�����蔻�����������B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//������ݒ�
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);

	return true;
}

//�A�b�v�f�[�g�֐�
void BackGroundWalls::Update()
{
	//�G���[�h�~
	if (IsSetWallType())
	{
		//mainModel�̃A�b�v�f�[�g�����s
		m_mainModel.Update();
	}
}

//�h���[�֐�
void BackGroundWalls::Render(RenderContext& rc)
{
	//�G���[�h�~
	if (IsSetWallType())
	{
		//�`��
		m_mainModel.Draw(rc);
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
}