#include "stdafx.h"
#include "PlayerPointerUi.h"
#include "Elevator.h"

//定数等
namespace {
	static const float POINTER_SPRITE_W_SIZE = 92.0f;
	static const float POINTER_SPRITE_H_SIZE = 100.0f;

	static const Vector4 FONT_COLOR = { 0.3f,0.3f,1.0f,1.0f };
	static const float FONT_X_POSITION = -200.0f;
}

bool PlayerPointerUi::Start()
{

	m_pointer.Init("Assets/modelData/playerUI/PlayerPointerUi/pointer.DDS",
		POINTER_SPRITE_W_SIZE,
		POINTER_SPRITE_H_SIZE);

	m_elevator = FindGO<Elevator>("elevator");

}

void PlayerPointerUi::Update()
{

	if (m_isPointerDraw == false)
	{
		return;
	}

	PointerPositionUpdate();

	SpriteUpdate();

}

void PlayerPointerUi::SpriteUpdate()
{
	m_spritePosition.y = 400.0f;

	Vector3 fontPos;

	fontPos.y = m_spritePosition.y + 30.0f;

	fontPos.x = m_spritePosition.x + FONT_X_POSITION;

	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"escape point");

	m_font.SetText(wcsbuf);

	m_font.SetPosition(fontPos);

	m_font.SetColor(FONT_COLOR);

	m_pointer.SetPosition(Vector3(m_spritePosition.x,m_spritePosition.y, 0.0f));

	m_pointer.Update();

}

void PlayerPointerUi::PointerPositionUpdate()
{

	Vector3 objectPos = m_elevator->GetPosition();

	//ワールド座標からスクリーン座標を計算。
	//計算結果をm_spritePositionに格納する
	g_camera3D->CalcScreenPositionFromWorldPosition(m_spritePosition, objectPos);

}

bool PlayerPointerUi::IsSpriteInCamera()
{

	Vector3 diff = m_elevator->GetPosition() - g_camera3D->GetPosition();

	//エネミーからプレイヤーに向かうベクトルを正規化
	diff.Normalize();
	//エネミーの正面ベクトルと、敵からプレイヤーに向かうベクトルの
	//内積(cosθ)を求める。
	float cos = g_camera3D->GetForward().Dot(diff);
	if (cos >= 1)
	{
		cos = 1.0f;
	}
	//内積(cosθ)から角度(θ)を求める
	float angle = acosf(cos);
	//角度(θ)が90°(視野角)より小さければ
	if (angle <= (Math::PI / 180.0f) * 90.0f)
	{

		return true;

	}

	return false;

}

void PlayerPointerUi::Render(RenderContext& rc)
{
	if (m_isPointerDraw == true && IsSpriteInCamera())
	{
		m_pointer.Draw(rc);

		m_font.Draw(rc);
	}
}

