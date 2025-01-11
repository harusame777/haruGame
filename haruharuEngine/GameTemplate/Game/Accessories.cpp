#include "stdafx.h"
#include "Accessories.h"

bool Accessories::Start()
{

	m_mainModel.Init("Assets/modelData/objects/accessories/desk/desk.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_usuallyShader);

	m_mainModel.SetPosition(m_position);

	m_mainModel.SetRotation(m_rotation);

	return true;
}

void Accessories::Update()
{

	m_mainModel.Update();

}

void Accessories::Render(RenderContext& rc)
{

	m_mainModel.Draw(rc);

}