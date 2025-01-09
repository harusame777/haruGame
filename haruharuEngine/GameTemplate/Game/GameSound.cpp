#include "stdafx.h"
#include "GameSound.h"

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

	return true;
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

//ポインタサウンドリクエスト
const SoundSource& GameSound::PointerSoundOrder(const SoundListNum& listNum)
{

	//サウンドを作成
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	return *orderSound;

}