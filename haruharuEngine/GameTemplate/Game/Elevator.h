#pragma once
#include "BootObjectBase.h"

class Game;

class Elevator : public BootObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Elevator(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Elevator(){}
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
};

