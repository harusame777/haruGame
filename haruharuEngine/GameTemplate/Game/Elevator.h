#pragma once
#include "BootObjectBase.h"

class Game;

class Elevator : public BootObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Elevator(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Elevator(){}
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
};

