#pragma once
#include "BootObjectBase.h"

class ManagerLocker;

class Locker : public BootObjectBase
{
public:
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
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// ���b�J�[���s
	/// </summary>
	void LockerExecution();
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
	/// �A�j���[�V�����X�e�[�g
	/// </summary>
	EnAnimationClip m_animationClipState = EnAnimationClip::en_idle;
	/// <summary>
	/// ���b�J�[�̃}�l�[�W���[�̃C���X�^���X
	/// </summary>
	ManagerLocker* m_lockerManager = nullptr;
};

