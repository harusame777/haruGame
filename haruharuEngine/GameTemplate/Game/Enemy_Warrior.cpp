#include "stdafx.h"
#include "Enemy_Warrior.h"
#include "Player.h"

//�R���X�g���N�^
Enemy_Warrior::Enemy_Warrior()
{

}

//�f�X�g���N�^
Enemy_Warrior::~Enemy_Warrior()
{

}

//�X�^�[�g�֐�
bool Enemy_Warrior::Start()
{
	m_modelRender.Init("Assets/modelData/testEnemy/youtai.tkm");
	m_modelRender.SetScale(1.0f, 1.0f, 1.0f);
	m_modelRender.SetPosition({500.0f,0.0f,0.0f});

	//�V���h�E�}�b�v�ɕ`�悷��悤�ɂ���
	m_modelRender.SetShadowChasterFlag(false);

	m_player = FindGO<Player>("player");

	m_nvmMesh.Init("Assets/nvm/test.tkn");

	return true;
}

//�A�b�v�f�[�g�֐�
void Enemy_Warrior::Update()
{
	bool isEnd;

	Vector3 playerPos = m_player->GetPosition();

	m_pathFiding.Execute(
		m_path,
		m_nvmMesh,
		m_position,
		playerPos,
		PhysicsWorld::GetInstance(),
		50.0f,
		200.0f
	);

	//�p�X����ړ�����
	m_position = m_path.Move(
		m_position,
		10.0f,
		isEnd
	);

	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
}

//�h���[�֐�
void Enemy_Warrior::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}