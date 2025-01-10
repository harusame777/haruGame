#pragma once

class BackGroundWalls : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BackGroundWalls();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BackGroundWalls();
	/// <summary>
	/// �ǂ̎��
	/// </summary>
	enum WallType
	{
		/// <summary>
		/// ��1_4
		/// </summary>
		en_wallType1_4,
		/// <summary>
		/// ��2_4
		/// </summary>
		en_wallType2_4,
		/// <summary>
		/// ��4_4
		/// </summary>
		en_wallType4_4,
		/// <summary>
		/// ��4_6
		/// </summary>
		en_wallType4_6,
		/// <summary>
		/// �ǃh�A�t��4_4
		/// </summary>
		en_wallTypeDoorWay4_4,
		/// <summary>
		/// ��̉�
		/// </summary>
		en_wallOnes,
		/// <summary>
		/// �ǂ̐�
		/// </summary>
		en_wallNum,
		/// <summary>
		/// ���ݒ�
		/// </summary>
		en_wallTypeNone,
	};
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
	/// �ǂ̎�ނ�ݒ�
	/// </summary>
	/// <param name="walltype"></param>
	void SetWallType(const WallType& walltype);
	/// <summary>
	/// �ǂ̎�ނ��ݒ肳��Ă��邩�ǂ���
	/// </summary>
	const bool& IsSetWallType()
	{
		bool isSetWallType;
		isSetWallType = (m_wallType != WallType::en_wallTypeNone);
		return isSetWallType;
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
	/// �ǂ̎��
	/// </summary>
	WallType m_wallType = WallType::en_wallTypeNone;
	/// <summary>
	/// ���C�����f��
	/// </summary>
	ModelRender m_mainModel;
};

