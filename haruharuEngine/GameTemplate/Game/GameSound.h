#pragma once
#include "sound/SoundSource.h"

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
		//���艹�P
		en_decisionSound,
		//�S�ɒe����鉹
		en_hitByIronSound,
		//�G�l�~�[�E�H���A�[���s��
		en_enemyWarriorWalkSound,
		//�L���T�E���h
		en_killSound,
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
	const SoundSource& PointerSoundOrder(const SoundListNum& listNum);
	void SoundListInit(
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
	public:
		void SetSoundInit(const SoundListNum& soundListNum)
		{
			m_soundData = NewGO<SoundSource>(0);

			m_soundData->Init(soundListNum);
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
			m_soundData->Play(false);
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
	std::vector<SoundListData*> m_playSoundList;
};

