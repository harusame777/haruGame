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
	/// ���^AI�����s����֐�
	/// </summary>
	void MetaAIExecution(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// �E�H���A�[�ɌĂт������s��
	/// </summary>
	void CallWarrior();
	/// <summary>
	/// �G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
	/// </summary>
	void ChangeTrackingState();
	/// <summary>
	/// 
	/// </summary>
	const bool SearchCallCompliedWarrior();
private:
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
	/// �Ăт������G�l�~�[
	/// </summary>
	EnemySM_Warrior* m_MainCallWarrior = nullptr;
	/// <summary>
	/// �Ă΂ꂽ�G�l�~�[�P
	/// </summary>
	EnemySM_Warrior* m_subCalledWarriorFirst = nullptr;
	/// <summary>
	/// �Ă΂ꂽ�G�l�~�[�Q
	/// </summary>
	EnemySM_Warrior* m_subCalledWarriorSecond = nullptr;
	/// <summary>
	/// �G�l�~�[�E�H���A�[�̃��X�g
	/// </summary>
	std::vector<MetaAIWarriorData*> m_enemyWarriorList;
};
