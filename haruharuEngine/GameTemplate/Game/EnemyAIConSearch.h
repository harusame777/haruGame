#pragma once
#include "EnemyAIConBase.h"

class Player;
class EnemyBase;

class EnemyAIConSearch : public EnemyAIConBase
{
public:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	void Start() override;
	/// <summary>
	/// �������s
	/// </summary>
	/// <returns></returns>
	bool Execution() override;
private:
	/// <summary>
	/// ���C�ŃG�l�~�[�ƃv���C���[�̊Ԃɕǂ��������𒲂ׂ�֐�
	/// </summary>
	bool RayTestWall();
	/// <summary>
	/// �v���C���[�C���X�^���X
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �R���C�_�[
	/// </summary>
	SphereCollider m_sphereCollider;						

};

