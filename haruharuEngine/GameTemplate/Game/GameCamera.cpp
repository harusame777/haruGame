#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

//定数等
namespace {
	static const float FPSInitToCameraPos_Y = 55.0f;
	static const float FPSInitToCameraPos_Z = -250.0f;
	static const float TPSInitToCameraPos_Y = 125.0f;
	static const float TPSInitToCameraPos_Z = -450.0f;

	static const float CameraRotSpeed = 3.0f;
}

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
	m_toCameraPos.Set(0.0f, FPSInitToCameraPos_Y, FPSInitToCameraPos_Z);

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
#ifdef _DEBUG
	//カメラのモード切替の処理
	CamFPSorTPS();
	//TPSカメラの処理
	TPSCam();
#endif // DEBUG_MODE
	//FPSカメラの処理
	NewFPSCam();
}

//FPSカメラの関数
void GameCamera::FPSCam()
{
#ifdef _DEBUG 
	if (m_camMode != en_camModeFPS)
	{
		return;
	}
#endif // DEBUG_MODE 

	//注視点を計算
	Vector3 target = m_player->GetPosition();

	target.y += 55.0f;
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
	qRot.SetRotationDeg(Vector3::AxisY, CameraRotSpeed * PadX);
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
		qRot.SetRotationDeg(axisX, -CameraRotSpeed * PadY);
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

void GameCamera::NewFPSCam()
{

	//視点を作成
	Vector3 newCamPos = m_player->GetPosition();

	newCamPos.y += 55.0f;
	newCamPos.z -= 0.01f;

	//古いカメラの注視点を取得
	Vector3 oldCamPos = m_toCameraPos;

	//パッドの入力を取得
	//パッドのX軸
	float PadX = g_pad[0]->GetRStickXF();
	//パッドのY軸
	float PadY = g_pad[0]->GetRStickYF();

	//パッドYの入力がなければ
	if (PadY == 0.0f)
	{
		//速度をリセット
		m_velocityY = 0.0f;
	}

	//パッドXの入力がなければ
	if (PadX == 0.0f)
	{
		//速度をリセット
		m_velocityX = 0.0f;
	}

	//Y軸回りの回転
	
	//横方向の回転軸を作成
	//m_camRotation.SetRotationDeg(
	//	Vector3::AxisY,
	//	SmoothDamp(
	//		m_camRotation.y
	//		,m_camRotation.y + PadX * 3.0f,
	//		m_velocityX,
	//		1.0f));

	Quaternion rotX;
	Quaternion rotY;

	m_oldFramePadX = Leap(PadX, m_oldFramePadX, 0.5f);

	rotX.SetRotationDeg(Vector3::AxisY, 3.0f * m_oldFramePadX);

	//横方向の回転軸に注視点から視点までのベクトルを加算
	rotX.Apply(m_toCameraPos);

	//X軸回りの回転s
	Vector3 axisX;
	//パッドの入力があれば
	if (PadY != 0.0f)
	{
		//Y軸と注視点から視点までのベクトルの外積を計算
		axisX.Cross(Vector3::AxisY, m_toCameraPos);
		//正規化
		axisX.Normalize();
		//縦方向の回転軸を作成
		//m_camRotation.SetRotationDeg(axisX, SmoothDamp(
		//	m_camRotation.x,
		//	m_camRotation.x - PadY * 3.0f,
		//	m_velocityY,
		//	1.0f));

		m_oldFramePadY = Leap(-PadY, m_oldFramePadY, 0.5f);

		rotY.SetRotationDeg(axisX, 3.0f * m_oldFramePadY);
	}
	//縦方向の回転軸に注視点から視点までのベクトルを加算
	rotY.Apply(m_toCameraPos);

	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	if (toPosDir.y < -0.7f) {
		//カメラが上向きすぎ。
		m_toCameraPos = oldCamPos;
	}
	else if (toPosDir.y > 0.7f) {
		//カメラが下向きすぎ。
		m_toCameraPos = oldCamPos;
	}

	//注視点を計算する。
	Vector3 targetPos = newCamPos + m_toCameraPos;

	//視点を更新
	g_camera3D->SetTarget(targetPos);
	g_camera3D->SetPosition(newCamPos);
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
	g_camera3D->Update();
}

//TPSカメラの処理
void GameCamera::TPSCam()
{
	if (m_camMode != en_camModeTPS)
	{
		return;
	}

	//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_player->GetPosition();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 250.0f;
	target += g_camera3D->GetForward() * 20.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.5f * x);
	qRot.Apply(m_toCameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.5f * y);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.95f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
	g_camera3D->Update();
}

//デバッグ時のカメラのモード切替の関数
void GameCamera::CamFPSorTPS()
{
	if (g_pad[0]->IsTrigger(enButtonLB1))
	{
		if (m_camMode == en_camModeFPS)
		{
			m_camMode = en_camModeTPS;

			//注視点から視点までのベクトルを設定
			m_toCameraPos.Set(0.0f, TPSInitToCameraPos_Y, TPSInitToCameraPos_Z);
		}
		else if(m_camMode == en_camModeTPS)
		{
			m_camMode = en_camModeFPS;

			//注視点から視点までのベクトルを設定
			m_toCameraPos.Set(0.0f, FPSInitToCameraPos_Y, FPSInitToCameraPos_Z);
		}
	}
}

void GameCamera::SetCameraTarget(const Vector3& position)
{
	Vector3 cameraToPosVec = g_camera3D->GetPosition() - position;
	
	cameraToPosVec.Normalize();
	cameraToPosVec.y = 0.0f;

	float radian = atan2(cameraToPosVec.x, cameraToPosVec.z);

	float degree = radian * (180.0f / Math::PI);

	Quaternion rotX;

	rotX.SetRotationDeg(Vector3::AxisY, degree);

	m_toCameraPos.Set(
		0.0f,
		position.y,
		FPSInitToCameraPos_Z
	);

	rotX.Apply(m_toCameraPos);

	//注視点を計算する。
	Vector3 targetPos = g_camera3D->GetPosition() + m_toCameraPos;

	//視点を更新
	g_camera3D->SetTarget(targetPos);
}