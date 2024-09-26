#pragma once

class BackGroundFloor : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BackGroundFloor();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BackGroundFloor();
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos = ���W"></param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot = ��]"></param>
	void SetRotation(const Quaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]���擾
	/// </summary>
	/// <returns></returns>
	const Quaternion& GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="sca = �g�嗦"></param>
	void SetScale(const Vector3& sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <returns></returns>
	const Vector3& GetScale()
	{
		return m_scale;
	}
	/// <summary>
	/// ���ʃx�N�g����ݒ�
	/// </summary>
	/// <param name="forward = ���ʃx�N�g��"></param>
	void SetForward(const Vector3& forward)
	{
		m_forward = forward;
	}
	/// <summary>
	/// ���ʃx�N�g�����擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetForward()
	{
		return m_forward;
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
	/// �h���[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ���W
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// ��]
	/// </summary>
	Quaternion m_rotation;
	/// <summary>
	/// �g�嗦
	/// </summary>
	Vector3 m_scale = Vector3::Zero;
	/// <summary>
	/// ���ʃx�N�g��
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// �����蔻��
	/// </summary>
	PhysicsStaticObject m_physicsStaticObject;
	/// <summary>
	/// ���f�������_�[
	/// </summary>
	ModelRender m_modelRender;
};

