#include "stdafx.h"
#include "GameSetting.h"
#include "GameWindow.h"

namespace GameSettingConstant {

	

};

bool GameSetting::Start()
{

	//�Q�[���E�B���h�E���쐬
	m_gameWindow = NewGO<GameWindow>(1,"gameSettingWindow");

}

void GameSetting::Update()
{

}

void GameSetting::Render(RenderContext& rc)
{

}
