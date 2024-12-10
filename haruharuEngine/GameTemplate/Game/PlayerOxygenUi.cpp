#include "stdafx.h"
#include "PlayerOxygenUi.h"

//スタート関数
bool PlayerOxygenUi::Start()
{

}

//アップデート関数
void PlayerOxygenUi::Update()
{
	if (m_gameTimer == nullptr)
	{
		return;
	}

	m_mainTimer = *m_gameTimer;



}

//レンダー関数
void PlayerOxygenUi::Render(RenderContext& rc)
{

}