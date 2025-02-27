#pragma once
#include "sound/SoundSource.h"

//�萔��
namespace {
	static const int MAX_SOUNDLIST_NUM = 30;
}

class GameSound : public IGameObject
{
public:
	/// <summary>
	/// �T�E���h���X�g
	/// </summary>
	enum SoundListNum
	{
		//�΂��@�鉹
		en_rockDigSound,
		//�΂��󂷉�
		en_breakDigSound,
		//���艹�P
		en_decisionSound,
		//�S�ɒe����鉹
		en_hitByIronSound,
		//�G�l�~�[�E�H���A�[���s��
		en_enemyWarriorWalkSound,
		//�G�l�~�[�E�H���A�[���K
		en_enemyWarriorRoar,
		//�L���T�E���h
		en_killSound,
		//�G�l�~�[�E�H���A�[���s��
		en_playerWalkSound,
		//�t�H���g��ł�
		en_fontIn,
		//�V���E�B�����ĉ�
		en_syuwin,
		//�ǐ�BGM
		en_chaseBGM,
		//�^�C�g��BGM
		en_TitleBgm,
		//�T�E���h��
		SoundListMaxNum,
		//�ݒ�Ȃ�
		Non
	};
	enum SoundPriority
	{
		//�D��x���
		en_priority_high = 1,
		//�D��x���
		en_priority_middle = 2,
		//�D��x�O��
		en_priority_low = 3,
		//�ݒ�Ȃ�
		en_priority_non = 4,
	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameSound(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameSound(){}
	/// <summary>
	/// �T�E���h���w�肵�Ė炷
	/// </summary>
	void LocalSoundOrder(
		const SoundListNum& listNum,
		const bool& loop,
		const float& volume);
	void LocalSoundOrder(
		const SoundListNum& listNum,
		const bool& loop,
		const float& volume,
		const Vector3& soundPos);

	SoundSource& ReturnPointerLocalSoundOrder(
		const SoundListNum& listNum,
		const float& volume);

	const SoundSource& PointerSoundOrder(const SoundListNum& listNum);
	const SoundSource& SoundListInit(
		const SoundListNum& listNum, 
		const SoundPriority& priority,
		const float& volume
		);
private:
	struct SoundListData
	{
	private:
		/// <summary>
		/// �T�E���h�̃f�[�^
		/// </summary>
		SoundSource* m_soundData = nullptr;
		/// <summary>
		/// �Đ��ԍ�
		/// </summary>
		SoundListNum m_soundListNum = SoundListNum::Non;
		/// <summary>
		/// �D��x
		/// </summary>
		SoundPriority m_soundPriority = SoundPriority::en_priority_non;
		/// <summary>
		/// ����
		/// </summary>
		float m_volume = 0.0f;
		/// <summary>
		/// ���̃T�E���h���X�g���g�p�����ǂ���
		/// </summary>
		bool m_use = false;
	public:
		void SetSoundInit(const SoundListNum& soundListNum)
		{
			m_soundListNum = soundListNum;

			m_soundData = NewGO<SoundSource>(0);

			m_soundData->Init(m_soundListNum);
		}
		const SoundSource& GetSoundPtr() const
		{
			return *m_soundData;
		}
		void SetSoundPriority(const SoundPriority& soundPriority)
		{
			m_soundPriority = soundPriority;
		}
		const int& GetSoundPriority() const
		{
			return m_soundPriority;
		}
		void SetVolume(const float& volume)
		{
			m_volume = volume;
		}
		void PlayListSound()
		{
			m_soundData->SetVolume(m_volume);

			m_soundData->Play(false);
		}
		void SetSoundUse(const bool& use)
		{
			m_use = use;
		}
		const bool& IsListUse() const
		{
			return m_use;
		}
		void SoundDataReset()
		{
			m_soundData = nullptr;

			m_soundListNum = SoundListNum::Non;

			m_soundPriority = SoundPriority::en_priority_non;

			m_volume = 0.0f;

			m_use = false;
		}
	};
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
	/// �T�E���h���X�g���Đ�����
	/// </summary>
	void PlayListSound();
	/// <summary>
	/// �D�揇�ʔ�r
	/// </summary>
	bool compareByValueDesc(
		const SoundListData& a,
		const SoundListData& b);
	/// <summary>
	/// �T�E���h���X�g������������
	/// </summary>
	void SoundListReset();
	/// <summary>
	/// ���Đ����X�g
	/// </summary>
	SoundListData m_playSoundList[MAX_SOUNDLIST_NUM];
};

