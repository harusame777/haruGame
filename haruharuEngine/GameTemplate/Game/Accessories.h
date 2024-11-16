#pragma once
#include"ObjectBase.h"

class Accessories : public ObjectBase
{
public:

	Accessories() {};
	~Accessories() {};

	bool Start();

	void Update();

	void Render(RenderContext& rc);

};

