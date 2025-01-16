#pragma once
#include "WarriorDataHolder.h"
#include "PatrolRuteDataHolder.h"

class EnemySM_Warrior;
class EnemyBase;
class Player;
class EnemyAIMetaBase;

class DebugEnemyTrackingState;

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
	~EnemyAIMetaWarrior() 
	{
		for (auto& metaAIs : m_AIMetaList)
		{
			metaAIs->DeleteAIMetaProgram();

			delete metaAIs;
		}

		m_AIMetaList.clear();

		m_patrolRuteDataHolder->DelteListData();
	};
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
		/// �ދp
		/// </summary>
		mode_retreat,
		/// <summary>
		/// ��~
		/// </summary>
		mode_stop,
		/// <summary>
		/// ����
		/// </summary>
		mode_footStep,
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
	/// ���X�g�Ƀ��^AI�̃v���O�������i�[����
	/// </summary>
	/// <param name="programData"></param>
	/// <param name="isOneTime"></param>
	void ListInitAIMeta(EnemyAIMetaBase* programData, const bool isOneTime);
	/// <summary>
	/// ���^AI�����s����֐�
	/// </summary>
	void MetaAIExecution(EnemySM_Warrior* enemyPtr,const MetaAIMode setMode);
	/// <summary>
	/// �������I������
	/// </summary>
	void ProcessEnd(const MetaAIMode setMode, EnemySMBase* initEnemy);
	
	std::shared_ptr<WarriorDataHolder> GetEnemyDatas()
	{
		return m_warriorDataHolder;
	}
private:
	/// <summary>
	/// ���^AI�v���O�����̃f�[�^
	/// </summary>
	struct MetaAIData
	{
	private:
		/// <summary>
		/// ��񂫂�̋N�����ǂ���
		/// </summary>
		bool m_isOneTimeOnlyUpdate = false;
		/// <summary>
		/// ���^AI�̃v���O�����f�[�^
		/// </summary>
		EnemyAIMetaBase* m_metaAIProgramData;
	public:
		/// <summary>
		/// ��񂫂肩
		/// </summary>
		/// <param name="is"></param>
		void SetOneTimeOnlyUpdate(const bool is)
		{
			m_isOneTimeOnlyUpdate = is;
		}
		/// <summary>
		/// ��񂫂肩�ǂ���
		/// </summary>
		/// <returns></returns>
		const bool GetOneTimeOnlyUpdate() const
		{
			return m_isOneTimeOnlyUpdate;
		}
		/// <summary>
		/// ���^AI�v���O������ݒ�
		/// </summary>
		/// <param name="initData"></param>
		void SetAIMetaProgram(EnemyAIMetaBase* initData)
		{
			m_metaAIProgramData = initData;
		}
		void DeleteAIMetaProgram()
		{
			delete m_metaAIProgramData;
		}
		/// <summary>
		/// ���^AI�̃v���O�������擾
		/// </summary>
		/// <returns></returns>
		EnemyAIMetaBase* GetAIMetaProgram()
		{
			return m_metaAIProgramData;
		}
	};
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
	std::vector<MetaAIData*> m_AIMetaList;
	/// <summary>
	/// �E�H���A�[�̋��ʃf�[�^�z���_�`
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
	/// <summary>
	/// �X�e�[�g�f�o�b�N
	/// </summary>
	DebugEnemyTrackingState* m_debugWarriorTrackingState = nullptr;
	/// <summary>
	/// ���x�������_�[
	/// </summary>
	LevelRender m_patrolRuteLevelRender;
	/// <summary>
	/// ���񃋁[�g�̋��ʃf�[�^�z���_�[
	/// </summary>
	std::shared_ptr<PatrolRuteDataHolder> m_patrolRuteDataHolder;
};

