#include "stdafx.h"
#include "DebugEnemyTrackingState.h"
#include "EnemyWarriorTrackingState.h"
#include "WarriorDataHolder.h"

//�萔��
namespace {
	/// <summary>
	/// �����T�C�Y
	/// </summary>
	static const float SPRITE_W_SIZE = 150.0f;
	static const float SPRITE_H_SIZE = 150.0f;
}

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
	//�D�F�}�[�J�[��ݒ�
	m_grayMarker.Init("Assets/modelData/debug/testWarriorTrackingStateGray.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	//�ԐF�}�[�J�[��ݒ�
	m_redMarker.Init("Assets/modelData/debug/testWarriorTrackingStateRed.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	//���F�}�[�J�[��ݒ�
	m_yellowMarker.Init("Assets/modelData/debug/testWarriorTrackingStateYellow.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	//�ΐF�}�[�J�[��ݒ�
	m_greenMarker.Init("Assets/modelData/debug/testWarriorTrackingStateGreen.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);


	//warrior�̐���3��
	for (int i = 0; i < 3; i++)
	{
		m_stateMarkers[i].m_makerColor[WarriorTrackingState::en_nonTracking] = &m_grayMarker;
		m_stateMarkers[i].m_makerColor[WarriorTrackingState::en_chaseFromBehind] = &m_redMarker;
		m_stateMarkers[i].m_makerColor[WarriorTrackingState::en_wrapAround] = &m_yellowMarker;
		m_stateMarkers[i].m_makerColor[WarriorTrackingState::en_usually] = &m_greenMarker;
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
	int dataNum = 0;

	//�E�H���A�[�̐��Ԃ��
	for (const auto& ptr: m_warriorDataHolder->m_warriorDatas)
	{
		//�E�H���A�[�̈ʒu���擾
		m_stateMarkers[dataNum].m_warriorPosition = ptr->GetEnemyPtr().GetPosition();
		//�I�u�W�F�N�g�̏�̕��ɉ摜��\���������̂ŁB
		//y���W�������傫������B
		m_stateMarkers[dataNum].m_warriorPosition.y += 80.0f;
		//���[���h���W����X�N���[�����W���v�Z�B
		//�v�Z���ʂ�m_spritePosition�Ɋi�[����
		g_camera3D->CalcScreenPositionFromWorldPosition(m_stateMarkers[dataNum].m_spritePosition
			, m_stateMarkers[dataNum].m_warriorPosition);
		//�z���i�߂�
		dataNum++;
	}

}

void DebugEnemyTrackingState::SpriteUpdate()
{
	int dataNum = 0;

	//�E�H���A�[�̐��Ԃ��
	for (const auto& ptr : m_warriorDataHolder->m_warriorDatas)
	{
		m_stateMarkers[dataNum].m_warriorTrackingStateNum = ptr->GetEnemyPtr().GetTrackingStateNumber();

		m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]
			->SetPosition(Vector3(m_stateMarkers[dataNum].m_spritePosition.x, m_stateMarkers[dataNum].m_spritePosition.y, 0.0f));

		m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]->Update();

		dataNum++;
	}

}

//�h���[�֐�
void DebugEnemyTrackingState::Render(RenderContext& rc)
{
	int dataNum = 0;

	for (const auto& ptr : m_warriorDataHolder->m_warriorDatas)
	{
		m_stateMarkers[dataNum].m_makerColor[m_stateMarkers[dataNum].m_warriorTrackingStateNum]->Draw(rc);

		dataNum++;
	}
}