#pragma once
#include "ObjectBase.h"

class Player;
class CrystalGetCommandSprite;

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
	/// �N���X�^���擾�֐�
	/// </summary>
	void GetCrystal();
	/// <summary>
	/// ���C�e�X�g���s���ĕǂ��Ȃ����ǂ����𒲂ׂ�֐�
	/// </summary>
	/// <returns></returns>
	const bool IsLookCrystal();
	/// <summary>
	/// �擾�͈͓��Ƀv���C���[�����邩�ǂ������ׂ�֐�
	/// </summary>
	/// <returns></returns>
	const bool IsInGetRange();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	void Render(RenderContext& rc); 
	/// <summary>
	/// ���̃I�u�W�F�N�g���擾����Ă��邩�ǂ���
	/// </summary>
	bool m_isGetObject = false;
	/// <summary>
	/// �R���C�_�[
	/// </summary>
	SphereCollider m_sphereCollider;
	/// <summary>
	/// �v���C���[�̃C���X�^���X
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �N���X�^���̎擾�R�}���h�\���v���O�����̃C���X�^���X
	/// </summary>
	CrystalGetCommandSprite* m_GetCOMSprite = nullptr;
	/// <summary>
	/// �f�o�b�N�p��fontrender
	/// </summary>
	FontRender m_debugFontRender;
};

