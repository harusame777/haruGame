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
private:
	enum EnAnimationClip
	{
		en_idle,

		en_OpenLocker,

		en_animationNum
	};

	/// <summary>
	/// アニメーションクリップ
	/// </summary>
	AnimationClip m_animationClip[en_animationNum];

	EnAnimationClip m_animationClipState = EnAnimationClip::en_idle;
};

