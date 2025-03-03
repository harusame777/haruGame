#pragma once
#include "BootObjectBase.h"

class Player;
class CrystalGetCommandSprite;
class ManagerCrystal;
class PlayerScoreUi;

class Crystal : public BootObjectBase
{
public:
	enum CrystalColor{
		en_crystal_M,
		en_crystal_R,
		en_crystal_Y,
	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Crystal();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Crystal();
	/// <summary>
	/// ���̃N���X�^���͍̎悳��܂���
	/// </summary>
	void CrystalCollected();
	/// <summary>
	/// ���̃N���X�^���̍̎�Ɏ��s���܂���
	/// </summary>
	void CollectedFailure()
	{
		//�̎�N�[���^�C����������
		m_collectCoolTime = 2.0f;
	}
	//�N���X�^����z�u����
	void CrystalArrangement()
	{
		m_isGetObject = false;
	}
	/// <summary>
	/// �̎悳��Ă��邩�ǂ������擾
	/// </summary>
	/// <returns></returns>
	const bool GetCollected() const
	{
		return m_isGetObject;
	}
	/// <summary>
	/// �N���X�^���̃J���[������
	/// </summary>
	/// <param name="color"></param>
	void CrystalSetColor(const CrystalColor color)
	{
		m_crystalColorState = color;
	}
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
	/// �̎�N�[���^�C��
	/// </summary>
	float m_collectCoolTime = 0.0f;
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
	/// <summary>
	/// �N���X�^���̃��^AI�̃C���X�^���X
	/// </summary>
	ManagerCrystal* m_managerCrystalPtr = nullptr;
	/// <summary>
	/// �X�R�A��Ui
	/// </summary>
	PlayerScoreUi* m_scoreUi = nullptr;
	/// <summary>
	/// �N���X�^���̃��f��
	/// </summary>
	ModelRender m_crystal_M_Model;
	ModelRender m_crystal_R_Model;
	ModelRender m_crystal_Y_Model;
	/// <summary>
	/// �N���X�^���̐F�X�e�[�g
	/// </summary>
	CrystalColor m_crystalColorState = CrystalColor::en_crystal_M;
	/// <summary>
	/// �X�R�A
	/// </summary>
	float m_scoreM = 150.0f;
	float m_scoreR = 400.0f;
	float m_scoreY = 1500.0f;
};

