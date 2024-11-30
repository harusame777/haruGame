#pragma once
#include "PlayerUIBase.h"
#include "Crystal.h"
#include "CrystalDataHolder.h"
//�ꎞ�I�ȃ��m����Ŏ��ԏ�������������
#include "EnemyAIConBase.h"

class Player;

class PlayerScanCrystalUi : public PlayerUIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerScanCrystalUi() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerScanCrystalUi() {};
	/// <summary>
	/// �f�[�^�z���_�[�Z�b�g
	/// </summary>
	/// <param name="dataHolder"></param>
	void InitCrystalDataHolder(std::shared_ptr<CrystalDataHolder> dataHolder)
	{
		m_crystalDataHolder = dataHolder;
	}
private:
	enum ScanState
	{
		/// <summary>
		/// �ҋ@���
		/// </summary>
		en_scanStandby,
		/// <summary>
		/// ��������`��
		/// </summary>
		en_scanLineEasing,
		/// <summary>
		/// �A���t�@�l���C�[�W���O
		/// </summary>
		en_scanAEasing,
		/// <summary>
		/// �}�[�J�[��`��
		/// </summary>
		en_scanMarkerDraw,
	};
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �C���t�H���[�V�����̃f�[�^�̏�����
	/// </summary>
	void InitInfomationDatas();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �X�v���C�g�X�V
	/// </summary>
	void SpriteUpdate();
	/// <summary>
	/// �A���t�@�l�̃C�[�W���O
	/// </summary>
	/// <returns></returns>
	const float AlphaEasingWeakBlinking();
	/// <summary>
	/// ���C�v�̃C�[�W���O�֐�
	/// </summary>
	/// <returns></returns>
	const float WipeEasing();
	/// <summary>
	/// �v���C���[�̃J�������ɂ��邩�𒲂ׂ�
	/// </summary>
	/// <returns></returns>
	const bool AngleCheck();
	/// <summary>
	/// �h���[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �X�L�����X�e�[�g
	/// </summary>
	ScanState m_scanState = ScanState::en_scanStandby;
	/// <summary>
	/// �������̃X�v���C�g
	/// </summary>
	SpriteRender m_scanlineSprite;
	/// <summary>
	/// �������̃f�[�^
	/// </summary>
	struct ScanLineSpriteData
	{
		/// <summary>
		/// ���C�v����
		/// </summary>
		Vector2 m_wipeDir;
		/// <summary>
		/// ���C�v�T�C�Y
		/// </summary>
		float m_wipeSize;
		/// <summary>
		/// �A���t�@�l
		/// </summary>
		float m_paramA = 1.0f;
	};
	/// <summary>
	/// �������̃f�[�^�ϐ�
	/// </summary>
	ScanLineSpriteData m_scanLineData;
	/// <summary>
	/// �A���t�@�l����
	/// </summary>
	float m_alphaRatio = 0.0f;
	/// <summary>
	/// �C�[�W���O����ւ�
	/// </summary>
	bool m_swapEasing = true;
	/// <summary>
	/// ���C�v����
	/// </summary>
	float m_wipeRatio = 1.0f;
	/// <summary>
	/// �C���t�H���[�V�����̃C�[�W���O�̃f�[�^
	/// </summary>
	struct InfomationEasingData
	{
		/// <summary>
		/// ���C�v����
		/// </summary>
		Vector2 m_wipeDir;
		/// <summary>
		/// ���C�v�T�C�Y
		/// </summary>
		float m_wipeSize;
		/// <summary>
		/// �A���t�@�l
		/// </summary>
		float m_paramA = 1.0f;
	};
	/// <summary>
	/// �C���t�H���[�V�����̃f�[�^
	/// </summary>
	struct InfomationData
	{
	public:
		/// <summary>
		/// �X�v���C�g�̃|�C���^
		/// </summary>
		SpriteRender m_infoPtr;
		/// <summary>
		/// �C���t�H���[�V�����̃C�[�W���O�̃f�[�^
		/// </summary>
		InfomationEasingData m_easingData;
	private:
		/// <summary>
		/// �N���X�^���̃f�[�^
		/// </summary>
		Crystal* m_crystalDataPtr = nullptr;
		/// <summary>
		/// �`�悷�邩�ǂ���
		/// </summary>
		bool m_isDraw = false;
	public:
		/// <summary>
		/// �N���X�^���̃f�[�^��ݒ�
		/// </summary>
		/// <param name="crystalData"></param>
		void SetCrystalData(Crystal crystalData)
		{
			//�N���X�^���̃A�h���X����
			//m_crystalDataPtr = &crystalData;
		}
		/// <summary>
		/// �N���X�^���̃f�[�^���擾
		/// </summary>
		/// <returns></returns>
		Crystal* GetCrystalData()
		{
			return m_crystalDataPtr;
		}
		/// <summary>
		/// �`�悷�邩�ǂ���
		/// </summary>
		/// <param name="is"></param>
		void SetIsDraw(const bool is)
		{
			m_isDraw = is;
		}
		/// <summary>
		/// �`�悷�邩�ǂ������擾
		/// </summary>
		/// <returns></returns>
		const bool GetIsDraw() const
		{
			return m_isDraw;
		}
	};
	/// <summary>
	/// �C���t�H���[�V�����̃f�[�^�̐�
	/// </summary>
	InfomationData m_infoDatas[MAX_CRYSTAL_NUM];
	/// <summary>
	/// �X�L�����t���O
	/// </summary>
	bool m_scanFlag = false;
	/// <summary>
	/// �X�L�����J�n
	/// </summary>
	void ScanStart()
	{
		//�X�L�����t���O��true�ɂ���
		m_scanFlag = true;
		//�X�L�����X�e�[�g���A���t�@�l�C�[�W���O�ɕύX����
		m_scanState = ScanState::en_scanLineEasing;
		//�C�[�W���O����������������
		//�A���t�@�l�C�[�W���O
		m_swapEasing = true;
		m_scanLineData.m_paramA = 0.3;
		m_alphaRatio = 0.0f;
		//���C�v�C�[�W���O
		m_scanLineData.m_wipeSize = 0.0f;
		m_wipeRatio = 0.0f;
	}
	/// <summary>
	/// �X�L�����I��
	/// </summary>
	void ScanEnd()
	{
		m_scanFlag = false;
	}
	/// <summary>
	/// flaot�p���`���
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}
	/// <summary>
	/// �N���X�^���̋��ʃf�[�^�z���_�[
	/// </summary>
	std::shared_ptr<CrystalDataHolder> m_crystalDataHolder;

	//�����ԏ���
	EnemyAIConBase* m_waitTime2s = nullptr;

	EnemyAIConBase* m_waitTime5s = nullptr;
};

