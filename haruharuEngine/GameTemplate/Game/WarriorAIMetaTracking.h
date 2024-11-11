#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"

class EnemyBase;

class WarriorAIMetaTracking : public EnemyAIMetaBase 
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WarriorAIMetaTracking(std::shared_ptr<WarriorDataHolder> data)
	{
		m_sharedWarriorDatas = data;
	};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WarriorAIMetaTracking() {};
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
	/// <summary>
	/// �E�H���A�[�ɌĂт������s��
	/// </summary>
	void CallWarrior();
	/// <summary>
	/// �G�l�~�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
	/// </summary>
	void ChangeTrackingState();
	/// <summary>
	/// �Ăяo�����G�l�~�[
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;
protected:
	/// <summary>
	/// ���ʂ��Ă���E�H���A�[�̃f�[�^
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
};

