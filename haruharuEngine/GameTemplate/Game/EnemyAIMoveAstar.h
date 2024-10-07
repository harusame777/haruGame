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
	/// �X�^�[�g�֐�
	/// </summary>
	void Start() override;
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update() override;
private:
	/// <summary>
	/// �i�r���b�V���t�@�C��
	/// </summary>
	TknFile m_tknFile;
	/// <summary>
	/// �i�r���b�V���̃��C���v��
	/// </summary>
	nsAI::NaviMesh m_nvmMesh;
	/// <summary>
	/// �i�r���b�V���̃p�X�v��
	/// </summary>
	nsAI::Path m_path;
	/// <summary>
	/// �i�r���b�V���̒T���v��
	/// </summary>
	nsAI::PathFinding m_pathFiding;
};

