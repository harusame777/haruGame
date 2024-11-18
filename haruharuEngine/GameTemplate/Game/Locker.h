#pragma once
#include "ObjectBase.h"

class Locker : public ObjectBase
{
public:
	Locker() {};
	~Locker() {};

	bool Start();

	void Update();

	void Render(RenderContext& rc);

};

