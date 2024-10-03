#include "stdafx.h"
#include "Player.h"

//定数等
namespace {
	const static float playerSpeed = 250.0f;
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
	m_CController.Init(25.0f, 75.0f, m_position);

	//位置の初期設定
	m_CController.SetPosition(m_position);

	return true;
}

//アップデート関数
void Player::Update()
{
	//移動関数
	Move();
}

//移動関数
void Player::Move()
{
	//移動速度を初期化
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

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
	m_moveSpeed += cameraForward * lStick_y * playerSpeed;	//奥方向への移動速度を加算。
	m_moveSpeed += cameraRight * lStick_x * playerSpeed;		//右方向への移動速度を加算。
	//キャラクターコントローラーを使用して、座標を更新。
	m_position = m_CController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
}