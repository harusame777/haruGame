#include "stdafx.h"
#include "Locker.h"

bool Locker::Start()
{
	m_mainModel.Init("Assets/modelData/objects/locker/locker.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_usuallyShader);

	m_mainModel.SetPosition(m_position);

	return true;
}

void Locker::Update()
{

	m_mainModel.Update();

}

void Locker::Render(RenderContext& rc)
{
	m_mainModel.Draw(rc);
}