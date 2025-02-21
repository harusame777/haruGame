#include "stdafx.h"
#include "GameSound.h"

//�萔��
namespace{
	static const int MAX_SOUND_PLAY_VALUE = 3;
}

//�X�^�[�g�֐�
bool GameSound::Start()
{
	g_soundEngine->ResistWaveFileBank(SoundListNum::en_rockDigSound,
		"Assets/sound/rockDigSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_breakDigSound,
		"Assets/sound/breakDigSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_decisionSound,
		"Assets/sound/decisionSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_hitByIronSound,
		"Assets/sound/hitByIronSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_enemyWarriorWalkSound,
		"Assets/sound/enemyWarriorWalkSound_2.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_killSound,
		"Assets/sound/killSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_playerWalkSound,
		"Assets/sound/playerWalkSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_fontIn,
		"Assets/sound/fontIn.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_syuwin,
		"Assets/sound/syuwinSound.wav");

	return true;
}

void GameSound::Update()
{

	PlayListSound();

	SoundListReset();

}

void GameSound::PlayListSound()
{

	if (m_playSoundList[0].IsListUse() == false)
	{
		return;
	}

	// �\�[�g����
	std::sort(std::begin(m_playSoundList), std::end(m_playSoundList),
		[](const SoundListData& a, const SoundListData& b) {
			return a.GetSoundPriority() < b.GetSoundPriority(); // �����\�[�g
		});

	//�Đ�
	for (int listNo = 0;
		listNo < MAX_SOUND_PLAY_VALUE;
		listNo++)
	{
		
		m_playSoundList[listNo].PlayListSound();

	}

}

bool GameSound::compareByValueDesc(
	const SoundListData& a,
	const SoundListData& b)
{
	return a.GetSoundPriority() < b.GetSoundPriority();
}

void GameSound::SoundListReset()
{

	for (int listNo = 0;
		listNo < MAX_SOUNDLIST_NUM; 
		listNo++)
	{
		m_playSoundList[listNo].SoundDataReset();
	}

}

//���[�J���T�E���h���N�G�X�g
void GameSound::LocalSoundOrder(const SoundListNum& listNum,
	const bool& loop,
	const float& volume)
{

	//�T�E���h���쐬
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	orderSound->SetVolume(volume);

	orderSound->Play(loop);

}

//���[�J���T�E���h���N�G�X�g
void GameSound::LocalSoundOrder(const SoundListNum& listNum,
	const bool& loop,
	const float& volume,
	const Vector3& soundPos)
{

	//�T�E���h���쐬
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	orderSound->SetPosition(soundPos);

	orderSound->SetVolume(volume);

	orderSound->Play(loop);

}

const SoundSource& GameSound::SoundListInit(
	const SoundListNum& listNum,
	const SoundPriority& priority,
	const float& volume
)
{

	SoundListData* initData = nullptr;

	for (int listNo = 0;
		listNo < MAX_SOUNDLIST_NUM;
		listNo++)
	{
		if (m_playSoundList[listNo].IsListUse() == false)
		{

			initData = &m_playSoundList[listNo];

			break;

		}
	}

	initData->SetSoundInit(listNum);

	initData->SetSoundPriority(priority);

	initData->SetVolume(volume);

	initData->SetSoundUse(true);

	return initData->GetSoundPtr();
}

//�|�C���^�T�E���h���N�G�X�g
const SoundSource& GameSound::PointerSoundOrder(const SoundListNum& listNum)
{

	//�T�E���h���쐬
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	return *orderSound;

}