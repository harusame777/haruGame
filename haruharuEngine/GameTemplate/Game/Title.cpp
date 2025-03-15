#include "stdafx.h"
#include "Title.h"
#include "Load.h"
#include "GameSound.h"

namespace {
	static const float BACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float BACKSIDE_SPRITE_H_SIZE = 900.0f;

	static const Vector3 MAIN_FONT_POSITION = { -100.0f,-100.0f,0.0f };
	static const Vector3 SUB_FONT_POSITION = { -50.0f,-150.0f,0.0f };
	static const Vector3 TITLE_POSITION = { -400.0f,200.0f,0.0f };

	static const Vector4 FONT_COLOR = { 1.0f,1.0f,1.0f,1.0f };

}

//スタート関数
bool Title::Start()
{
	m_backSideSprite.Init("Assets/modelData/title/back_side_1.DDS",
		BACKSIDE_SPRITE_W_SIZE,
		BACKSIDE_SPRITE_H_SIZE);

	m_gameMenu = NewGO<GameMenu>(2, "titleGameMenu");

	m_gameSetting = NewGO<GameSetting>(2, "titleGameSetting");

	m_gameMenu->InitMenuDatas(
		L"Game Start",
		[&]() -> bool
		{
			GameStart();

			return true;
		}
	);

	m_gameMenu->InitMenuDatas(
		L"Setting",
		[&]() -> bool 
		{
			m_gameSetting->GoSettingMenuOpen();

			return true;
		}
	);

	m_gameSetting->InitMenuEndFunc(
		[&]() -> bool
		{

			m_gameMenu->GoMenuOpen();
			
			return true;
		}
	);

	m_gameSetting->InitSetting(
		L"Test1",
		test1,
		100,
		0,
		[&]() -> bool
		{
			

			return true;
		}
	);

	m_gameSetting->InitSetting(
		L"Test2",
		test2,
		1.0f,
		0.0f,
		[&]() -> bool
		{
			m_gameSound->LocalSoundOrder(GameSound::en_decisionSound, false, 0.5f);

			return true;
		}
	);

	//ロード画面のインスタンスを取得
	m_load = FindGO<Load>("load");

	m_gameSound = FindGO<GameSound>("gameSound");

	return true;
}

//アップデート関数
void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		if (m_isGameIn == true)
			return;

		if (m_gameMenu->IsMenuOpenNow() == true)
			return;

		if (m_gameSetting->IsSettingOpenNow() == true)
			return;
		

		m_gameSound->LocalSoundOrder(GameSound::en_decisionSound, false, 0.5f);

		m_gameMenu->GoMenuOpen();
	}

	//フォントのアップデート
	FontUpdate();
	//背景アップデート
	m_backSideSprite.Update();
}

void Title::FontUpdate()
{
	//メインフォント
	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"Ready?");

	m_mainFont.SetColor(FONT_COLOR);

	m_mainFont.SetPivot({ 0.5f,0.5f });

	m_mainFont.SetPosition(MAIN_FONT_POSITION);

	m_mainFont.SetText(wcsbuf);
	//サブフォント
	swprintf_s(wcsbuf, 256, L"push B");

	m_subFont.SetColor(FONT_COLOR);

	m_subFont.SetPivot({ 0.5f,0.5f });

	m_subFont.SetPosition(SUB_FONT_POSITION);

	m_subFont.SetScale(0.5f);

	m_subFont.SetText(wcsbuf);
	//タイトル
	swprintf_s(wcsbuf, 256, L"SALVAGE");

	m_title.SetColor(FONT_COLOR);

	m_title.SetPivot({ 0.5f,0.5f });

	m_title.SetPosition(TITLE_POSITION);

	m_title.SetScale(3.0f);

	m_title.SetText(wcsbuf);
}

void Title::Render(RenderContext& rc)
{
	m_backSideSprite.Draw(rc);

	m_mainFont.Draw(rc);

	m_subFont.Draw(rc);

	m_title.Draw(rc);
}