#pragma once
#include "PlayerUIBase.h"

class PlayerOxygenUi : public PlayerUIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerOxygenUi() {}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerOxygenUi(){}
	/// <summary>
	/// �O������^�C�}�[�̃|�C���^���i�[����֐�
	/// </summary>
	/// <param name="timerPtr"></param>
	void InitTimerPtr(float* timerPtr)
	{
		m_gameTimer = timerPtr;
	}
private:
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �Q�[���^�C�}�[
	/// </summary>
	float* m_gameTimer = nullptr;
	/// <summary>
	/// �^�C�}�[
	/// </summary>
	float m_mainTimer = 0.0f;
};

