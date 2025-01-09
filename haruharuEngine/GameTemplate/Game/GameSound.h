#pragma once
#include "sound/SoundSource.h"

class GameSound : public IGameObject
{
public:
	enum SoundListNum
	{
		//石を掘る音
		en_rockDigSound,
		//タイトルBGM
		en_TitleBgm,
		//サウンド数
		SoundListMaxNum,
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameSound(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameSound(){}
	/// <summary>
	/// サウンドを指定して鳴らす
	/// </summary>
	void LocalSoundOrder(const SoundListNum& listNum,
		const bool& loop,
		const float& volume);
	const SoundSource& PointerSoundOrder(const SoundListNum& listNum);
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
};

