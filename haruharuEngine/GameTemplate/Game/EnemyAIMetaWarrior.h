#pragma once
#include "WarriorDataHolder.h"

class EnemySM_Warrior;
class EnemyBase;
class Player;

class EnemyAIMetaWarrior : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyAIMetaWarrior() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyAIMetaWarrior() {};
	/// <summary>
	///	���^AI�̂ǂ̃v���O�������N�����邩
	/// </summary>
	enum MetaAIMode
	{
		/// <summary>
		///�ǐՃX�e�[�g�ύX 
		/// </summary>
		mode_trackingStateChange,
		/// <summary>
		/// ���񃋁[�g�ݒ�
		/// </summary>
		mode_patrolRouteSet,
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
	/// �X�^�[�g�֐�
	/// </summary>
	bool Start();
	/// <summary>
	/// ���X�g�ɃG�l�~�[���i�[����
	/// </summary>
	/// <param name="enemyPtr"></param>
	void ListInitEnemy(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// ���^AI�����s����֐�
	/// </summary>
	void MetaAIExecution(EnemySM_Warrior* enemyPtr,const MetaAIMode setMode);
	/// <summary>
	/// �E�H���A�[�ɌĂт������s��
	/// </summary>
	void CallWarrior();
	/// <summary>
	/// �G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
	/// </summary>
	void ChangeTrackingState();
	/// <summary>
	/// �E�H���A�[�̋������v�Z����֐�
	/// </summary>
	void WarriorRangeCalc();
	/// <summary>
	/// �������I������
	/// </summary>
	void ProcessEnd();
private:
	/// <summary>
	/// �v���C���[�̃C���X�^���X���i�[����ϐ�
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// ���^AI�̃��[�h
	/// </summary>
	MetaAIMode m_nowMetaAIMode;
	/// <summary>
	/// ���^AI�ɕۑ�����G�l�~�[�̃f�[�^
	/// </summary>
	struct MetaAIWarriorData
	{
		/// <summary>
		/// true�ł���ΌĂт����ɉ������G�l�~�[
		/// </summary>
		bool m_isCallCompliedWarrior = false;
		/// <summary>
		/// �G�l�~�[�̃|�C���^
		/// </summary>
		EnemySM_Warrior* m_warriorPtr = nullptr;
	};
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
	/// ���x�������_�[
	/// </summary>
	LevelRender m_levelRender;
	/// <summary>
	/// �Ăт������G�l�~�[
	/// </summary>
	EnemySM_Warrior* m_MainCallWarrior = nullptr;
	/// <summary>
	/// �G�l�~�[�E�H���A�[�̃��X�g
	/// </summary>
	std::vector<MetaAIWarriorData*> m_enemyWarriorList;
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
	/// <summary>
	/// �p�g���[�����[�g�̃��X�g
	/// </summary>
	std::vector<MetaAIPatrolRuteData*> m_patrolRuteList;
	/// <summary>
	/// �E�H���A�[�̋������X�g
	/// </summary>
	float m_warriorDistanceList[WARRIOR_NUM];
	/// <summary>
	/// ���ݏ��������ǂ���
	/// </summary>
	bool m_isCurrentlyProcessed = false;
};

