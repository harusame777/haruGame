#include "stdafx.h"
#include "GameSound.h"

//�X�^�[�g�֐�
bool GameSound::Start()
{
	g_soundEngine->ResistWaveFileBank(SoundListNum::en_rockDigSound,
		"Assets/sound/rockDigSound.wav");

	return true;
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

//�|�C���^�T�E���h���N�G�X�g
const SoundSource& GameSound::PointerSoundOrder(const SoundListNum& listNum)
{

	//�T�E���h���쐬
	SoundSource* orderSound = NewGO<SoundSource>(0);

	orderSound->Init(listNum);

	return *orderSound;

}