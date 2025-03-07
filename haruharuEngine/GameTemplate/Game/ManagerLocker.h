#pragma once
#include "Locker.h"
#include "LockerDataHolder.h"

class Player;
class GameCamera;

class ManagerLocker : public IGameObject
{
public:
	/// <summary>
	/// ���b�J�[�Ǘ��X�e�[�g
	/// </summary>
	enum LockerManageState
	{
		//�ݒu�O
		en_standby,
		//�z�u��
		en_underplacement,
		//���Ă�
		en_broken,
	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ManagerLocker() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ManagerLocker() {};
	/// <summary>
	/// �f�[�^�z���_�[���擾
	/// </summary>
    /// <returns></returns>
	std::shared_ptr<LockerDataHolder> GetLockerDataHolder()
	{
		return m_lockerDataHolder;
	}
	/// <summary>
	/// �S�̂̒��Ń��b�J�[����ł��g�p�����ǂ���
	/// </summary>
	/// <returns></returns>
	const bool IsWholeLockersInUse();
	/// <summary>
	/// �v���C���[�����b�J�[�ɓ��������̏���
	/// </summary>
	void SetPlayerInLocker();
	/// <summary>
	/// �v���C���[�����b�J�[����o�����̏���
	/// </summary>
	void SetPlayerOutLocker();
	/// <summary>
	/// �J�����̃^�[�Q�b�g��ݒ�
	/// </summary>
	void SetCameraTarget(const Vector3& pos);
private:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �z�u����
	/// </summary>
	void InitArrangement();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// ���b�J�[�̊Ǘ��p�f�[�^
	/// </summary>
	struct LockerManageData
	{
	private:
		/// <summary>
		/// ���b�J�[�̃A�h���X
		/// </summary>
		Locker* m_lockerAddress = nullptr;
		/// <summary>
		/// ���b�J�[�Ǘ��X�e�[�g
		/// </summary>
		LockerManageState m_lockerManageState = LockerManageState::en_standby;
	public:
		/// <summary>
		/// ���b�J�[�̃A�h���X��ݒ�
		/// </summary>
		/// <param name="address"></param>
		void SetLockerAddress(Locker* address)
		{
			m_lockerAddress = address;
		}
		/// <summary>
		/// ���b�J�[�̃A�h���X��Ԃ�
		/// </summary>
		/// <returns></returns>
		Locker* GetLockerAddress() const
		{
			return m_lockerAddress;
		}
		/// <summary>
		/// ���b�J�[�̊Ǘ��X�e�[�g��ݒ�
		/// </summary>
		/// <param name="state"></param>
		void SetLockerRelocationState(const LockerManageState state)
		{
			m_lockerManageState = state;
		}
		/// <summary>
		/// ���b�J�[�̊Ǘ��X�e�[�g���擾
		/// </summary>
		/// <returns></returns>
		const LockerManageState GetLockerRelocationState() const
		{
			return m_lockerManageState;
		}
	};
	/// <summary>
	/// ���b�J�[�̊Ǘ��p�f�[�^�z��
	/// </summary>
	LockerManageData m_lockerManageDatas[MAX_LOCKER_NUM];
	/// <summary>
	/// ���b�J�[�z�u�ʒu�f�[�^
	/// </summary>
	struct LockerArrangementData
	{
	private:
		/// <summary>
		/// �z�u�ʒu
		/// </summary>
		Vector3 m_arrangementPos = Vector3::Zero;
		/// <summary>
		/// �z�u��]
		/// </summary>
		Quaternion m_arrangementRot;
		/// <summary>
		/// ���̈ʒu�ɔz�u����Ă���N���X�^���̃A�h���X
		/// </summary>
		Locker* m_lockerAddress = nullptr;
		/// <summary>
		/// ���b�J�[���z�u�����ǂ���
		/// </summary>
		bool m_isLockerUnderInstallation = false;
	public:
		/// <summary>
		/// �ʒu�ݒ�
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3 pos)
		{
			m_arrangementPos = pos;
		}
		void LockerPosAndRotUpdate()
		{
			m_lockerAddress->SetPosition(m_arrangementPos);

			m_lockerAddress->SetRotation(m_arrangementRot);
		}
		/// <summary>
		/// �ʒu�擾
		/// </summary>
		/// <returns></returns>
		const Vector3 GetPosition() const
		{
			return m_arrangementPos;
		}
		/// <summary>
		/// ��]�ݒ�
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion rot)
		{
			m_arrangementRot = rot;
		}
		/// <summary>
		/// ��]�擾
		/// </summary>
		/// <returns></returns>
		const Quaternion GetRotation() const
		{
			return m_arrangementRot;
		}
		/// <summary>
		/// �A�h���X������
		/// </summary>
		/// <param name="crystal"></param>
		void InitAddress(Locker* locker)
		{
			m_lockerAddress = locker;
		}
		/// <summary>
		/// �A�h���X�擾
		/// </summary>
		/// <returns></returns>
		Locker* GetAddress() const
		{
			return m_lockerAddress;
		}
		/// <summary>
		/// �z�u�����ǂ�����ݒ�
		/// </summary>
		/// <param name="is"></param>
		void SetIsLockerUnderInstallation(const bool is)
		{
			m_isLockerUnderInstallation = is;
		}
		/// <summary>
		/// �z�u�����ǂ������擾
		/// </summary>
		/// <returns></returns>
		bool GetIsCrystalUnderInstallation() const
		{
			return m_isLockerUnderInstallation;
		}
	};
	/// <summary>
	/// ���b�J�[�̃f�[�^�z���_�[
	/// </summary>
	std::shared_ptr<LockerDataHolder> m_lockerDataHolder;
	/// <summary>
	/// ���b�J�[�̈ʒu�f�[�^���i�[���Ă���
	/// </summary>
	std::vector<LockerArrangementData*> m_lockerArrangementDatas;
	/// <summary>
	/// ���b�J�[�̔z�u�ʒu���擾���邽�߂̃��x�������_�[
	/// </summary>
	LevelRender m_lockerArrangementLevelRender;
	/// <summary>
	/// �v���C���[�̃C���X�^���X
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �v���C���[�J�����̃C���X�^���X
	/// </summary>
	GameCamera* m_gameCamera = nullptr;
};

