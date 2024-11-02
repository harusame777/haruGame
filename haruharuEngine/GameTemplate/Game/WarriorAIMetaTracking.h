#pragma once
#include "EnemyAIMetaBase.h"

class EnemyBase;
class EnemySMBase;

class WarriorAIMetaTracking : public EnemyAIMetaBase 
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WarriorAIMetaTracking(std::shared_ptr<WarriorDataHolder> data) : EnemyAIMetaBase(data) 
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
	EnemySM_Warrior* m_MainCallWarrior = nullptr;

};

