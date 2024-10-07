#pragma once
#include "EnemyBase.h"
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class Enemy_Warrior : public EnemyBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Enemy_Warrior();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	~Enemy_Warrior();
private:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �h���[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// AIList�̏�����
	/// </summary>
	void InitAIList();
	/// <summary>
	/// AIList���̃v���O�����̃A�b�v�f�[�g
	/// </summary>
	void AIListUpdate();
private:
	/// <summary>
	/// ���f��
	/// </summary>
	ModelRender m_modelRender;

	//test
	TknFile m_tknFile;
	nsAI::NaviMesh m_nvmMesh;
	nsAI::Path m_path;
	nsAI::PathFinding m_pathFiding;
	Player* m_player = nullptr;


};

