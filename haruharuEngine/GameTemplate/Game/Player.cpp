#include "stdafx.h"
#include "Player.h"
#include "PlayerStaminaUi.h"

//定数等
namespace {
	//歩き時のプレイヤーのスピード
	const static float playerSpeedWalk = 150.0f;
	//走り時のプレイヤーのスピード
	const static float playerSpeedRun = 300.0f;
}

//コンストラクタ
Player::Player()
{

}

//デストラクタ
Player::~Player()
{

}

//スタート関数
bool Player::Start()
{
	//キャラクターコントローラーを初期化
	m_CController.Init(10.0f, 20.0f, m_position);

	//位置の初期設定
	m_CController.SetPosition(m_position);

	m_playerStaminaUi = FindGO<PlayerStaminaUi>("StaminaUI");
	
	m_playerStaminaUi->InitPlayerStaminaPtr(&m_stamina);

	return true;
}

//アップデート関数
void Player::Update()
{
	//移動関数
	Move();
	//正面値を設定
	SetForward(g_camera3D->GetForward());
}

//移動関数
void Player::Move()
{
	//プレイヤーが歩き状態か走り状態化を調べて
	//速度を選択する
	IsWalkOrRun();

	//移動速度を初期化
	m_moveVector.x = 0.0f;
	m_moveVector.z = 0.0f;

	//このフレームの移動量を求める。
	//左スティックの入力量を受け取る。
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//カメラの前方方向と右方向を取得。
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveVector += cameraForward * lStick_y * m_moveSpeed;	//奥方向への移動速度を加算。
	m_moveVector += cameraRight * lStick_x * m_moveSpeed;		//右方向への移動速度を加算。
	//キャラクターコントローラーを使用して、座標を更新。
	m_position = m_CController.Execute(m_moveVector, g_gameTime->GetFrameDeltaTime());
}

//プレイヤーが走り状態か歩き状態化を調べる関数
void Player::IsWalkOrRun()
{
	if (g_pad[0]->IsPress(enButtonRB1) && m_isStaminaOut == false)
	{
		m_moveSpeed = playerSpeedRun;

		m_stamina--;

		if (0 >= m_stamina)
		{
			m_stamina = 0;

			m_isStaminaOut = true;
		}
	}
	else
	{
		m_moveSpeed = playerSpeedWalk;

		m_stamina++;

		if (100 <= m_stamina)
		{
			m_stamina = 100;

			m_isStaminaOut = false;
		}
	}
}