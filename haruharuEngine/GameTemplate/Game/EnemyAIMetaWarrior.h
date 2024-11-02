#pragma once
#include "WarriorDataHolder.h"

class EnemySM_Warrior;
class EnemyBase;
class WarriorDataHolder;
class Player;
class EnemyAIMetaBase;

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
		/// <summary>
		/// �������p
		/// </summary>
		mode_init,
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
	/// �������I������
	/// </summary>
	void ProcessEnd();
private:
	/// <summary>
	/// ���^AI�̃��[�h
	/// </summary>
	MetaAIMode m_nowMetaAIMode;
	/// <summary>
	/// �Ăт������G�l�~�[
	/// </summary>
	EnemySM_Warrior* m_MainCallWarrior = nullptr;
	/// <summary>
	/// ���^AI�̃��X�g
	/// </summary>
	std::vector<EnemyAIMetaBase*> m_AIMetaList;
	/// <summary>
	/// �E�H���A�[�̋��ʃf�[�^�z���_�`
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
	/// <summary>
	/// ���ݏ��������ǂ���
	/// </summary>
	bool m_isCurrentlyProcessed = false;
};

