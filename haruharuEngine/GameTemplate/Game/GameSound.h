#pragma once
#include "sound/SoundSource.h"

//定数等
namespace {
	static const int MAX_SOUNDLIST_NUM = 30;
}

class GameSound : public IGameObject
{
public:
	/// <summary>
	/// サウンドリスト
	/// </summary>
	enum SoundListNum
	{
		//石を掘る音
		en_rockDigSound,
		//石を壊す音
		en_breakDigSound,
		//決定音１
		en_decisionSound,
		//鉄に弾かれる音
		en_hitByIronSound,
		//エネミーウォリアー走行音
		en_enemyWarriorWalkSound,
		//エネミーウォリアー咆哮
		en_enemyWarriorRoar,
		//キルサウンド
		en_killSound,
		//エネミーウォリアー走行音
		en_playerWalkSound,
		//フォントを打つ音
		en_fontIn,
		//シュウィンって音
		en_syuwin,
		//追跡BGM
		en_chaseBGM,
		//タイトルBGM
		en_TitleBgm,
		//サウンド数
		SoundListMaxNum,
		//設定なし
		Non
	};
	enum SoundPriority
	{
		//優先度一番
		en_priority_high = 1,
		//優先度二番
		en_priority_middle = 2,
		//優先度三番
		en_priority_low = 3,
		//設定なし
		en_priority_non = 4,
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
	void LocalSoundOrder(
		const SoundListNum& listNum,
		const bool& loop,
		const float& volume);
	void LocalSoundOrder(
		const SoundListNum& listNum,
		const bool& loop,
		const float& volume,
		const Vector3& soundPos);

	SoundSource& ReturnPointerLocalSoundOrder(
		const SoundListNum& listNum,
		const float& volume);

	const SoundSource& PointerSoundOrder(const SoundListNum& listNum);
	const SoundSource& SoundListInit(
		const SoundListNum& listNum, 
		const SoundPriority& priority,
		const float& volume
		);
private:
	struct SoundListData
	{
	private:
		/// <summary>
		/// サウンドのデータ
		/// </summary>
		SoundSource* m_soundData = nullptr;
		/// <summary>
		/// 再生番号
		/// </summary>
		SoundListNum m_soundListNum = SoundListNum::Non;
		/// <summary>
		/// 優先度
		/// </summary>
		SoundPriority m_soundPriority = SoundPriority::en_priority_non;
		/// <summary>
		/// 音量
		/// </summary>
		float m_volume = 0.0f;
		/// <summary>
		/// このサウンドリストが使用中かどうか
		/// </summary>
		bool m_use = false;
	public:
		void SetSoundInit(const SoundListNum& soundListNum)
		{
			m_soundListNum = soundListNum;

			m_soundData = NewGO<SoundSource>(0);

			m_soundData->Init(m_soundListNum);
		}
		const SoundSource& GetSoundPtr() const
		{
			return *m_soundData;
		}
		void SetSoundPriority(const SoundPriority& soundPriority)
		{
			m_soundPriority = soundPriority;
		}
		const int& GetSoundPriority() const
		{
			return m_soundPriority;
		}
		void SetVolume(const float& volume)
		{
			m_volume = volume;
		}
		void PlayListSound()
		{
			m_soundData->SetVolume(m_volume);

			m_soundData->Play(false);
		}
		void SetSoundUse(const bool& use)
		{
			m_use = use;
		}
		const bool& IsListUse() const
		{
			return m_use;
		}
		void SoundDataReset()
		{
			m_soundData = nullptr;

			m_soundListNum = SoundListNum::Non;

			m_soundPriority = SoundPriority::en_priority_non;

			m_volume = 0.0f;

			m_use = false;
		}
	};
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// サウンドリストを再生する
	/// </summary>
	void PlayListSound();
	/// <summary>
	/// 優先順位比較
	/// </summary>
	bool compareByValueDesc(
		const SoundListData& a,
		const SoundListData& b);
	/// <summary>
	/// サウンドリストを初期化する
	/// </summary>
	void SoundListReset();
	/// <summary>
	/// 音再生リスト
	/// </summary>
	SoundListData m_playSoundList[MAX_SOUNDLIST_NUM];
};

