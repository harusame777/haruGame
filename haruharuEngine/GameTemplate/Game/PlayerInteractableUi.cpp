#include "stdafx.h"
#include "PlayerInteractableUi.h"

//定数
namespace {
	/// <summary>
	/// フォントのカラー
	/// </summary>
	static const Vector4 FONT_COLOR = { 0.3f,0.3f,1.0f,1.0f };
	static const Vector3 FONT_POSITION = {-110.0f,-150.0f,0.0f};
}

//スタート関数
bool PlayerInteractableUi::Start()
{
	return true;
}

//アップデート関数
void PlayerInteractableUi::Update()
{
	//メインフォント
	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"push B");

	m_interactableFontSprite.SetColor(FONT_COLOR);

	m_interactableFontSprite.SetPivot({ 0.5f,0.5f });

	m_interactableFontSprite.SetPosition(FONT_POSITION);

	m_interactableFontSprite.SetText(wcsbuf);
}

//レンダー関数
void PlayerInteractableUi::Render(RenderContext& rc)
{
	if (m_interactableDarwFlag == true)
	{
		m_interactableFontSprite.Draw(rc);

		m_interactableDarwFlag = false;
	}
}