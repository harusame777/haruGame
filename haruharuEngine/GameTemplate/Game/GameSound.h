#pragma once
#include "sound/SoundSource.h"

class GameSound : public IGameObject
{
public:
	enum SoundListNum
	{
		//�΂��@�鉹
		en_rockDigSound,
		//�^�C�g��BGM
		en_TitleBgm,
		//�T�E���h��
		SoundListMaxNum,
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
	void LocalSoundOrder(const SoundListNum& listNum,
		const bool& loop,
		const float& volume);
	const SoundSource& PointerSoundOrder(const SoundListNum& listNum);
private:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
};

