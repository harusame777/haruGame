#include "stdafx.h"
#include "Locker.h"

bool Locker::Start()
{
	m_animationClip[EnAnimationClip::en_idle].Load("Assets/modelData/objects/locker/locker_idle_AnimationV2.tka");
	m_animationClip[EnAnimationClip::en_idle].SetLoopFlag(true);

	m_animationClip[EnAnimationClip::en_OpenLocker].Load("Assets/modelData/objects/locker/locker_open_AnimationV2.tka");
	m_animationClip[EnAnimationClip::en_OpenLocker].SetLoopFlag(true);

	m_mainModel.Init("Assets/modelData/objects/locker/lockerV2.tkm",m_animationClip, en_animationNum,
		enModelUpAxisZ, ModelRender::en_usuallyShader);

	//ˆÊ’uÝ’è
	m_mainModel.SetPosition(m_position);
	//‰ñ“]’lÝ’è
	m_mainModel.SetRotation(m_rotation);

	//“–‚½‚è”»’è‚ðì¬
	m_physicsStaticObject.CreateFromModel(m_mainModel.GetModel(), m_mainModel.GetModel().GetWorldMatrix());

	//‘®«‚ðÝ’è
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);


	return true;
}

void Locker::Update()
{

	m_mainModel.PlayAnimation(EnAnimationClip::en_OpenLocker);

	m_physicsStaticObject.GetRigitBody()->SetPositionAndRotation(m_position, m_rotation);

	m_mainModel.Update();

}

void Locker::Render(RenderContext& rc)
{
	m_mainModel.Draw(rc);
}