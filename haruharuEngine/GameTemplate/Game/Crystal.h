#pragma once
#include "ObjectBase.h"

class Crystal : public ObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Crystal();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Crystal();
private:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �I�u�W�F�N�g�擾�֐�
	/// </summary>
	void GetObject();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	void Render(RenderContext& rc);
	/// <summary>
	/// ���̃I�u�W�F�N�g���擾����Ă��邩�ǂ���
	/// </summary>
	bool m_isGetObject = false;
};

