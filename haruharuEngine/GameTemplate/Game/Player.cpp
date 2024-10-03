#include "stdafx.h"
#include "Player.h"

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

}