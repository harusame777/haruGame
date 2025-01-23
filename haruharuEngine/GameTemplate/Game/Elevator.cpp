#include "stdafx.h"
#include "Elevator.h"
#include "Game.h"

//íËêîìô
namespace {

	static const Vector3 ELEVATOR_POS = { 0.0f,0.0f,0.0f };

}

bool Elevator::Start()
{
	m_mainModel.Init("Assets/modelData/objects/elevator/elevator.tkm",nullptr,0,enModelUpAxisZ, ModelRender::en_usuallyShader);

	InitBootObject("Assets/modelData/objects/elevator/elevatorBootPos.tkl");

	m_mainModel.SetPosition(ELEVATOR_POS);

	m_mainModel.Update();

	m_game = FindGO<Game>("game");

	return true;
}

void Elevator::Update()
{
	if (IsObjectBootConditions() == true)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_game->PlayerGameClear();
		}
	}

	m_mainModel.Update();
}

void Elevator::Render(RenderContext& rc)
{
	m_mainModel.Draw(rc);
}