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



}

void GameEffect::Render(RenderContext& rc)
{

}