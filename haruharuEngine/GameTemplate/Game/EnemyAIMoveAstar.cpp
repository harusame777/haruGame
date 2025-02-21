#include "stdafx.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyBase.h"
#include "WarriorDataHolder.h"
#include "Player.h"
#include <cmath>
#include "EnemyAIConBase.h"
#include "EnemyAIConWaitTime.h"
#include "EnemyAIConWallSearch.h"

//�����L���ɂ���ƃf�o�b�O���[�h�ɂȂ�
//#define DEBUG_MODE

//�萔��
namespace {
	static const float ENEMY_SPEED = 150.0f;
}

//�X�^�[�g�֐�
void EnemyAIMoveAstar::EnemyAIStart()
{
	m_nvmMesh.Init("Assets/nvm/testnvm10.tkn");

	m_player = FindGO<Player>("player");

	m_timer = (new EnemyAIConWaitTime(1.0f));

	m_wallChack = (new EnemyAIConWallSearch);

	m_wallChack->BinedEnemy(&GetEnemyPtr());

	m_wallChack->InitData();
 
}

//�A�b�v�f�[�g�֐�
void EnemyAIMoveAstar::EnemyAIUpdate()
{
	PathFidingExecute();
	
	bool isRetreat = false;

	if (aroundEnemyPtr)
	{
		isRetreat = aroundEnemyPtr->GetRetreat();
	}

	if (m_wallChack->Execution())
	{
		MoveAstar();
	}
	else
	{
		MoveUsually();
	}
}

void EnemyAIMoveAstar::PathFidingExecute()
{
	//�������g�̈ʒu���擾
	Vector3 myPos = GetEnemyPtr().GetPosition();

	//�ړ���̈ʒu���擾
	Vector3 tarPos = GetEnemyPtr().GetMoveTargetPosition();

	if (m_timer->Execution()) {
		m_timer->InitData();
		//�p�X����������
		m_pathFiding.Execute(
			m_path,							//�\�z���ꂽ�p�X�̊i�[��
			m_nvmMesh,						//�i�r���b�V��
			myPos,							//�J�n���W
			tarPos,							//�ړ�����W
			PhysicsWorld::GetInstance(),	//�����G���W��
			1.0f,							//AI�G�[�W�����g�̔��a50.0
			1.0f,							//AI�G�[�W�F���g�̍���200
			[&](const nsAI::PathFinding::CellWork* nextCell
				)-> float {							//�J�X�^���q���[���X�e�B�b�N�R�X�g�̌v�Z

					float t = 0.0f;


					//���̃G�l�~�[����荞�݃X�e�[�g�̃G�l�~�[�łȂ����
					if (GetEnemyPtr().GetTrackingStateNumber() != WarriorTrackingState::en_wrapAround)
					{
						//�߂�
						return t;
					}

					Vector3 behindWarriorPos;

					if (GetEnemyPtr().GetTrackingStateNumber() == WarriorTrackingState::en_wrapAround) {
						for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
						{
							if (ptr->GetTrackingState() == WarriorTrackingState::en_chaseFromBehind)
							{
								chaseEnemyPtr = ptr;
							}
							if (ptr->GetTrackingState() == WarriorTrackingState::en_wrapAround)
							{
								aroundEnemyPtr = ptr;
							}
						}

						if (chaseEnemyPtr) {
							//�ǐՒ��̓G�Ǝ����Ƃ̋������v�Z���ċ߂���Αދp������
							auto toAroundEnemyFromChaseEnemy = (chaseEnemyPtr->GetEnemyPtr().GetPosition() - GetEnemyPtr().GetPosition()).Length();
							if (toAroundEnemyFromChaseEnemy < 100.0f)
							{
								aroundEnemyPtr->SetRetreat(true);

								return 0.0f;
							}
							// �ǐՒ��̓G�Ƃ̋������v�Z���āA�߂��قǃR�X�g�������Ȃ�悤�ɂ���
							auto toPlayerFromChaseEnemy = m_player->GetPosition() - chaseEnemyPtr->GetEnemyPtr().GetPosition();
							auto toPlayerFromNextCell = m_player->GetPosition() - nextCell->cell->GetCenterPosition();
							toPlayerFromChaseEnemy.Normalize();
							toPlayerFromNextCell.Normalize();
							if (toPlayerFromChaseEnemy.Dot(toPlayerFromNextCell) > 0.0f) {
								return 1000000.0f;
							}
							return 0.0f;
						}

					}

					return t;
			}
		);
	}
}

//�G�[�X�^�[�ړ�
void EnemyAIMoveAstar::MoveAstar()
{
	bool isEnd;

	//�������g�̈ʒu���擾
	Vector3 myPos = GetEnemyPtr().GetPosition();

	//�p�X����ړ�����
	//�ړ�����v�Z
	Vector3 pathMovePos = m_path.Move(
		myPos,
		3.0f,
		isEnd
	);

	//��]����������̌v�Z
	Vector3 atan2CalcVec = pathMovePos - myPos;
	//���K������
	atan2CalcVec.Normalize();
	//Y�l��0�ɂ���
	atan2CalcVec.y = 0.0f;

	AstarRotationValueCalc(atan2CalcVec);

	GetEnemyPtr().SetPosition(pathMovePos);

	//���ʒl
	Vector3 newForward = Vector3::AxisZ;

	GetEnemyPtr().GetRotation().Apply(newForward);

	GetEnemyPtr().SetForward(newForward);
}

//�ʏ�ړ�
void EnemyAIMoveAstar::MoveUsually()
{
	//���̃G�l�~�[�̃|�W�V�������擾
	Vector3 enemyPos = GetEnemyPtr().GetPosition();
	//�v���C���[�̃|�W�V�������擾
	Vector3 targetPos = GetEnemyPtr().GetMoveTargetPosition();

	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�����v�Z
	Vector3 diff = targetPos - enemyPos;
	//�x�N�g����P�ʃx�N�g����
	diff.Normalize();
	//�X�s�[�h�����Z
	Vector3 moveSpeed = diff * ENEMY_SPEED;
	//�ŏI�I�Ȉړ��ʒu��ݒ�
	Vector3 finalPos = GetEnemyPtr().GetCController()
		->Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	//�ʒu��ݒ�
	GetEnemyPtr().SetPosition(finalPos);

	//��]�n�̌v�Z
	UsuallyRotationValueCalc(moveSpeed);

	//���ʒl
	Vector3 newForward = Vector3::AxisZ;

	GetEnemyPtr().SetForward(newForward);
}

void EnemyAIMoveAstar::AstarRotationValueCalc(const Vector3& direction)
{
	float angle = atan2(direction.x, direction.z);

	Quaternion finalRot;
	finalRot.SetRotation(Vector3::AxisY, angle);

	//��]�l�𑗂�
	GetEnemyPtr().SetRotation(finalRot);
}

void EnemyAIMoveAstar::UsuallyRotationValueCalc(const Vector3& moveSpeed)
{
	if (fabsf(moveSpeed.x) < 0.001f
		&& fabsf(moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(moveSpeed.x, moveSpeed.z);
	Quaternion rotation;
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	rotation.SetRotationY(angle);
	//��]�l��ݒ�
	GetEnemyPtr().SetRotation(rotation);
}