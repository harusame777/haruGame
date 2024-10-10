#pragma once
#include "EnemyAIConBase.h"

class EnemyBase;

class EnemyAIConWaitTime : public EnemyAIConBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="setTime"></param>
	EnemyAIConWaitTime(float setTime)
	{
		m_timerMax = setTime;
	}
	/// <summary>
	/// �X�^�[�g�֐��A����������̂ŁA�ʏ�����
	/// �����āA�^�C�}�[�����������Ȃ���΂Ȃ�Ȃ�������������g��
	/// </summary>
	void Start() override;
	/// <summary>
	/// �������s
	/// </summary>
	/// <returns></returns>
	bool Execution() override;
private:
	/// <summary>
	/// �^�C�}�[
	/// </summary>
	float m_timer = 0.0f;
	/// <summary>
	/// �^�C�}�[�ő�l
	/// </summary>
	float m_timerMax = 0.0f;
	/// <summary>
	/// �^�C�}�[�����������邩�ǂ���
	/// </summary>
	bool m_isTimerInit = false;
};

