#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCamera();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameCamera();
	/// <summary>
	/// カメラのターゲットを設定
	/// </summary>
	void SetCameraTarget(const Vector3& position);
private:
	/// <summary>
	/// デバッグ時のカメラのモード
	/// </summary>
	enum CameraMode {
		//FPS視点
		en_camModeFPS,
		//TPS視点
		en_camModeTPS,
	};
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// FPSカメラの処理
	/// </summary>
	void FPSCam();
	/// <summary>
	/// TPSカメラの処理
	/// </summary>
	void TPSCam();
	/// <summary>
	/// カメラのモード切替をする関数
	/// </summary>
	void CamFPSorTPS();
	/// <summary>
	/// 新しいFPSカメラの処理
	/// </summary>
	void NewFPSCam();
	/// <summary>
	/// カメラの速度
	/// </summary>
	float m_velocityX;
	float m_velocityY;
	/// <summary>
	/// カメラの角度
	/// </summary>
	Quaternion m_camRotation;
	/// <summary>
	/// 
	/// </summary>
	float m_oldFramePadX = 0.0f;
	float m_oldFramePadY = 0.0f;
	/// <summary>
	/// flaot用線形補間
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}
	/// <summary>
	/// 速度可変線形保管
	/// </summary>
	/// <param name="currentValue"></param>
	/// <param name="targetValue"></param>
	/// <param name="velocity"></param>
	/// <param name="smoothTime"></param>
	const float SmoothDamp(
		float currentValue,
		float targetValue,
		float& velocity,
		float smoothTime
	)
	{
		velocity += (targetValue - currentValue) 
			/ smoothTime * g_gameTime->GetFrameDeltaTime();

		currentValue += velocity * g_gameTime->GetFrameDeltaTime();

		return currentValue;
	}
	/// <summary>
	/// 注視点から視点までのベクトル
	/// </summary>
	Vector3 m_toCameraPos;
	/// <summary>
	/// プレイヤーのインスタンスを格納するための変数
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// カメラのモード
	/// </summary>
	CameraMode m_camMode = en_camModeFPS;
};
