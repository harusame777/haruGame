#pragma once
#include "EnemyAIBase.h"

class EnemyBase : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyBase()
	{

	}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EnemyBase()
	{

	}
protected:
	/// <summary>
	/// AIList�̏�����
	/// </summary>
	virtual void InitAIList() = 0;
	/// <summary>
	/// AIList���̃v���O�����̃A�b�v�f�[�g
	/// </summary>
	virtual void AIListUpdate() = 0;
	/// <summary>
	/// ���ݍ��W
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// ���݉�]�l
	/// </summary>
	Quaternion m_rotation;
	/// <summary>
	/// ���݊g��l
	/// </summary>
	Vector3 m_scale = Vector3::One;
	/// <summary>
	/// ���ݐ��ʃx�N�g��
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// �L�����R��
	/// </summary>
	CharacterController m_CController;
	/// <summary>
	/// �ړ���̈ʒu
	/// </summary>
	Vector3 m_moveTargetPosition = Vector3::Zero;
	/// <summary>
	/// �G�l�~�[�E�H���A�[�̃X�e�[�g�}�V��
	/// </summary>
	EnemyAIBase* m_enemyWarriorSM = nullptr;
	/// <summary>
	/// ���݂̃X�e�[�g�̐��l
	/// </summary>
	int m_stateNumber = -1;
	/// <summary>
	/// �f�o�b�N�p�t�H���g�����_�[
	/// </summary>
	FontRender m_debugStateDisplayRender;
public:
	/// <summary>
	/// �ʒu�ݒ�
	/// </summary>
	/// <param name="pos = ���W"></param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// �ʒu�擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ��]�ݒ�
	/// </summary>
	/// <param name="rot = ��]"></param>
	void SetRotation(const Quaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]�擾
	/// </summary>
	/// <returns></returns>
	const Quaternion& GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// �g�嗦�ݒ�
	/// </summary>
	/// <param name="sca = �g�嗦"></param>
	void SetScale(const Vector3& sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// �g�嗦�擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetScale()
	{
		return m_scale;
	}
	/// <summary>
	/// ���ʃx�N�g���ݒ�
	/// </summary>
	/// <param name="forward = ���ʃx�N�g��"></param>
	void SetForward(const Vector3& forward)
	{
		m_forward = forward;
	}
	/// <summary>
	/// ���ʃx�N�g���擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetFoward()
	{
		return m_forward;
	}
	/// <summary>
	/// �ړ���ʒu��ݒ�
	/// </summary>
	/// <param name="movePosition = �ړ�����W"></param>
	void SetMoveTargetPosition(const Vector3& movePosition)
	{
		m_moveTargetPosition = movePosition;
	}
	/// <summary>
	/// �ړ���ʒu���擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetMoveTargetPosition()
	{
		return m_moveTargetPosition;
	}
	/// <summary>
	/// �X�e�[�g�i���o�[��ݒ�
	/// </summary>
	/// <param name="stateNum = �X�e�[�g�i���o�["></param>
	void SetStateNumber(const int stateNum)
	{
		m_stateNumber = stateNum;
	}
	/// <summary>
	/// �X�e�[�g�i���o�[���擾
	/// </summary>
	/// <returns></returns>
	const int GetStateNumber()
	{
		return m_stateNumber;
	}
	/// <summary>
	/// �f�o�b�N�f�B�X�v���C�����ݒ�
	/// </summary>
	void DebugStateDisplay()
	{
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"NowState[%01d]", int(m_stateNumber));

		m_debugStateDisplayRender.SetText(wcsbuf);
	}
};

