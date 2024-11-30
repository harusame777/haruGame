#include "stdafx.h"
#include "Crystal.h"
#include "Player.h"
#include "CrystalGetCommandSprite.h"
#include "ManagerCrystal.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//クリスタルを採取するときにクリスタルにカメラを向けないと採取できないようにしたい
//
//1.クリスタルから、カメラに伸びるベクトルAを作る
//
//2.ベクトルAを正規化する
//
//3.カメラの正面ベクトルを取得する
//
//4.ベクトルAとカメラの正面値の内積を計算して、ベクトルAとカメラの正面ベクトルが
//どれだけ似ているか(相似性)を調べる
//
//5.数値が一定以下だったら採取できるようにする

//定数等
namespace {
	/// <summary>
	/// 取得距離の計算に使うやつ
	/// </summary>
	static const float GET_RANGE_CALC = 90.0f;
	/// <summary>
	/// 修正値１
	/// </summary>
	static const Vector3 CORRE_POSITION = { 0.0f,-60.0f,0.0f };
}

//コンストラクタ
Crystal::Crystal()
{

}

//デストラクタ
Crystal::~Crystal()
{

}

//スタート関数
bool Crystal::Start()
{

	//クリスタル01をモデルに設定
	m_mainModel.Init("Assets/modelData/objects/crystal/crystal01_Model.tkm", nullptr, 0, enModelUpAxisZ, true);

	m_managerCrystalPtr = FindGO<ManagerCrystal>("CrystalMetaAI");

	//シャドウマップに描画するようにする
	m_mainModel.SetShadowChasterFlag(true);

	//座標を設定
	m_mainModel.SetPosition(m_position);
	//回転を設定
	m_mainModel.SetRotation(m_rotation);
	//拡大率を設定
	m_mainModel.SetScale(m_scale);
	//初期設定を確定
	m_mainModel.Update();

	//プレイヤーのインスタンスを取得する
	m_player = FindGO<Player>("player");

	//クリスタルの取得コマンド表示プログラムのインスタンスを取得する
	m_GetCOMSprite = FindGO<CrystalGetCommandSprite>("object");

	//コライダーを初期化する
	m_sphereCollider.Create(1.0f);

	return true;
}

//アップデート関数
void Crystal::Update()
{
	//クリスタル取得処理
	GetCrystal();
	//座標を設定
	m_mainModel.SetPosition(m_position);
	//回転を設定
	m_mainModel.SetRotation(m_rotation);
	//描画更新
	m_mainModel.Update();
}

//レンダー関数
void Crystal::Render(RenderContext& rc)
{
	//取得されていなかったら
	if (!m_isGetObject)
	{
		//描画する
		m_mainModel.Draw(rc);
	}

#ifdef DEBUG_MODE
	m_debugFontRender.Draw(rc);
#endif
}

//クリスタルを取得できるかどうか判定する関数
const bool Crystal::IsLookCrystal()
{
	//カメラの正面ベクトルを取得
	Vector3 camForward = g_camera3D->GetForward();

	//プレイヤーの座標を取得
	Vector3 playerPos = m_player->GetPosition();

	//プレイヤーの座標から自身の座標を引いて
	//自身からプレイヤーへ伸びるベクトルを計算する
	Vector3 diff = playerPos - (m_position + CORRE_POSITION);

	//正規化して単位ベクトルにする
	diff.Normalize();

	//内積を計算し、相似性を測る
	float similarity = Dot(camForward, diff);

	//もし-0.95よりも相似性が小さかったら
	if (similarity <= -0.95)
	{
		//trueを返す
		return true;
	}

	return false;
}

const bool Crystal::IsInGetRange()
{
	//プレイヤーの座標を取得
	Vector3 playerPos = m_player->GetPosition();

	//プレイヤーの座標から自身の座標を引いて
	//自身からプレイヤーへ伸びるベクトルを計算する
	Vector3 diff = playerPos - m_position;

	//自身からプレイヤーへ伸びるベクトルの２乗を計算する
	float range = diff.LengthSq();
	
	//もし取得範囲内だったら
	if (range <= GET_RANGE_CALC * GET_RANGE_CALC)
	{
		//trueを返す
		return true;
	}

	return false;
}

void Crystal::GetCrystal()
{
	if (m_collectCoolTime <= 0.0f)
	{
		m_collectCoolTime = 0.0f;
	}
	else
	{
		m_collectCoolTime -= g_gameTime->GetFrameDeltaTime();
		return;
	}

	if (IsInGetRange() && IsLookCrystal())
	{
#ifdef DEBUG_MODE
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"GetTrue");

		m_debugFontRender.SetText(wcsbuf);
#endif

		//もしBボタンが押されたら
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//採取を開始する
			m_GetCOMSprite->CrystalCollectStart(this);
		}
	}
#ifdef DEBUG_MODE
	else
	{
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"GetFalse");

		m_debugFontRender.SetText(wcsbuf);
	}
#endif 

}

void Crystal::CrystalCollected()
{
	m_isGetObject = true;

	m_managerCrystalPtr->ArrangementDataRefresh(this);
}