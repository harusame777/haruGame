#pragma once
#include "stdafx.h"
#include "Player.h"

class PlayerUIBase : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerUIBase() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~PlayerUIBase() {};
protected:
	/// <summary>
	/// �v���C���[�̃|�C���^
	/// </summary>
	Player* m_playerPtr = nullptr;

};

