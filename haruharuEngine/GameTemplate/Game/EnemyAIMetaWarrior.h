#pragma once

class EnemySM_Warrior;
class EnemyBase;

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
	/// �X�^�[�g�֐�
	/// </summary>
	bool Start();
	/// <summary>
	/// ���X�g�ɃG�l�~�[���i�[����
	/// </summary>
	/// <param name="enemyPtr"></param>
	void ListInitEnemy(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// �G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
	/// </summary>
	void MetaAIExecution(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// �E�H���A�[�ɌĂт������s��
	/// </summary>
	void CallWarrior(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// ���X�g���̃G�l�~�[���ǐՏ�Ԃ����ׂ�ϐ�
	/// </summary>
	/// <returns></returns>
	const bool SearchEnemyTracking() const;
private:
	/// <summary>
	/// �G�l�~�[�E�H���A�[�̃��X�g
	/// </summary>
	std::vector<EnemySM_Warrior*> m_enemyWarriorList;
	/// <summary>
	/// �Ăт����ɉ������G�l�~�[�̃��X�g
	/// </summary>
	std::list<EnemySM_Warrior*> m_CallRespondWarriorList;
};

