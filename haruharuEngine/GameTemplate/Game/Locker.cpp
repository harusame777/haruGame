#include "stdafx.h"
#include "Locker.h"
#include "ManagerLocker.h"

bool Locker::Start()
{
	m_animationClip[EnAnimationClip::en_idle].Load("Assets/modelData/objects/locker/locker_idle_AnimationV3.tka");
	m_animationClip[EnAnimationClip::en_idle].SetLoopFlag(true);

	m_animationClip[EnAnimationClip::en_OpenLocker].Load("Assets/modelData/objects/locker/locker_open_AnimationV3.tka");
	m_animationClip[EnAnimationClip::en_OpenLocker].SetLoopFlag(false);

	m_mainModel.Init("Assets/modelData/objects/locker/lockerV3.tkm",m_animationClip, en_animationNum,
		enModelUpAxisZ, ModelRender::en_usuallyShader);

	//CameraMoveStart
	m_mainModel.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});
	
	//ˆÊ’uÝ’è
	m_mainModel.SetPosition(m_position);
	//‰ñ“]’lÝ’è
	m_mainModel.SetRotation(m_rotation);

	//“–‚½‚è”»’è‚ðì¬
	m_physicsStaticObject.CreateFromModel(m_mainModel.GetModel(), m_mainModel.GetModel().GetWorldMatrix());

	InitBootObject("Assets/modelData/objects/locker/BootPosition.tkl");

	return true;
}

void Locker::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	if (wcscmp(eventName, L"CameraMoveStart") == 0)
	{

	}
}

void Locker::Update()
{

	LockerExecution();

	m_physicsStaticObject.GetRigitBody()->SetPositionAndRotation(m_position, m_rotation);

	m_mainModel.PlayAnimation(m_animationClipState);

	UpdateBootData();


	m_mainModel.Update();

}

void Locker::LockerExecution()
{

	if (IsObjectBootConditions())
	{
		if (m_lockerManager->IsWholeLockersInUse())
			return;

		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_animationClipState = EnAnimationClip::en_OpenLocker;

			m_isLockerInUse = true;
		}
	}

	if (m_mainModel.IsPlayingAnimation() == false)
	{
		m_animationClipState = EnAnimationClip::en_idle;
	}

}

void Locker::Render(RenderContext& rc)
{
	m_mainModel.Draw(rc);
}