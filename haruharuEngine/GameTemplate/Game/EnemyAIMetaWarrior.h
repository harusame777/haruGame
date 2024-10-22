#pragma once

class EnemySM_Warrior;

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
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// ���X�g�ɃG�l�~�[���i�[����
	/// </summary>
	/// <param name="enemyPtr"></param>
	void ListInitEnemy(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// �G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
	/// </summary>
	void ChangeTrackingState();
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
};

