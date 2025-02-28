#include "stdafx.h"
#include "GameMenu.h"
#include "GameWindow.h"
#include "GameSound.h"

bool GameMenu::Start()
{
	m_gameWindow = NewGO<GameWindow>(1,"menuGameWindow");

	m_gameSound = FindGO<GameSound>("gameSound");

	return true;
}

void GameMenu::Update()
{

	MenuStateUpdate();

}

void GameMenu::MenuStateUpdate()
{

	switch (m_gameMenuState)
	{
	case GameMenu::en_standby:

		//‘Ò‹@

		break;
	case GameMenu::en_windowOpen:

		if (m_gameWindow->IsWindowClose() == true)
		{
			m_gameWindow->WindowOpen();
		}

		if (m_gameWindow->IsWindowOpen() == true)
		{

		}

		break;
	default:
		break;
	}

}

void GameMenu::Render(RenderContext& rc)
{

}