#include "stdafx.h"
#include "DebugEnemyTrackingState.h"
#include "EnemyWarriorTrackingState.h"
#include "WarriorDataHolder.h"
#include "EnemySM_Warrior.h"


//�R���X�g���N�^
DebugEnemyTrackingState::DebugEnemyTrackingState()
{

}

//�f�X�g���N�^
DebugEnemyTrackingState::~DebugEnemyTrackingState()
{

}

//�X�^�[�g�֐�
bool DebugEnemyTrackingState::Start()
{

	

	//warrior�̐���3��
	for (auto& ptr : m_warriorDataHolder->m_warriorDatas)
	{

		EnemyDebugStruct* newList = new EnemyDebugStruct;

		newList->InitColor();

		newList->m_enemySM = ptr;

		m_enemyDebugSpriteList.push_back(newList);

	}

	return true;
}

//�A�b�v�f�[�g�֐�
void DebugEnemyTrackingState::Update()
{
	if (m_warriorDataHolder == nullptr)
	{
		return;
	}

	//�}�[�J�[�̈ʒu���X�V����
	MarkerPositionUpdate();
	//�`��X�V
	SpriteUpdate();
}

void DebugEnemyTrackingState::MarkerPositionUpdate()
{
	//int dataNum = 0;

	////�E�H���A�[�̐��Ԃ��
	//for (const auto& ptr: m_warriorDataHolder->m_warriorDatas)
	//{
	//	//�E�H���A�[�̈ʒu���擾
	//	m_stateMarkers[dataNum].m_warriorPosition = ptr->GetEnemyPtr().GetPosition();
	//	//�I�u�W�F�N�g�̏�̕��ɉ摜��\���������̂ŁB
	//	//y���W�������傫������B
	//	m_stateMarkers[dataNum].m_warriorPosition.y += 80.0f;
	//	//���[���h���W����X�N���[�����W���v�Z�B
	//	//�v�Z���ʂ�m_spritePosition�Ɋi�[����
	//	g_camera3D->CalcScreenPositionFromWorldPosition(m_stateMarkers[dataNum].m_spritePosition
	//		, m_stateMarkers[dataNum].m_warriorPosition);
	//	//�z���i�߂�
	//	dataNum++;
	//}

	for (auto& ptr : m_enemyDebugSpriteList)
	{
		//�E�H���A�[�̈ʒu���擾
		ptr->m_warriorPosition = ptr->m_enemySM->GetEnemyPtr().GetPosition();
		//�I�u�W�F�N�g�̏�̕��ɉ摜��\���������̂ŁB
		//y���W�������傫������B
		ptr->m_warriorPosition.y += 80.0f;
		//���[���h���W����X�N���[�����W���v�Z�B
		//�v�Z���ʂ�m_spritePosition�Ɋi�[����
		g_camera3D->CalcScreenPositionFromWorldPosition(ptr->m_spritePosition, ptr->m_warriorPosition);
	}

}

void DebugEnemyTrackingState::SpriteUpdate()
{
	//int dataNum = 0;

	////�E�H���A�[�̐��Ԃ��
	//for (const auto& ptr : m_warriorDataHolder->m_warriorDatas)
	//{
	//	m_stateMarkers[dataNum].m_warriorTrackingStateNum = ptr->GetEnemyPtr().GetTrackingStateNumber();

	//	m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]
	//		->SetPosition(Vector3(m_stateMarkers[dataNum].m_spritePosition.x, m_stateMarkers[dataNum].m_spritePosition.y, 0.0f));

	//	m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]->Update();

	//	dataNum++;
	//}

	for (auto& ptr : m_enemyDebugSpriteList)
	{
		ptr->m_warriorTrackingStateNum = ptr->m_enemySM->GetEnemyPtr().GetTrackingStateNumber();

		ptr->m_colorList[ptr->m_warriorTrackingStateNum]->m_makerColor.SetPosition(Vector3(ptr->m_spritePosition.x , ptr->m_spritePosition.y , 0.0f));

		ptr->m_colorList[ptr->m_warriorTrackingStateNum]->m_makerColor.Update();
	}

}

//�h���[�֐�
void DebugEnemyTrackingState::Render(RenderContext& rc)
{
	//int dataNum = 0;

	//for (const auto& ptr : m_warriorDataHolder->m_warriorDatas)
	//{
	//	m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]->Draw(rc);

	//	dataNum++;
	//}

	for (auto& ptr : m_enemyDebugSpriteList)
	{
		if (IsInCamera(ptr))
		{
			ptr->m_colorList[ptr->m_warriorTrackingStateNum]->m_makerColor.Draw(rc);
		}
	}
}

const bool DebugEnemyTrackingState::IsInCamera(EnemyDebugStruct* ptr)
{

	Vector3 diff = ptr->m_enemySM->GetEnemyPtr().GetPosition() - g_camera3D->GetPosition();

	//�G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K��
	diff.Normalize();
	//�G�l�~�[�̐��ʃx�N�g���ƁA�G����v���C���[�Ɍ������x�N�g����
	//����(cos��)�����߂�B
	float cos = g_camera3D->GetForward().Dot(diff);
	if (cos >= 1)
	{
		cos = 1.0f;
	}
	//����(cos��)����p�x(��)�����߂�
	float angle = acosf(cos);
	//�p�x(��)��90��(����p)��菬�������
	if (angle <= (Math::PI / 180.0f) * 90.0f)
	{

		return true;

	}

	return false;
}