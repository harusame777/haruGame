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
