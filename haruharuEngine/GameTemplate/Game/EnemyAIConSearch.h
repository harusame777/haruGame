#pragma once
#include "EnemyAIConBase.h"

class Player;
class EnemyBase;

class EnemyAIConSearch : public EnemyAIConBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyAIConSearch(const float setViewingAngle,const float setSearchRad)
	{
		m_viewingAngle = setViewingAngle;
		m_enemySearchRad = setSearchRad;
	}
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
	/// ����p
	/// </summary>
	/// <returns></returns>
	bool AngleCheck();
	/// <summary>
	/// ����p
	/// </summary>
	float m_viewingAngle = 0.0f;
	/// <summary>
	/// ���G�͈�
	/// </summary>
	float m_enemySearchRad = 500.0f;
	/// <summary>
	/// �v���C���[�C���X�^���X
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �R���C�_�[
	/// </summary>
	SphereCollider m_sphereCollider;
};

