#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

//コンストラクタ
GameCamera::GameCamera()
{
}

//デストラクタ
GameCamera::~GameCamera()
{

}

//スタート関数
bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定
	m_toCameraPos.Set(0.0f, 125.0f, -250.0f);

	//プレイヤーのインスタンスを設定
	m_player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);

	return true;
}

//アップデート関数
void GameCamera::Update()
{
	//注視点を計算
	Vector3 target = m_player->GetPosition();

	target.y += 90.0f;
	target.z -= 0.01f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を取得
	//パッドのX軸
	float PadX = g_pad[0]->GetRStickXF();
	//パッドのY軸
	float PadY = g_pad[0]->GetRStickYF();

	//Y軸回りの回転
	Quaternion qRot;
	//横方向の回転軸を作成
	qRot.SetRotationDeg(Vector3::AxisY, 1.6f * PadX);
	//横方向の回転軸に注視点から視点までのベクトルを加算
	qRot.Apply(m_toCameraPos);

	//X軸回りの回転
	Vector3 axisX;
	//パッドの入力があれば
	if (PadY != 0.0f)
	{
		//Y軸と注視点から視点までのベクトルの外積を計算
		axisX.Cross(Vector3::AxisY, m_toCameraPos);
		//正規化
		axisX.Normalize();
		//縦方向の回転軸を作成
		qRot.SetRotationDeg(axisX, -1.6 * PadY);
	}
	//縦方向の回転軸に注視点から視点までのベクトルを加算
	qRot.Apply(m_toCameraPos);

	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	if (toPosDir.y < -0.7f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.7f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算する
	Vector3 pos = target + m_toCameraPos;
	//視点を更新
	g_camera3D->SetTarget(pos);
	g_camera3D->SetPosition(target);
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
	g_camera3D->Update();
}