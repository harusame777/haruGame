#pragma once

//�萔��
namespace {
	static const Vector3 WINDOWTOP_OPEN_POSITION = { 0.0f,400.0f,0.0f };
	static const Vector3 WINDOWTOP_CLOSE_POSITION = { 0.0f,20.0f,0.0f };
	static const Vector3 WINDOWBOTTOM_OPEN_POSITION = { 0.0f,-400.0f,0.0f };
	static const Vector3 WINDOWBOTTOM_CLOSE_POSITION = { 0.0f,-20.0f,0.0f };
}

class Window : public IGameObject
{
private:
	/// <summary>
	/// �E�B���h�E�X�e�[�g
	/// </summary>
	enum WindowState {
		//�ҋ@
		en_state_standby,
		//�E�B���h�E�J����
		en_state_windowOpen,
		//�J������Ԃőҋ@
		en_state_openWait,
		//�E�B���h�E�߂�
		en_state_windowClose,
		//�E�B���h�E���鏈������
		en_state_windowCloseCompletion,
		
	};
	WindowState m_windowState = WindowState::en_state_standby;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Window(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Window(){}
	/// <summary>
	/// �E�B���h�E�I�[�v��
	/// </summary>
	void WindowOpen()
	{
		if (m_windowState != WindowState::en_state_standby)
		{
			return;
		}

		m_windowState = WindowState::en_state_windowOpen;

		m_windowFrameEasingMax = WINDOWTOP_OPEN_POSITION.y;

		m_windowFrameEasingMin = WINDOWTOP_CLOSE_POSITION.y;

		m_windowFrameRatio = 0.0f;

		m_isWindowCloseCompletion = false;

		m_isWindowDraw = true;
	}
	/// <summary>
	/// �E�B���h�E�N���[�Y
	/// </summary>
	void WindowClose()
	{
		if (m_windowState != WindowState::en_state_openWait)
		{
			return;
		}

		m_windowState = WindowState::en_state_windowClose;

		m_windowFrameEasingMax = WINDOWTOP_CLOSE_POSITION.y;

		m_windowFrameEasingMin = WINDOWTOP_OPEN_POSITION.y;

		m_windowFrameRatio = 0.0f;
	}

	const bool& IsWindowOpen()const 
	{
		if (m_windowState != WindowState::en_state_openWait)
		{
			return false;
		}

		return true;
	}

	const bool& IsWindowClose()const 
	{
		return m_isWindowCloseCompletion;
	}
private:
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
	/// �E�B���h�E�̃X�e�[�g�X�V�֐�
	/// </summary>
	void WindowStateUpdate();
	/// <summary>
	/// �E�B���h�E�g�X�V
	/// </summary>
	const float& WindowFrameUpdate();
	/// <summary>
	/// �E�B���h�E�x�[�X�̃��C�v�v�Z�֐�
	/// </summary>
	const float& WindowBaseWipeCalc();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �E�B���h�E�̃f�[�^
	/// </summary>
	struct WindowDatas
	{
	private:
		/// <summary>
		/// ���C�v����
		/// </summary>
		float m_wipeRatio = 0.0f;
	public:
		/// <summary>
		/// ���C�v�����ݒ�
		/// </summary>
		/// <param name="value"></param>
		void SetWipeRatio(const float value)
		{
			m_wipeRatio = value;
		}
		/// <summary>
		/// ���C�v�����擾
		/// </summary>
		/// <returns></returns>
		const float GetWipeRatio() const
		{
			return m_wipeRatio;
		}
	};
	WindowDatas m_windowDatas;
	/// <summary>
	/// �E�B���h�E��`�悷�邩�ǂ���
	/// </summary>
	bool m_isWindowDraw = false;
	/// <summary>
	/// �E�B���h�E�������������ǂ���
	/// </summary>
	bool m_isWindowCloseCompletion = false;
	/// <summary>
	/// �E�B���h�E�㕔
	/// </summary>
	SpriteRender m_window_top;
	/// <summary>
	/// �E�B���h�E����
	/// </summary>
	SpriteRender m_window_bottom;
	/// <summary>
	/// �E�B���h�E�̃t���[���̃C�[�W���O�Ɏg�p����ϐ�
	/// </summary>
	float m_windowFrameRatio = 0.0f;
	float m_windowFrameEasingMax = 0.0f;
	float m_windowFrameEasingMin = 0.0f;
	/// <summary>
	/// �E�B���h�E�x�[�X
	/// </summary>
	SpriteRender m_window_base;
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
};
