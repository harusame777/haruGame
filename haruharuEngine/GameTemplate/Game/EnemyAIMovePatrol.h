#pragma once
#include "EnemyAIBase.h"


class EnemyAIMovePatrol : public EnemyAIBase
{
public:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	void EnemyAIStart() override;
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void EnemyAIUpdate() override;
private:
	/// <summary>
	/// ���񃋁[�g�̃p�X���擾���邽�߂̃��x�������_�[
	/// </summary>
	LevelRender m_patrolVecPath;
	/// <summary>
	/// ���񃋁[�g�̃��X�g
	/// </summary>
	std::vector<Vector3*> m_patrolPathList;
};

