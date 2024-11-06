#include "stdafx.h"
#include "Enemy_Warrior.h"
#include "Player.h"
#include "EnemyAIMoveAstar.h"
#include "EnemySM_Warrior.h"

//�����L���ɂ���ƃf�o�b�O���[�h�ɂȂ�
//#define DEBUG_MODE

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

	//�L�����N�^�[�R���g���[���[��������
	m_CController.Init(10.0f, 20.0f, m_position);

	//�ʒu�̏����ݒ�
	m_CController.SetPosition(m_position);

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//����̃R���W�������쐬����B
	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 30.0f * m_scale.z);
	m_collisionObject->SetName("enemy_col");
	m_collisionObject->SetPosition(m_position);
	////�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
	m_collisionObject->SetIsEnableAutoDelete(false);
	
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

	m_collisionObject->SetPosition(m_position);

	m_CController.SetPosition(m_position);

#ifdef DEBUG_MODE
	DebugStateDisplay(GetStateNumber());
#endif

	m_modelRender.Update();
}

//�h���[�֐�
void Enemy_Warrior::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

#ifdef DEBUG_MODE
	m_debugStateDisplayRender.Draw(rc);
#endif
}

//AIList�̏�����
void Enemy_Warrior::InitAIList()
{
	//�X�e�[�g�}�V��
	m_enemyWarriorSM = new EnemySM_Warrior;

	m_enemyWarriorSM->BinedEnemy(this);

	m_enemyWarriorSM->EnemyAIStart();

}

void Enemy_Warrior::AIListUpdate()
{
	m_enemyWarriorSM->EnemyAIUpdate();
}