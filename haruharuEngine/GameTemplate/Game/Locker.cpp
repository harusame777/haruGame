#include "stdafx.h"
#include "Locker.h"
#include "ManagerLocker.h"

bool Locker::Start()
{
	m_animationClip[EnAnimationClip::en_idle].Load("Assets/modelData/objects/locker/locker_idle_AnimationV3.tka");
	m_animationClip[EnAnimationClip::en_idle].SetLoopFlag(true);

	m_animationClip[EnAnimationClip::en_OpenLocker].Load("Assets/modelData/objects/locker/locker_open_AnimationV3.tka");
	m_animationClip[EnAnimationClip::en_OpenLocker].SetLoopFlag(false);

	m_mainModel.Init("Assets/modelData/objects/locker/lockerV4.tkm",m_animationClip, en_animationNum,
		enModelUpAxisZ, ModelRender::en_usuallyShader);

	//CameraMoveStart
	m_mainModel.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});
	
	//位置設定
	m_mainModel.SetPosition(m_position);
	//回転値設定
	m_mainModel.SetRotation(m_rotation);

	//当たり判定を作成
	m_physicsStaticObject.CreateFromModel(m_mainModel.GetModel(), m_mainModel.GetModel().GetWorldMatrix());

	InitBootObject("Assets/modelData/objects/locker/BootPosition.tkl");

	Vector3 levelPos = Vector3::Zero;

	//カメラターゲット計算
	m_cameraPosInLevel.Init("Assets/modelData/objects/locker/LockerCameraPos.tkl",
		[&](LevelObjectData_Render& objData)
	{
		if (objData.EqualObjectName(L"CameraTargetPos") == true)
		{
			levelPos = objData.m_position;

			return true;
		}
		return true;
	});

	//正面方向計算
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	float angle = atan2(m_forward.x, m_forward.z);

	float cosNum = cos(angle);
	float sinNum = sin(angle);

	m_cameraTargetPos = {
		levelPos.x * cosNum + levelPos.z * sinNum,
		levelPos.y,
		-levelPos.x * sinNum + levelPos.z * cosNum
	};

	m_cameraTargetPos += m_position;

	return true;
}

void Locker::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	if (wcscmp(eventName, L"CameraMoveStart") == 0)
	{
		if (m_lockerState == LockerState::en_standby)
		{
			m_lockerState = LockerState::en_lockerInCameraEasing;

			m_cameraEasingStart = g_camera3D->GetPosition();
		}

		if (m_lockerState == LockerState::en_playerInUse)
			m_lockerState = LockerState::en_lockerOutCameraEasing;


		Vector3 endPos = m_position;

		endPos.y += 55.0f;

		m_cameraEasingEnd = endPos;

		m_cameraEasingRatio = 0.0f;
	}
}

void Locker::Update()
{

	LockerStateUpdate();

	m_physicsStaticObject.GetRigitBody()->SetPositionAndRotation(m_position, m_rotation);

	m_mainModel.PlayAnimation(m_animationClipState);

	UpdateBootData();

	m_mainModel.Update();
}

void Locker::LockerStateUpdate()
{
	Vector3 testPos = m_position;
	testPos.y += 55.0f;

	switch (m_lockerState)
	{
	case Locker::en_standby:

		if (IsObjectBootConditions())
		{
			if (m_lockerManager->IsWholeLockersInUse() == true)
				return;

			if (g_pad[0]->IsTrigger(enButtonB))
			{

				m_animationClipState = EnAnimationClip::en_OpenLocker;

				m_isLockerInUse = true;

				m_lockerManager->SetPlayerInLocker();
			}
		}

		break;
	case Locker::en_lockerInCameraEasing:

		if (LockerInCameraEasing(false) && 
			m_mainModel.IsPlayingAnimation() == false)
		{
			m_animationClipState = EnAnimationClip::en_idle;

			m_lockerState = LockerState::en_playerInUse;

			Vector3 targetPos = (m_forward * 20.0f) + m_position;

			m_lockerManager->SetCameraTarget(targetPos);
		}

		break;
	case Locker::en_playerInUse:

		g_camera3D->SetPosition(m_cameraEasingEnd);

		if (IsObjectBootConditions())
		{
			if (m_lockerManager->IsWholeLockersInUse() == false)
				return;

			if (g_pad[0]->IsTrigger(enButtonB))
			{
				m_animationClipState = EnAnimationClip::en_OpenLocker;

				m_lockerManager->SetPlayerOutLocker();
			}
		}

		break;

	case Locker::en_lockerOutCameraEasing:

		if (LockerInCameraEasing(true) &&
			m_mainModel.IsPlayingAnimation() == false)
		{
			m_animationClipState = EnAnimationClip::en_idle;

			m_lockerState = LockerState::en_standby;

			m_isLockerInUse = false;

			m_lockerManager->SetCameraTarget(m_position);
		}

		break;
	default:
		break;
	}


}

const bool Locker::LockerInCameraEasing(const bool swap)
{
	Vector3 easingPos;

	//カメライージング割合を加算
	m_cameraEasingRatio += g_gameTime->GetFrameDeltaTime() * 2.0f;

	if (swap == true)
	{
		easingPos.Lerp(
			m_cameraEasingRatio,
			m_cameraEasingEnd,
			m_cameraEasingStart);
	}
	else
	{
		easingPos.Lerp(
			m_cameraEasingRatio,
			m_cameraEasingStart,
			m_cameraEasingEnd);
	}

	g_camera3D->SetPosition(easingPos);

	g_camera3D->SetTarget(m_cameraTargetPos);

	//カメライージング割合が1.0fより多かったら
	if (m_cameraEasingRatio > 1.0f)
	{
		//カメライージング割合を1.0fにして
		m_cameraEasingRatio = 1.0f;

		return true;
	}

	return false;
}

void Locker::Render(RenderContext& rc)
{
	m_mainModel.Draw(rc);
}