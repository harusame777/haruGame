#include "stdafx.h"
#include "GameSound.h"

//定数等
namespace{
	static const int MAX_SOUND_PLAY_VALUE = 3;
}

//スタート関数
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

	// ソート処理
	std::sort(std::begin(m_playSoundList), std::end(m_playSoundList),
		[](const SoundListData& a, const SoundListData& b) {
			return a.GetSoundPriority() < b.GetSoundPriority(); // 昇順ソート
		});

	//再生
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

//ポインタサウンドリクエスト
const SoundSource& GameSound::PointerSoundOrder(const SoundListNum& listNum)
{

	//サウンドを作成
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	return *orderSound;

}