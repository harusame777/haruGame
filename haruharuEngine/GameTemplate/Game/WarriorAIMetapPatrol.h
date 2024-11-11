#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "PatrolRuteDataHolder.h"

class EnemyBase;
class Player;

class WarriorAIMetapPatrol : public EnemyAIMetaBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WarriorAIMetapPatrol(std::shared_ptr<WarriorDataHolder> enemyData,
		std::shared_ptr<PatrolRuteDataHolder> patrolData)
	{
		m_sharedWarriorDatas = enemyData;

		m_sharedPatrolRuteDatas = patrolData;

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
	/// �����I��
	/// </summary>
	void ProcessEnd();
private:
	enum SearchMode {

		en_Near,

		en_Far,
	};
	/// <summary>
	/// �E�H���A�[�̋������v�Z����֐�
	/// </summary>
	void WarriorRangeCalc();
	/// <summary>
	/// ���񃋁[�g��T��
	/// </summary>
	/// <param name="mode"></param>
	void SearchRute(const SearchMode mode);
	/// <summary>
	/// ���x�������_�[
	/// </summary>
	LevelRender m_levelRender;
	/// <summary>
	/// �v���C���[�̃C���X�^���X���i�[����ϐ�
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �Ăяo�����G�l�~�[
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;
protected:
	/// <summary>
	/// ���ʂ��Ă���E�H���A�[�̃f�[�^
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
	/// <summary>
	/// ���ʂ��Ă��鏄�񃋁[�g�̃f�[�^
	/// </summary>
	std::shared_ptr<PatrolRuteDataHolder> m_sharedPatrolRuteDatas;

	float m_warriorDistanceList[3];
};

