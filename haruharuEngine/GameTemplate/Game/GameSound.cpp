#include "stdafx.h"
#include "GameSound.h"

//定数等
namespace{
	static const int MAX_SOUND_PLAY_VALUE = 1;
}

//スタート関数
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

	//優先順位
	//std::sort(
	//	m_playSoundList.begin(),
	//	m_playSoundList.end(),
	//	compareByValueDesc);

	//再生
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

//ローカルサウンドリクエスト
void GameSound::LocalSoundOrder(const SoundListNum& listNum,
	const bool& loop,
	const float& volume)
{

	//サウンドを作成
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	orderSound->SetVolume(volume);

	orderSound->Play(loop);

}

//ローカルサウンドリクエスト
void GameSound::LocalSoundOrder(const SoundListNum& listNum,
	const bool& loop,
	const float& volume,
	const Vector3& soundPos)
{

	//サウンドを作成
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

//ポインタサウンドリクエスト
const SoundSource& GameSound::PointerSoundOrder(const SoundListNum& listNum)
{

	//サウンドを作成
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	return *orderSound;

}