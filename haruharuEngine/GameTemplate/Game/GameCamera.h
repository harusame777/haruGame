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
