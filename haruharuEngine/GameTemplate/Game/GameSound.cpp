#include "stdafx.h"
#include "GameSound.h"

//スタート関数
bool GameSound::Start()
{
	g_soundEngine->ResistWaveFileBank(SoundListNum::en_rockDigSound,
		"Assets/sound/rockDigSound.wav");

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

//ポインタサウンドリクエスト
const SoundSource& GameSound::PointerSoundOrder(const SoundListNum& listNum)
{

	//サウンドを作成
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	return *orderSound;

}