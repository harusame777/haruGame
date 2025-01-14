#include "stdafx.h"
#include "Gameover.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemyBase.h"
#include "Player.h"

//定数等
namespace {
	static const float BACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float BACKSIDE_SPRITE_H_SIZE = 900.0f;
}

//スタート関数
bool Gameover::Start()
{
	m_backSideSprite.Init("Assets/modelData/title/back_side_1.DDS",
		BACKSIDE_SPRITE_W_SIZE,
		BACKSIDE_SPRITE_H_SIZE);

	Player* player = FindGO<Player>("player");

	Vector3 playerPos = player->GetPosition();

	EnemyAIMetaWarrior* enemyMetaAI = FindGO<EnemyAIMetaWarrior>("MetaAI");

	std::shared_ptr<WarriorDataHolder> warriorDataHolder;

	warriorDataHolder = enemyMetaAI->GetEnemyDatas();

	Vector3 attackWarriorPos;

	for (auto& ptr : warriorDataHolder->m_warriorDatas)
	{
		bool flag = ptr->GetEnemyPtr().GetAttackFlag();

		if (flag)
		{
			attackWarriorPos = ptr->GetEnemyPtr().GetPosition();
		}
	}

	m_cameraToWarriorDir = attackWarriorPos - g_camera3D->GetPosition();

	float endAngle = atan2(m_cameraToWarriorDir.x, m_cameraToWarriorDir.z);

	m_endRotation.SetRotation(Vector3::AxisY, endAngle);

	m_cameraToTargetDir = g_camera3D->GetTarget() - g_camera3D->GetPosition();

	m_cameraToTargetDir.Normalize();

	float startAngle = atan2(m_cameraToTargetDir.x, m_cameraToTargetDir.z);

	m_startRotation.SetRotation(Vector3::AxisY, startAngle);

	m_gameoverState = GameoverState::en_cameraEasing;

	return true;
}

//アップデート関数
void Gameover::Update()
{
	GameoverStateUpdate();
}

//ステート更新関数
void Gameover::GameoverStateUpdate()
{
	switch (m_gameoverState)
	{
	case Gameover::en_standby:
		break;
	case Gameover::en_cameraEasing:

		//if (CameraEasing())
		//{
		//	m_gameoverState = GameoverState::en_enemyAnimation;
		//}

		break;
	case Gameover::en_enemyAnimation:
		break;
	default:
		break;
	}
}

//カメラのイージング関数
const bool& Gameover::CameraEasing()
{
	//回転まで実装
	m_startRotation.AddRotationDegY(5.0f);

	m_startRotation.Apply(m_cameraToTargetDir);

	Vector3 newCameraPos = m_cameraToTargetDir + g_camera3D->GetPosition();

	g_camera3D->SetTarget(newCameraPos);

	m_cameraToTargetDir = Vector3::AxisZ;

	return false;
}

//レンダー関数
void Gameover::Render(RenderContext& rc)
{

}