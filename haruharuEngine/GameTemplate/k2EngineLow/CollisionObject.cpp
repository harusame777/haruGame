#include "k2EngineLowPreCompile.h"
#include "CollisionObject.h"

namespace nsK2EngineLow {
	//コンストラクタ
	CollisionObject::CollisionObject()
	{

	}

	//デストラクタ
	CollisionObject::~CollisionObject()
	{
		if (g_collisionObjectManager)
		{
			g_collisionObjectManager->RemoveCollisionObject(this);
		}
	}

	//スタート関数
	bool CollisionObject::Start()
	{
		g_collisionObjectManager->AddCollisionObject(this);
		return true;
	}

	//アップデート関数
	void CollisionObject::Update()
	{
		if (m_isEnableAutoDelete == false)
		{
			return;
		}

		if (m_timer > m_timeLimit + 0000.1f)
		{
			DeleteGO(this);
		}
		m_timer += g_gameTime->GetFrameDeltaTime();
	}

	//コンストラクタ
	CollisionObjectManager::CollisionObjectManager()
	{

	}

	//デストラクタ
	CollisionObjectManager::~CollisionObjectManager()
	{
		m_collisionObjectVector.clear();
	}
}
