#pragma once
#include "EnemyAIMetaBase.h"

class EnemyBase;
class Player;

class WarriorAIMetapPatrol : public EnemyAIMetaBase
{
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WarriorAIMetapPatrol(std::shared_ptr<WarriorDataHolder> data) : EnemyAIMetaBase(data)
	{
		m_sharedWarriorDatas = data;
	};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WarriorAIMetapPatrol() {};
	/// <summary>
	/// ���^AI�̏������֐�
	/// </summary>
	void MetaAIInit();
	/// <summary>
	/// ���^AI�̎��s�֐�
	/// </summary>
	/// <param name="initEnemy"></param>
	void MetaAIExecution(EnemySMBase* initEnemy);
	/// <summary>
	/// �E�H���A�[�̋������v�Z����֐�
	/// </summary>
	void WarriorRangeCalc();
private:
	/// <summary>
	/// ���^AI�̏��񃋁[�g�̃f�[�^
	/// </summary>
	struct MetaAIPatrolRuteData
	{
		/// <summary>
		/// ���̃��[�g���g�p���Ă���E�H���A�[�����݂��邩
		/// </summary>
		bool m_isUse = false;
		/// <summary>
		/// �I���n�_
		/// </summary>
		Vector3 m_patrolPos;
	};
	struct DistanceListData
	{
		/// <summary>
		/// ����
		/// </summary>
		float Distance;
		/// <summary>
		/// �E�H���A�[�̃f�[�^
		/// </summary>
		EnemySM_Warrior* m_warriorData;

	};
	/// <summary>
	/// �p�g���[�����[�g�̎��
	/// </summary>
	enum PatrolRuteState
	{
		/// <summary>
		/// �v���C���[�̋߂�
		/// </summary>
		en_playerToNear,
		/// <summary>
		/// �}�b�v�̒[�̕�
		/// </summary>
		en_goToEdge,
	};
	/// <summary>
	/// ���x�������_�[
	/// </summary>
	LevelRender m_levelRender;
	/// <summary>
	/// �v���C���[�̃C���X�^���X���i�[����ϐ�
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �p�g���[�����[�g�̃��X�g
	/// </summary>
	std::vector<MetaAIPatrolRuteData*> m_patrolRuteList;
	/// <summary>
	/// �Ăяo�����G�l�~�[
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;

	float m_warriorDistanceList[3];
};

