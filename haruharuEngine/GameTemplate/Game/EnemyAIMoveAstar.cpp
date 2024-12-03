#include "stdafx.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyBase.h"
#include "WarriorDataHolder.h"
#include "Player.h"
#include <cmath>
#include "EnemyAIConBase.h"
#include "EnemyAIConWaitTime.h"

//�����L���ɂ���ƃf�o�b�O���[�h�ɂȂ�
//#define DEBUG_MODE

//�X�^�[�g�֐�
void EnemyAIMoveAstar::EnemyAIStart()
{
	m_nvmMesh.Init("Assets/nvm/testnvm10.tkn");

	m_player = FindGO<Player>("player");

	m_timer = (new EnemyAIConWaitTime(1.0f));
 
}

//�A�b�v�f�[�g�֐�
void EnemyAIMoveAstar::EnemyAIUpdate()
{
	bool isEnd;

	//�������g�̈ʒu���擾
	Vector3 myPos = GetEnemyPtr().GetPosition();
	
	//�ړ���̈ʒu���擾
	Vector3 tarPos = GetEnemyPtr().GetMoveTargetPosition();

#ifdef DEBUG_MODE
	if (g_pad[0]->IsPress(enButtonA))
	{
#endif
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

						EnemySM_Warrior* aroundEnemyPtr = nullptr;

						//���̃G�l�~�[����荞�݃X�e�[�g�̃G�l�~�[�łȂ����
						if (GetEnemyPtr().GetTrackingStateNumber() != WarriorTrackingState::en_wrapAround)
						{
							//�߂�
							return t;
						}

						Vector3 behindWarriorPos;

						if (GetEnemyPtr().GetTrackingStateNumber() == WarriorTrackingState::en_wrapAround) {
							EnemySM_Warrior* chaseEnemyPtr = nullptr;
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
								/*auto diff = chaseEnemyPtr->GetEnemyPtr().GetPosition() - nextCell->cell->GetCenterPosition();
								float t =pow( min(1.0f, diff.Length() / 10000.0f), 0.1f);
								auto toPlayerFromChaseEnemy = m_player->GetPosition() - chaseEnemyPtr->GetEnemyPtr().GetPosition();
								auto toPlayerFromNextCell = m_player->GetPosition() - nextCell->cell->GetCenterPosition();
								toPlayerFromChaseEnemy.Normalize();
								toPlayerFromNextCell.Normalize();
								t *= max(0.0f, toPlayerFromChaseEnemy.Dot(toPlayerFromNextCell));
								t = std::lerp(100000, 0, t);
								*/
								return t;
							}

						}

#if 0
						for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
						{
							if (ptr->GetTrackingState() != WarriorTrackingState::en_chaseFromBehind)
							{
								return t;
							}

							behindWarriorPos = ptr->GetEnemyPtr().GetPosition();

							Vector3 cellPos = nextCell->cell->GetCenterPosition();

							float behindWarriorToCellPosDiff = (cellPos - behindWarriorPos).Length();

							Vector3 playerPos = m_player->GetPosition();

							float behindWarriorToPlayerPosDiff = (playerPos - behindWarriorPos).Length();

							if (behindWarriorToCellPosDiff <= 500.0f/*behindWarriorToPlayerPosDiff*/)
							{
								t += 10000.0f;
							}

						}
#endif

						return t;
				}
			);
		}
#ifdef DEBUG_MODE
	}
#endif

		//�p�X����ړ�����
		//�ړ�����v�Z
		Vector3 pathMovePos = m_path.Move(
			myPos,
			5.0f,
			isEnd
		);

		//��]����������̌v�Z
		Vector3 atan2CalcVec = pathMovePos - myPos;
		//���K������
		atan2CalcVec.Normalize();
		//Y�l��0�ɂ���
		atan2CalcVec.y = 0.0f;

		RotationValueCalc(atan2CalcVec);

		//Vector3 moveVec = { 0.0f,0.0f,0.0f };

		//moveVec = pathMovePos;

		//moveVec.Normalize();

		//moveVec += GetEnemyPtr().GetFoward() * 150.0f;

		//Vector3 newPos = GetEnemyPtr().GetCController()->Execute(moveVec, g_gameTime->GetFrameDeltaTime());

		////�ړ��������W�𑗂�
		//GetEnemyPtr().SetPosition(newPos);

		GetEnemyPtr().SetPosition(pathMovePos);


		//���ʒl
		Vector3 newForward = Vector3::AxisZ;

		GetEnemyPtr().GetRotation().Apply(newForward);

		GetEnemyPtr().SetForward(newForward);
}

void EnemyAIMoveAstar::RotationValueCalc(const Vector3& direction)
{
	float angle = atan2(direction.x, direction.z);

	Quaternion finalRot;
	finalRot.SetRotation(Vector3::AxisY, angle);

	//��]�l�𑗂�
	GetEnemyPtr().SetRotation(finalRot);
}