#pragma once
#include "EnemyAIBase.h"

class EnemyBase;
class WarriorDataHolder;
class Player;
class EnemyAIConBase;

class EnemyAIMove : public EnemyAIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyAIMove(){}
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
	/// ��]�l�̌v�Z
	/// </summary>
	void RotationCalc(const Vector3& moveSpeed);
	/// <summary>
	/// �v���C���[
	/// </summary>
	Player* m_player = nullptr;
};

