#pragma once
#include "EnemyAIBase.h"
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class EnemyBase;
class WarriorDataHolder;
class Player;
class EnemySM_Warrior;
class EnemyAIConBase;

class EnemyAIMoveAstar : public EnemyAIBase 
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyAIMoveAstar(std::shared_ptr<WarriorDataHolder> data) 
	{
		m_sharedWarriorDatas = data;
	}
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	void EnemyAIStart() override;
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void EnemyAIUpdate() override;
private:
	/// <summary>
	/// �p�X�T�����s
	/// </summary>
	void PathFidingExecute();
	/// <summary>
	/// �G�[�X�^�[�ړ�
	/// </summary>
	void MoveAstar();
	/// <summary>
	/// �ʏ�ړ�
	/// </summary>
	void MoveUsually();
	/// <summary>
	/// ��]�n�v�Z
	/// </summary>
	void AstarRotationValueCalc(const Vector3& direction);
	void UsuallyRotationValueCalc(const Vector3& direction);
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
	/// <summary>
	/// ���ʂ��Ă���E�H���A�[�̃f�[�^
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
	/// <summary>
	/// �v���C���[
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// 
	/// </summary>
	EnemyAIConBase* m_timer;
	/// <summary>
/// 
/// </summary>
	EnemyAIConBase* m_wallChack;

	EnemySM_Warrior* chaseEnemyPtr = nullptr;

	EnemySM_Warrior* aroundEnemyPtr = nullptr;


};

