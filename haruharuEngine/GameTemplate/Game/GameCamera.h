#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameCamera();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameCamera();
	/// <summary>
	/// �J�����̃^�[�Q�b�g��ݒ�
	/// </summary>
	void SetCameraTarget(const Vector3& position);
private:
	/// <summary>
	/// �f�o�b�O���̃J�����̃��[�h
	/// </summary>
	enum CameraMode {
		//FPS���_
		en_camModeFPS,
		//TPS���_
		en_camModeTPS,
	};
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// FPS�J�����̏���
	/// </summary>
	void FPSCam();
	/// <summary>
	/// TPS�J�����̏���
	/// </summary>
	void TPSCam();
	/// <summary>
	/// �J�����̃��[�h�ؑւ�����֐�
	/// </summary>
	void CamFPSorTPS();
	/// <summary>
	/// �V����FPS�J�����̏���
	/// </summary>
	void NewFPSCam();
	/// <summary>
	/// �J�����̑��x
	/// </summary>
	float m_velocityX;
	float m_velocityY;
	/// <summary>
	/// �J�����̊p�x
	/// </summary>
	Quaternion m_camRotation;
	/// <summary>
	/// 
	/// </summary>
	float m_oldFramePadX = 0.0f;
	float m_oldFramePadY = 0.0f;
	/// <summary>
	/// flaot�p���`���
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
	/// ���x�ϐ��`�ۊ�
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
	/// �����_���王�_�܂ł̃x�N�g��
	/// </summary>
	Vector3 m_toCameraPos;
	/// <summary>
	/// �v���C���[�̃C���X�^���X���i�[���邽�߂̕ϐ�
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �J�����̃��[�h
	/// </summary>
	CameraMode m_camMode = en_camModeFPS;
};
