#pragma once

class Player;
class PlayerInteractableUi;

class BootObjectBase : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BootObjectBase(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BootObjectBase(){}
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
	/// �N�����W��������
	/// ���x���Ŏ擾�A�ʒu�̖��O��bootPosition�Œ�
	/// </summary>
	/// <param name="filePath"></param>
	void InitBootObject(const char* filePath);
	/// <summary>
	/// �N�����W�擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetBootPosition() const
	{
		return m_bootPosition;
	}
	/// <summary>
	/// �I�u�W�F�N�g���N���ł�������ɂ��邩�ǂ������ׂ�֐�
	/// </summary>
	/// <returns></returns>
	const bool IsObjectBootConditions();
	/// <summary>
	/// �ʒu���Z�b�g
	/// </summary>
	/// <param name="resetPos"></param>
	void UpdateBootData();
private:
	/// <summary>
	/// �I�u�W�F�N�g���N���\�J�����x�N�^�[�������ɂ��邩�ǂ������ׂ�֐�
	/// </summary>
	/// <returns></returns>
	const bool IsObjectBootingCameraVector();
	/// <summary>
	/// �I�u�W�F�N�g���N���\�Ȕ͈͓����W�ɂ��邩�ǂ����𒲂ׂ�֐�
	/// </summary>
	/// <returns></returns>
	const bool IsObjectBootingRange();
	/// <summary>
	/// ���C���g�p���ĕǂɃ��C���������������ׂ�֐�
	/// </summary>
	/// <returns></returns>
	const bool IsRayTestWall();
protected:
	/// <summary>
	/// ���ݍ��W
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// ���݉�]
	/// </summary>
	Quaternion m_rotation;
	/// <summary>
	/// ���݊g�嗦
	/// </summary>
	Vector3 m_scale = Vector3::One;
	/// <summary>
	/// ���ݐ��ʃx�N�g��
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// �����蔻��
	/// </summary>
	PhysicsStaticObject m_physicsStaticObject;
	/// <summary>
	/// ���C�����f��
	/// </summary>
	ModelRender m_mainModel;
private:
	/// <summary>
	/// ���x����̍��W
	/// </summary>
	Vector3 m_levelPosition = Vector3::Zero;
	/// <summary>
	/// ���x��
	/// </summary>
	LevelRender m_getBootPosition;
	/// <summary>
	/// �v���C���[�̃C���X�^���X
	/// </summary>
	Player* m_bootPlayer = nullptr;
	/// <summary>
	/// �N�����W
	/// </summary>
	Vector3 m_bootPosition = Vector3::Zero;
	/// <summary>
	/// �C���^���N�g�\�X�v���C�gUi�̃C���X�^���X
	/// </summary>
	PlayerInteractableUi* m_playerInteractableUi = nullptr;
	/// <summary>
	/// �R���C�_�[
	/// </summary>
	SphereCollider m_sphereCollider;
};

