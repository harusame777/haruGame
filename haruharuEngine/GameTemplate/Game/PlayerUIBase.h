#pragma once
#include "stdafx.h"
#include "Player.h"

class PlayerUIBase : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerUIBase() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~PlayerUIBase() {};
protected:
	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_playerPtr = nullptr;

};

