#include "stdafx.h"
#include "Crystal.h"
#include "Player.h"
#include "CrystalGetCommandSprite.h"
#include "ManagerCrystal.h"
#include "PlayerScoreUi.h"

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
	/// <summary>
	/// デバッグのフォントの位置
	/// </summary>
	static const Vector3 DEBUG_FONT_POSITION = { 0.0f,100.0f,0.0f };
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
	m_crystal_M_Model.Init("Assets/modelData/objects/crystal/crystal01_Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_crystalShader);

	m_crystal_R_Model.Init("Assets/modelData/objects/crystal/crystal01_Model_R.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_crystalShader);

	m_crystal_Y_Model.Init("Assets/modelData/objects/crystal/crystal01_Model_Y.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_crystalShader);

	m_managerCrystalPtr = FindGO<ManagerCrystal>("CrystalMetaAI");

	//シャドウマップに描画するようにする
	m_crystal_M_Model.SetShadowChasterFlag(true);
	m_crystal_R_Model.SetShadowChasterFlag(true);
	m_crystal_Y_Model.SetShadowChasterFlag(true);

	//座標を設定
	m_crystal_M_Model.SetPosition(m_position);
	m_crystal_R_Model.SetPosition(m_position);
	m_crystal_Y_Model.SetPosition(m_position);
	//回転を設定
	m_crystal_M_Model.SetRotation(m_rotation);
	m_crystal_R_Model.SetRotation(m_rotation);
	m_crystal_Y_Model.SetRotation(m_rotation);
	//拡大率を設定
	m_crystal_M_Model.SetScale(m_scale);
	m_crystal_R_Model.SetScale(m_scale);
	m_crystal_Y_Model.SetScale(m_scale);
	//初期設定を確定
	m_crystal_M_Model.Update();
	m_crystal_R_Model.Update();
	m_crystal_Y_Model.Update();

	//プレイヤーのインスタンスを取得する
	m_player = FindGO<Player>("player");

	m_scoreUi = FindGO<PlayerScoreUi>("ScoreUI");

	//クリスタルの取得コマンド表示プログラムのインスタンスを取得する
	m_GetCOMSprite = FindGO<CrystalGetCommandSprite>("comSprite");

	InitBootObject("Assets/modelData/objects/crystal/crystalBootPos.tkl");

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
	m_crystal_M_Model.SetPosition(m_position);
	m_crystal_R_Model.SetPosition(m_position);
	m_crystal_Y_Model.SetPosition(m_position);
	//回転を設定
	m_crystal_M_Model.SetRotation(m_rotation);
	m_crystal_R_Model.SetRotation(m_rotation);
	m_crystal_Y_Model.SetRotation(m_rotation);
	if (m_GetCOMSprite->GetCollectFlag() == false)
	{
		UpdateBootData();
	}
	//描画更新
	m_crystal_M_Model.Update();
	m_crystal_R_Model.Update();
	m_crystal_Y_Model.Update();
}

//レンダー関数
void Crystal::Render(RenderContext& rc)
{
	//取得されていなかったら
	if (!m_isGetObject)
	{
		//描画する
		switch (m_crystalColorState)
		{
		case Crystal::en_crystal_M:

			m_crystal_M_Model.Draw(rc);

			break;
		case Crystal::en_crystal_R:

			m_crystal_R_Model.Draw(rc);

			break;
		case Crystal::en_crystal_Y:

			m_crystal_Y_Model.Draw(rc);

			break;
		default:
			break;
		}
	}

#ifdef _DEBUG
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

	if (m_GetCOMSprite->GetCollectFlag() == true)
	{
		return;
	}

	if (IsObjectBootConditions())
	{
#ifdef _DEBUG
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"GetTrue");

		m_debugFontRender.SetPosition(DEBUG_FONT_POSITION);

		m_debugFontRender.SetText(wcsbuf);
#endif

		//もしBボタンが押されたら
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//採取を開始する
			m_GetCOMSprite->CrystalCollectStart(this);
		}
	}
#ifdef _DEBUG
	else
	{
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"GetFalse");

		m_debugFontRender.SetPosition(DEBUG_FONT_POSITION);

		m_debugFontRender.SetText(wcsbuf);
	}
#endif 

}

void Crystal::CrystalCollected()
{
	m_isGetObject = true;

	switch (m_crystalColorState)
	{
	case Crystal::en_crystal_M:

		m_scoreUi->ScoreAdd(m_scoreM);

		break;
	case Crystal::en_crystal_R:

		m_scoreUi->ScoreAdd(m_scoreR);

		break;
	case Crystal::en_crystal_Y:

		m_scoreUi->ScoreAdd(m_scoreY);

		break;
	default:
		break;
	}

	m_managerCrystalPtr->ArrangementDataRefresh(this);
}