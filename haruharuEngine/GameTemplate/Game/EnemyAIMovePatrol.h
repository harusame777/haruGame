#pragma once
#include "EnemyAIBase.h"

class EnemyBase;
class WarriorDataHolder;
class Player;

class EnemyAIMovePatrol : public EnemyAIBase
{
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	void EnemyAIStart() override;
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void EnemyAIUpdate() override;
private:
	enum SearchMode {

		en_Near,

		en_Far,
	};
	/// <summary>
	/// �E�H���A�[�̋������v�Z����֐�
	/// </summary>
	void WarriorRangeCalc();
	void SearchRute(const SearchMode mode);
	/// <summary>
	/// ���^AI�̏��񃋁[�g�̃f�[�^
	/// </summary>
	struct MetaAIPatrolRuteData
	{
		/// <summary>
		/// ���̃��[�g���g�p���Ă���E�H���A�[�����݂��邩
		/// </summary>
		bool m_isUse = false;
		/// <summary>
		/// �I���n�_
		/// </summary>
		Vector3 m_patrolPos;
	};
	/// <summary>
	/// ���x�������_�[
	/// </summary>
	LevelRender m_levelRender;
	/// <summary>
	/// �v���C���[�̃C���X�^���X���i�[����ϐ�
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �p�g���[�����[�g�̃��X�g
	/// </summary>
	std::vector<MetaAIPatrolRuteData*> m_patrolRuteList;
};

