#pragma once
#include "EnemyAIBase.h"
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class EnemyBase;

class EnemyAIMoveAstar : public EnemyAIBase
{
public:
	/// <summary>
	/// スタート関数
	/// </summary>
	void Start() override;
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update() override;
private:
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
};

