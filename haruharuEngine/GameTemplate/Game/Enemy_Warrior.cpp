#include "stdafx.h"
#include "Enemy_Warrior.h"
#include "Player.h"
#include "EnemyAIMoveAstar.h"
#include "EnemySM_Warrior.h"
#include "EnemyAIMetaWarrior.h"
#include "GameSound.h"

namespace {

	static const float MAX_RANGE_CALC_NUM = 500.0f;
	static const float MIN_RANGE_NUM = 0.0f;

	static const float MAX_VOLUME_NUM = 1.0f;
	static const float MIN_VOLUME_NUM = 0.0f;
}

//�R���X�g���N�^
Enemy_Warrior::Enemy_Warrior()
{

}

//�f�X�g���N�^
Enemy_Warrior::~Enemy_Warrior()
{
	delete m_enemyWarriorSM;

	DeleteGO(m_collisionObject);
}


//�X�^�[�g�֐�
bool Enemy_Warrior::Start()
{
	m_animationClip[EnAnimationClip::en_idle].Load("Assets/modelData/enemyWarrior/enemy_Warrior_idle.tka");
	m_animationClip[EnAnimationClip::en_idle].SetLoopFlag(true);

	m_animationClip[EnAnimationClip::en_patrol].Load("Assets/modelData/enemyWarrior/enemy_Warrior_run.tka");
	m_animationClip[EnAnimationClip::en_patrol].SetLoopFlag(true);

	m_animationClip[EnAnimationClip::en_attack].Load("Assets/modelData/enemyWarrior/enemy_Warrior_attack.tka");
	m_animationClip[EnAnimationClip::en_attack].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/enemyWarrior/enemy_Warrior.tkm", m_animationClip,en_animationNum
		,enModelUpAxisZ,ModelRender::en_shadowShader);
	m_modelRender.SetScale(1.0f, 1.0f, 1.0f);
	m_modelRender.SetPosition({500.0f,0.0f,0.0f});

	//�A�j���[�V�����C�x���g�p�֐��ݒ�
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	m_gameSound = FindGO<GameSound>("gameSound");

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

	EnemyAIMetaWarrior* enemyMetaAI = FindGO<EnemyAIMetaWarrior>("MetaAI");

	std::shared_ptr<WarriorDataHolder> warriorDataHolder;

	warriorDataHolder = enemyMetaAI->GetEnemyDatas();

	int enemyNum = warriorDataHolder->m_warriorDatas.size();

	char colName[20] = "enemy_col:";

	char enemyNumChar[20] = "";

	std::sprintf(enemyNumChar, "%d", enemyNum);  // �����𕶎���ɕϊ�
	std::strcat(colName, enemyNumChar);        // �z��ɒǉ�

	SetCollisionName(colName);

	//����̃R���W�������쐬����B
	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 30.0f * m_scale.z);
	m_collisionObject->SetName(GetCollisionName());
	m_collisionObject->SetPosition(m_position);
	////�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
	m_collisionObject->SetIsEnableAutoDelete(false);
	
	return true;
}

void Enemy_Warrior::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	if (wcscmp(eventName, L"enemyRunSound") == 0)
	{
		Vector3 playerPos = m_player->GetPosition();
		Vector3 enemyPos = GetPosition();
		Vector3 playerToEnemydiff = playerPos - enemyPos;

		float diss = playerToEnemydiff.Length();

		float t;

		if (diss > 1000.0f)
		{
			t = 0.0f;
		}
		else
		{
			t = 1.0f - (diss / 1000.0f);
		}

		// ���`��ԁi�����ł� t �����̂܂܍ŏI�l�j
		float finalValue = t;

		m_gameSound->SoundListInit(
			GameSound::en_enemyWarriorWalkSound,
			GameSound::en_priority_high,
			finalValue
		);
	}
	else if (wcscmp(eventName, L"AttackImpact") == 0)
	{

		m_gameSound->LocalSoundOrder(GameSound::en_killSound, false, 1.0f);

		SetAttackImpact(true);
	}
}

//�A�b�v�f�[�g�֐�
void Enemy_Warrior::Update()
{
	AIListUpdate();

	m_modelRender.PlayAnimation(m_animationClipState);

	m_modelRender.SetRotation(m_rotation);

	m_modelRender.SetPosition(m_position);

	m_collisionObject->SetPosition(m_position);

	m_CController.SetPosition(m_position);

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
	//�X�e�[�g�}�V��
	m_enemyWarriorSM = new EnemySM_Warrior;

	m_enemyWarriorSM->BinedEnemy(this);

	m_enemyWarriorSM->EnemyAIStart();

}

void Enemy_Warrior::AIListUpdate()
{
	m_enemyWarriorSM->EnemyAIUpdate();
}