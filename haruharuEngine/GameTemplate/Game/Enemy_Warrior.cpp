#include "stdafx.h"
#include "Enemy_Warrior.h"
#include "Player.h"
#include "EnemyAIMoveAstar.h"
#include "EnemySM_Warrior.h"

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

	InitAIList();
	
	return true;
}

//�A�b�v�f�[�g�֐�
void Enemy_Warrior::Update()
{
	Vector3 plaPos = m_player->GetPosition();

	SetMoveTargetPosition(plaPos);

	AIListUpdate();

	m_modelRender.SetRotation(m_rotation);

	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
}

//�h���[�֐�
void Enemy_Warrior::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

//AIList�̏�����
void Enemy_Warrior::InitAIList()
{
	//AI��List�����̃G�l�~�[�ɕK�v�ȕ��ŏ���������
	//�X�e�[�g�}�V��
	m_EnemyAIList.push_back(new EnemySM_Warrior);
	//�o�H�T��
	m_EnemyAIList.push_back(new EnemyAIMoveAstar);

	//���̃G�l�~�[�̃C���X�^���X��AIList�̃v���O�����ɓn��
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->BinedEnemy(this);
	}

	//AIList�̒��̃v���O�����̃X�^�[�g�֐����N������
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->Start();
	}
}

void Enemy_Warrior::AIListUpdate()
{
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->Update();
	}
}