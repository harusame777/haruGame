#pragma once
#include "EnemyAIConBase.h"

class Player;
class EnemyBase;

class EnemyAIConColPlayer : public EnemyAIConBase
{
public:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	void InitData() override;
	/// <summary>
	/// �������s
	/// </summary>
	/// <returns></returns>
	bool Execution() override;
private:
	/// <summary>
	/// �v���C���[�̃C���X�^���X���i�[����ϐ�
	/// </summary>
	Player* m_player = nullptr;
};

