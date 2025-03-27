#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "EnemyBase.h"

class GameSound;

class WarriorAIMetaChaseBGM : public EnemyAIMetaBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WarriorAIMetaChaseBGM(std::shared_ptr<WarriorDataHolder> enemyData) 
	{
		m_sharedWarriorDatas = enemyData;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WarriorAIMetaChaseBGM() {};
	/// <summary>
	/// メタAIの初期化関数
	/// </summary>
	void MetaAIInit();
	/// <summary>
	/// メタAIの実行関数
	/// </summary>
	/// <param name="initEnemy"></param>
	void MetaAIExecution(EnemySMBase* initEnemy);
	/// <summary>
	/// 処理終了
	/// </summary>
	const bool ProcessEnd(EnemySMBase* initEnemy);
private:
	/// <summary>
	/// 追跡状態のエネミーを探す
	/// </summary>
	void SearchTrackingStateEnemy();
	/// <summary>
	/// BGM再生関数
	/// </summary>
	void BGMStart();
	/// <summary>
	/// BGM停止関数
	/// </summary>
	void BGMEnd();
	/// <summary>
	/// BGMフェードアウト関数
	/// </summary>
	void BGMFadeOut();
	/// <summary>
	/// 追跡状態のエネミーがいるかどうか
	/// </summary>
	bool m_isTrackingStateEnemy = false;
	/// <summary>
	/// 音楽が再生中かどうか
	/// </summary>
	bool m_isBGMPlayBack = false;
	
	bool m_isBGMFadeOut = false;

	float m_volumeRatio = 0.0f;

	/// <summary>
	/// 共通しているウォリアーのデータ
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
	/// <summary>
	/// ゲームサウンドのインスタンス
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// BGMのインスタンス
	/// </summary>
	SoundSource* m_gameBGM = nullptr;
	/// <summary>
	/// flaot用線形補間
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}
};

