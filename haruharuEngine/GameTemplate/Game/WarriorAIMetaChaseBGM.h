#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "EnemyBase.h"

class GameSound;

class WarriorAIMetaChaseBGM : public EnemyAIMetaBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WarriorAIMetaChaseBGM(std::shared_ptr<WarriorDataHolder> enemyData) 
	{
		m_sharedWarriorDatas = enemyData;
	};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WarriorAIMetaChaseBGM() {};
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
	const bool ProcessEnd(EnemySMBase* initEnemy);
private:
	/// <summary>
	/// �ǐՏ�Ԃ̃G�l�~�[��T��
	/// </summary>
	void SearchTrackingStateEnemy();
	/// <summary>
	/// BGM�Đ��֐�
	/// </summary>
	void BGMStart();
	/// <summary>
	/// BGM��~�֐�
	/// </summary>
	void BGMEnd();
	/// <summary>
	/// BGM�t�F�[�h�A�E�g�֐�
	/// </summary>
	void BGMFadeOut();
	/// <summary>
	/// �ǐՏ�Ԃ̃G�l�~�[�����邩�ǂ���
	/// </summary>
	bool m_isTrackingStateEnemy = false;
	/// <summary>
	/// ���y���Đ������ǂ���
	/// </summary>
	bool m_isBGMPlayBack = false;
	
	bool m_isBGMFadeOut = false;

	float m_volumeRatio = 0.0f;

	/// <summary>
	/// ���ʂ��Ă���E�H���A�[�̃f�[�^
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
	/// <summary>
	/// �Q�[���T�E���h�̃C���X�^���X
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// BGM�̃C���X�^���X
	/// </summary>
	SoundSource* m_gameBGM = nullptr;
	/// <summary>
	/// flaot�p���`���
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}
};

