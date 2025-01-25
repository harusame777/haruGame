#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "EnemyBase.h"

class Player;
class GameSound;

class WarriorAIMetaFootSteps : public EnemyAIMetaBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WarriorAIMetaFootSteps(std::shared_ptr<WarriorDataHolder> enemyData)
	{
		m_sharedWarriorDatas = enemyData;
	};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WarriorAIMetaFootSteps(){}
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
	const bool ProcessEnd(EnemySMBase* initEnemy);
private:
	/// <summary>
	/// �G�l�~�[�̃X�e�[�g���m�F����
	/// </summary>
	void EnemyStateCheck();
	/// <summary>
	/// �f�[�^�ɐ��l�����
	/// </summary>
	void DatasPriorityInit();
	/// <summary>
	/// �D��x
	/// </summary>
	enum EnemyDistance_Kinds
	{
		//�D��x���
		en_priority_high,
		//�D��x���
		en_priority_middle,
		//�D��x�O��
		en_priority_low,
		//�ݒ�Ȃ�
		en_priority_non = 4,
	};
	/// <summary>
	/// �G�l�~�[�f�[�^
	/// </summary>
	struct EnemyLength_Data
	{
		EnemyBase* m_enemyData = nullptr;

		float m_length = 0.0f;

		EnemyDistance_Kinds m_priority
			= EnemyDistance_Kinds::en_priority_non;

		int m_warriorStateNum = -1;
	};
	/// <summary>
	/// �����v�Z
	/// </summary>
	void LengthCalc();
	/// <summary>
	/// �v���C���[����G�l�~�[�܂ł̋���
	/// </summary>
	float m_playerToEnemyDiffSq = 0.0f;
	/// <summary>
	/// �v���C���[�̃C���X�^���X
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �Q�[���T�E���h�̃C���X�^���X
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// �Ăяo�����G�l�~�[
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;
	/// <summary>
	/// ���ʂ��Ă���E�H���A�[�̃f�[�^
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;

	EnemyLength_Data m_enemyLengthDatas[3];

	int m_enemyNum = 0;

	float m_valumeKinds[3];
};

