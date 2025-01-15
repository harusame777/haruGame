#include "stdafx.h"
#include "GameSound.h"

//�萔��
namespace{
	static const int MAX_SOUND_PLAY_VALUE = 1;
}

//�X�^�[�g�֐�
bool GameSound::Start()
{
	g_soundEngine->ResistWaveFileBank(SoundListNum::en_rockDigSound,
		"Assets/sound/rockDigSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_decisionSound,
		"Assets/sound/decisionSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_hitByIronSound,
		"Assets/sound/hitByIronSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_enemyWarriorWalkSound,
		"Assets/sound/enemyWarriorWalkSound.wav");

	g_soundEngine->ResistWaveFileBank(SoundListNum::en_killSound,
		"Assets/sound/killSound.wav");

	return true;
}

void GameSound::Update()
{

	PlayListSound();

	SoundListReset();

}

void GameSound::PlayListSound()
{

	//�D�揇��
	//std::sort(
	//	m_playSoundList.begin(),
	//	m_playSoundList.end(),
	//	compareByValueDesc);

	//�Đ�
	for (int soundNum = 0;
		soundNum < MAX_SOUND_PLAY_VALUE;
		soundNum++)
	{
		
		//m_playSoundList[soundNum]->PlayListSound();

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

	for (auto& listPtr: m_playSoundList)
	{
		delete(listPtr);
	}

	m_playSoundList.clear();

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

void GameSound::SoundListInit(
	const SoundListNum& listNum,
	const SoundPriority& priority,
	const float& volume
)
{
	SoundListData* newData = new SoundListData;

	newData->SetSoundInit(listNum);

	newData->SetSoundPriority(priority);

	newData->SetVolume(volume);

	m_playSoundList.push_back(newData);
}

//�|�C���^�T�E���h���N�G�X�g
const SoundSource& GameSound::PointerSoundOrder(const SoundListNum& listNum)
{

	//�T�E���h���쐬
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	return *orderSound;

}