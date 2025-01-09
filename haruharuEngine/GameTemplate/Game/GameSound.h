#pragma once
#include "sound/SoundSource.h"

class GameSound : public IGameObject
{
public:
	enum SoundListNum
	{
		//石を掘る音
		en_rockDigSound,
		//決定音１
		en_decisionSound,
		//鉄に弾かれる音
		en_hitByIronSound,
		//エネミーウォリアー走行音
		en_enemyWarriorWalkSound,
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
	void LocalSoundOrder(const SoundListNum& listNum,
		const bool& loop,
		const float& volume,
		const Vector3& soundPos);
	const SoundSource& PointerSoundOrder(const SoundListNum& listNum);
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
};

