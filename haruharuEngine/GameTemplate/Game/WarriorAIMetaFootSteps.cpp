#include "stdafx.h"
#include "WarriorAIMetaFootSteps.h"
#include "GameSound.h"
#include "Player.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"

//定数等
namespace {

	static const float HIGH_VALUME_EXP = 3.0f;
	static const float MIDDLE_VALUME_EXP = 5.0f;
	static const float LOW_VALUME_EXP = 10.0f;
}

//メタAIの初期化
void WarriorAIMetaFootSteps::MetaAIInit()
{
	m_player = FindGO<Player>("player");
	//コライダーを初期化
	m_sphereCollider.Create(1.0f);
}

//メタAIの実行
void WarriorAIMetaFootSteps::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	//エネミーの数取得
	m_enemyNum = m_sharedWarriorDatas->m_warriorDatas.size();

	if (m_enemyLengthDatas[0].m_enemyData == nullptr)
	{
		for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
		{
			m_enemyLengthDatas[enemyNo].m_enemyData
				= &m_sharedWarriorDatas->m_warriorDatas[enemyNo]->GetEnemyPtr();
		}

		return;
	}

	//距離データ初期化
	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{
		m_enemyLengthDatas[enemyNo].m_length = 0.0f;

		m_enemyLengthDatas[enemyNo].m_priority = en_priority_non;
	}

	EnemyStateCheck();

	LengthCalc();

	DatasPriorityInit();

	DatasEnemyWallCheck();
}

void WarriorAIMetaFootSteps::EnemyStateCheck()
{

	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{

		m_enemyLengthDatas[enemyNo].m_warriorStateNum
			= m_enemyLengthDatas[enemyNo].m_enemyData->GetStateNumber();

		if (m_enemyLengthDatas[enemyNo].m_warriorStateNum
			!= EnemySM_Warrior::en_warrior_tracking &&
			m_enemyLengthDatas[enemyNo].m_warriorStateNum
			!= EnemySM_Warrior::en_warrior_trackingMetaAI)
		{
			m_enemyLengthDatas[enemyNo].m_enemyData
				->SetFootStepFlag(true);

			return;
		}
	}

}

//距離計算
void WarriorAIMetaFootSteps::LengthCalc()
{

	//エネミー全体のプレイヤーとの距離を測る
	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{
		
		Vector3 diff = m_player->GetPosition()
			- m_enemyLengthDatas[enemyNo].m_enemyData->GetPosition();

		m_enemyLengthDatas[enemyNo].m_length = diff.Length();

	}	

}

void WarriorAIMetaFootSteps::DatasPriorityInit()
{

	EnemyLength_Data* highData = nullptr;
	std::vector<EnemyLength_Data*> lowDatas;
	
	//まず先頭要素のエネミーを一番近いエネミーと課程する
	//そして格納したデータとほかのデータを
	//比べて小さい方をhighに代入する
	//lowも大体同じ処理
	highData = &m_enemyLengthDatas[0];
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{
		if (highData->m_length
			> m_enemyLengthDatas[enemyNo].m_length)
			highData = &m_enemyLengthDatas[enemyNo];
	}

	//そしてそれ以外のデータをlowに指定
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{
		if (&m_enemyLengthDatas[enemyNo] == highData)
			continue;
		else
			lowDatas.push_back(&m_enemyLengthDatas[enemyNo]);
	}

	//最終設定
	highData->m_enemyData->SetFootStepFlag(true);

	for (auto& listData : lowDatas)
	{
		listData->m_enemyData->SetFootStepFlag(false);
	}
}


//壁の判定を取る構造体
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	/// <summary>
	/// 対象属性にレイが当たったかどうか
	/// </summary>
	bool isHit = false;
	/// <summary>
	///	判定
	/// </summary>
	/// <param name="covexResult"></param>
	/// <param name="normalInWorldSpace"></param>
	/// <returns></returns>
	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& covexResult,
		bool normalInWorldSpace)
	{
		//壁とぶつかっていなかったら
		if (covexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall)
		{
			//衝突したのは壁ではない
			return 0.0f;
		}

		//壁とぶつかってたらフラグをtrueにする
		isHit = true;
		return 0.0f;
	}
};

const bool& WarriorAIMetaFootSteps::RayTestWall(EnemyBase* initEnemy)
{
	//壁越しに見つけないようにレイを使用して壁の判定を取る
	//コライダーの始点と終点を初期化
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();

	//始点位置決定
	Vector3 startPos = initEnemy->GetPosition();
	startPos.y += 70.0f;
	start.setOrigin(btVector3(startPos.x, startPos.y, startPos.z));

	//終点位置決定
	Vector3 endPos = m_player->GetPosition();
	endPos.y += 75.0f;
	end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));

	SweepResultWall callback;

	//衝突検出
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(),
		start, end, callback);
	if (callback.isHit) {
		//当たった
		return true;
	}

	//当たってない
	return false;
}

const bool& WarriorAIMetaFootSteps::IsinCamera(EnemyBase* initEnemy)
{

	Vector3 diff = initEnemy->GetPosition() - g_camera3D->GetPosition();

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

void WarriorAIMetaFootSteps::DatasEnemyWallCheck()
{
	
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{

		if (RayTestWall(m_enemyLengthDatas[enemyNo].m_enemyData))
		{
			m_enemyLengthDatas[enemyNo].m_enemyData->SetValumeCalcValue(LOW_VALUME_EXP);

			continue;
		}

		if (IsinCamera(m_enemyLengthDatas[enemyNo].m_enemyData))
		{
			m_enemyLengthDatas[enemyNo].m_enemyData->SetValumeCalcValue(HIGH_VALUME_EXP);

			continue;
		}

		m_enemyLengthDatas[enemyNo].m_enemyData->SetValumeCalcValue(MIDDLE_VALUME_EXP);

	}
}

//処理終了
const bool WarriorAIMetaFootSteps::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}
