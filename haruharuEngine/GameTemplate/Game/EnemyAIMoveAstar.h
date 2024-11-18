#pragma once
#include "EnemyAIBase.h"
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class EnemyBase;
class WarriorDataHolder;
class Player;
class EnemyAIConBase;

class EnemyAIMoveAstar : public EnemyAIBase 
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAIMoveAstar(std::shared_ptr<WarriorDataHolder> data) 
	{
		m_sharedWarriorDatas = data;
	}
	/// <summary>
	/// スタート関数
	/// </summary>
	void EnemyAIStart() override;
	/// <summary>
	/// アップデート関数
	/// </summary>
	void EnemyAIUpdate() override;
private:
	/// <summary>
	/// 回転地計算
	/// </summary>
	void RotationValueCalc(const Vector3& direction);
	/// <summary>
	/// ナビメッシュファイル
	/// </summary>
	TknFile m_tknFile;
	/// <summary>
	/// ナビメッシュのメインプロ
	/// </summary>
	nsAI::NaviMesh m_nvmMesh;
	/// <summary>
	/// ナビメッシュのパスプロ
	/// </summary>
	nsAI::Path m_path;
	/// <summary>
	/// ナビメッシュの探索プロ
	/// </summary>
	nsAI::PathFinding m_pathFiding;
	/// <summary>
	/// 共通しているウォリアーのデータ
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
	/// <summary>
	/// プレイヤー
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// 
	/// </summary>
	EnemyAIConBase* m_timer;
};

