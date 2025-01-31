#include "stdafx.h"
#include "GameEffect.h"

//スタート関数
bool GameEffect::Start()
{
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/hit_eff.efk");

	return true;
}

void GameEffect::Update()
{

}

void GameEffect::LocalEffectOrder(
	const EffectListNum& listNum,
	const Vector3& pos,
	const Quaternion& rot
)
{
	EffectEmitter* localEffectEmitter = NewGO<EffectEmitter>(0);

	localEffectEmitter->Init(listNum);

	localEffectEmitter->SetPosition(pos);

	localEffectEmitter->SetRotation(rot);

	localEffectEmitter->Play();
}

void GameEffect::LocalEffectOrder(
	const EffectListNum& listNum,
	const Vector3& effectPos,
	const Vector3& targetPosA
)
{
	EffectEmitter* localEffectEmitter = NewGO<EffectEmitter>(0);

	localEffectEmitter->Init(listNum);

	localEffectEmitter->SetPosition(effectPos);

	//回転設定
	Vector3 rotVec = targetPosA - effectPos;

	rotVec.Normalize();

	float angle = atan2(rotVec.x, rotVec.z);

	Quaternion rot;

	rot.SetRotation(Vector3::AxisY, angle);

	//localEffectEmitter->SetRotation(rot);

	localEffectEmitter->SetScale(Vector3::One * 5);

	localEffectEmitter->Play();
}

void GameEffect::Render(RenderContext& rc)
{

}