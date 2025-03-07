#pragma once
#include "BootObjectBase.h"

class ManagerLocker;

class Locker : public BootObjectBase
{
public:
	enum LockerState 
	{
		en_standby,

		en_lockerInCameraEasing,

		en_playerInUse,

		en_lockerOutCameraEasing,

	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Locker() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Locker() {};
	/// <summary>
	/// ���b�J�[���g�p�����ǂ���
	/// </summary>
	/// <returns></returns>
	const bool IsLockerInUse() const
	{
		return m_isLockerInUse;
	}
	/// <summary>
	/// �}�l�[�W���[�̃C���X�^���X��ݒ�
	/// </summary>
	/// <param name="address"></param>
	void SetManegerInstance(ManagerLocker& address)
	{
		m_lockerManager = &address;
	}
private:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �A�j���[�V�����C�x���g�֐�
	/// </summary>
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// ���b�J�[���s
	/// </summary>
	void LockerStateUpdate();
	/// <summary>
	/// ���b�J�[�̃X�e�[�g
	/// </summary>
	LockerState m_lockerState = LockerState::en_standby;
	/// <summary>
	/// ���b�J�[���鎞�̃J�����C�[�W���O����
	/// </summary>
	const bool LockerInCameraEasing(const bool swap);
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �A�j���[�V�����N���b�v
	/// </summary>
	enum EnAnimationClip
	{
		en_idle,

		en_OpenLocker,

		en_animationNum
	};
	/// <summary>
	/// �A�j���[�V�����N���b�v
	/// </summary>
	AnimationClip m_animationClip[en_animationNum];
	/// <summary>
	/// ���̃��b�J�[���g�p�����ǂ���
	/// </summary>
	bool m_isLockerInUse = false;
	/// <summary>
	/// �J�����C�[�W���O�p�ϐ�
	/// </summary>
	Vector3 m_cameraEasingStart = Vector3::Zero;
	Vector3 m_cameraEasingEnd = Vector3::Zero;
	float m_cameraEasingRatio = 0.0f;
	/// <summary>
	/// �A�j���[�V�����X�e�[�g
	/// </summary>
	EnAnimationClip m_animationClipState = EnAnimationClip::en_idle;
	/// <summary>
	/// ���b�J�[�̃}�l�[�W���[�̃C���X�^���X
	/// </summary>
	ManagerLocker* m_lockerManager = nullptr;
	/// <summary>
	/// �J�������W�擾�p
	/// </summary>
	LevelRender m_cameraPosInLevel;
	/// <summary>
	/// �J�����̃^�[�Q�b�g�|�W�V����
	/// </summary>
	Vector3 m_cameraTargetPos = Vector3::Zero;
};

