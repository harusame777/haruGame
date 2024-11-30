#pragma once
#include "Crystal.h"

//�萔��
namespace {
	/// <summary>
	/// �N���X�^���̍ő吔
	/// </summary>
	static const int MAX_CRYSTAL_NUM = 3;
	/// <summary>
	/// �Ĕz�u�܂ł̎���
	/// </summary>
	static const float RELOCATION_TIME = 5.0f;
}

class ManagerCrystal : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ManagerCrystal() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ManagerCrystal() {};
	/// <summary>
	/// �z�u�f�[�^���Đݒ�\�ȏ�Ԃɂ���
	/// </summary>
	/// <param name="crystal"></param>
	void ArrangementDataRefresh(Crystal* crystal);
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
	/// �z��̒��ɍ̎悳��Ă���N���X�^�������邩�ǂ����𒲂ׂ�
	/// </summary>
	/// <returns></returns>
	const bool IsCrystalsAppearance()
	{

		//�N���X�^���̍ő吔�J��Ԃ�
		for (int CryNo = 0; CryNo < MAX_CRYSTAL_NUM; CryNo++)
		{
			//�����擾����Ă���N���X�^������������
			if (m_crystalManageDatas[CryNo]->GetCrystalRelocationState() 
				== CrystalRelocationState::en_notArrangement_State)
			{
				//true��Ԃ�
				return true;
			}
		}

		return false;
	}
	/// <summary>
	/// �Ĕz�u�ݒ�
	/// </summary>
	void InitRelocation();
	/// <summary>
	/// �N���X�^���̐ݒu�Ǘ��X�e�[�g
	/// </summary>
	enum CrystalRelocationState
	{
		/// <summary>
		/// ���ݒu���
		/// </summary>
		en_notArrangement_State,
		/// <summary>
		/// �z�u�ʒu����
		/// </summary>
		en_relocationPosDecision_State,
		/// <summary>
		/// �ݒu�^�C�}�[������
		/// </summary>
		en_relocationTimerProcessing_State,
		/// <summary>
		/// �ݒu���
		/// </summary>
		en_arrangement_State
	};
	/// <summary>
	/// �N���X�^���Ǘ��p�f�[�^
	/// </summary>
	struct CrystalManageData
	{
	private:
		/// <summary>
		/// �N���X�^���̃A�h���X
		/// </summary>
		Crystal* m_crystalAddress = nullptr;
		/// <summary>
		/// �N���X�^���Ĕz�u�܂ł̎���
		/// </summary>
		float m_RelocationTimer = 0.0f;
		/// <summary>
		/// �N���X�^���̐ݒu�Ǘ��X�e�[�g
		/// </summary>
		CrystalRelocationState m_manageCrystalState = CrystalRelocationState::en_arrangement_State;
	public:
		/// <summary>
		/// �N���X�^���̃A�h���X��ݒ�
		/// </summary>
		/// <param name="address"></param>
		void SetCrystalAddress(Crystal* address)
		{
			m_crystalAddress = address;
		}
		/// <summary>
		/// �N���X�^���̃A�h���X��Ԃ�
		/// </summary>
		/// <returns></returns>
		Crystal* GetCrystalAddress() const
		{
			return m_crystalAddress;
		}
		/// <summary>
		/// �^�C�}�[��������
		/// </summary>
		void InitCrystalRelocationTimer()
		{
			m_RelocationTimer = RELOCATION_TIME;
		}
		/// <summary>
		/// ���Z
		/// </summary>
		/// <param name="subTime"></param>
		void SubtractionCrystalRelocationTimer(const float subTime)
		{
			m_RelocationTimer -= subTime;
		}
		/// <summary>
		/// ���݂̍Ĕz�u�܂ł̎��Ԃ�\��
		/// </summary>
		/// <returns></returns>
		const float GetNowCrystalRelocationTimer() const 
		{
			return m_RelocationTimer;
		}
		/// <summary>
		/// �N���X�^���̊Ǘ��X�e�[�g��ݒ�
		/// </summary>
		/// <param name="state"></param>
		void SetCrystalRelocationState(const CrystalRelocationState state)
		{
			m_manageCrystalState = state;
		}
		/// <summary>
		/// �N���X�^���̊Ǘ��X�e�[�g���擾
		/// </summary>
		/// <returns></returns>
		const CrystalRelocationState GetCrystalRelocationState() const
		{
			return m_manageCrystalState;
		}
	};
	/// <summary>
	/// �N���X�^���̃f�[�^�z���_�[
	/// </summary>
	CrystalManageData* m_crystalManageDatas[MAX_CRYSTAL_NUM];
	/// <summary>
	/// �z�u�ʒu����
	/// </summary>
	void RelocationPosDecision(CrystalManageData* crystalData);
	/// <summary>
	///�@�Ĕz�u�^�C�}�[����
	/// </summary>
	void RelocationTimerProcess();
	/// <summary>
	/// �z�u�f�[�^
	/// </summary>
	struct CrystalArrangementData
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
		Crystal* m_crystalAddress = nullptr;
		/// <summary>
		/// �N���X�^�����z�u�����ǂ���
		/// </summary>
		bool m_isCrystalUnderInstallation = false;
	public:
		/// <summary>
		/// �ʒu�ݒ�
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3 pos)
		{
			m_arrangementPos = pos;
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
		void InitAddress(Crystal* crystal)
		{
			m_crystalAddress = crystal;
		}
		/// <summary>
		/// �A�h���X�擾
		/// </summary>
		/// <returns></returns>
		Crystal* GetAddress() const
		{
			return m_crystalAddress;
		}
		/// <summary>
		/// �z�u�����ǂ�����ݒ�
		/// </summary>
		/// <param name="is"></param>
		void SetIsCrystalUnderInstallation(const bool is)
		{
			m_isCrystalUnderInstallation = is;
		}
		/// <summary>
		/// �z�u�����ǂ������擾
		/// </summary>
		/// <returns></returns>
		const bool GetIsCrystalUnderInstallation() const
		{
			return m_isCrystalUnderInstallation;
		}
	};
	/// <summary>
	/// �N���X�^���̈ʒu�f�[�^���i�[���Ă���
	/// </summary>
	std::vector<CrystalArrangementData*> m_crystalArrangementDatas;
	/// <summary>
	/// �N���X�^���̔z�u�ʒu���擾���邽�߂̃��x�������_�[
	/// </summary>
	LevelRender m_crystalArrangementLevelRender;
};

