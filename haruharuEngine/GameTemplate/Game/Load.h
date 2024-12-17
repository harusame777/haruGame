#pragma once

class Load : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Load(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Load(){}
	/// <summary>
	/// ���[�h��ރX�e�[�g
	/// </summary>
	enum LoadTypeState
	{
		//�ʏ탍�[�h
		en_loadOrdinary,
		//�~�`���[�h
		en_loadCircular
	};
	/// <summary>
	/// �t�F�[�h�A�E�g�����������H
	/// </summary>
	/// <returns></returns>
	const bool& IsLoadBlackout()
	{
		if (m_loadProccesState == LoadProccesState::en_loadBlackoutStandby)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// �t�F�[�h�C�������������H
	/// </summary>
	/// <returns></returns>
	const bool& IsLoadCompletion()
	{
		if (m_loadProccesState == LoadProccesState::en_loadCompletion)
		{
			return true;
		}
		return false;
	}
private:
	/// <summary>
	/// ���[�h�̏�����
	/// </summary>
	enum LoadOrder
	{
		//�t�F�[�h�A�E�g���s���(�Â��Ȃ��)
		en_FadeOut,
		//�t�F�[�h�C�����s���(���邭�Ȃ��)
		en_FadeIn,
	};
	/// <summary>
	/// ���[�h�̎��s�X�e�[�g
	/// </summary>
	enum LoadProccesState
	{
		//���[�h�ҋ@���
		en_loadStandby,
		//�t�F�[�h�C�����s���(���邭�Ȃ��)
		en_loadExecutionFadeIn,
		//�t�F�[�h�A�E�g���s���(�Â��Ȃ��)
		en_loadExecutionFadeOut,
		//���Ԍo�߂Ŏ����I�Ƀt�F�[�h�C�����郍�[�h
		en_loadExecutionTimeLapse,
		//���[�h�Ó]�ҋ@
		en_loadBlackoutStandby,
		//���[�h����
		en_loadCompletion
	};
	LoadProccesState m_loadProccesState = LoadProccesState::en_loadStandby;
	/// <summary>
	/// ���[�h��ރX�e�[�g�i�[�ϐ�
	/// </summary>
	LoadTypeState m_loadTypeState[2];
public:
	struct LoadOrderData
	{
		//�t�F�[�h�A�E�g���郍�[�h
		LoadTypeState m_fadeOutLoad;
		//�t�F�[�h�C�����郍�[�h
		LoadTypeState m_fadeInLoad;
	};
	/// <summary>
	/// �t�F�[�h�A�E�g�����s����
	/// </summary>
	/// <param name="loadType"></param>
	void LoadExecutionFadeOut(const LoadOrderData& loadType);
	/// <summary>
	/// �t�F�[�h�C�������s����
	/// </summary>
	void LoadExecutionFadeIn();
	/// <summary>
	/// ���Ԍo�߂Ńt�F�[�h�C�����郍�[�h�����s����
	/// </summary>
	/// <param name="loadType"></param>
	/// <param name="time"></param>
	void LoadExecutionFadeOut(const LoadOrderData& loadType, const float& time);
private:
	/// <summary>
	/// ���[�h�̃f�[�^
	/// </summary>
	struct LoadDatas
	{
	private:
		/// <summary>
		/// �����l
		/// </summary>
		float m_loadIndex = 0.0f;
		/// <summary>
		/// ���[�h�̃X�e�[�g���V�F�[�_�[�ɑ���ϐ�
		/// </summary>
		int m_loadState = 0;
	public:
		/// <summary>
		/// ���[�h���l��ݒ�
		/// </summary>
		/// <param name="value"></param>
		void SetLoadIndex(const float& value)
		{
			m_loadIndex = value;
		}
		/// <summary>
		/// ���[�h���l���擾
		/// </summary>
		/// <returns></returns>
		const float& GetLoadIndex() const
		{
			return m_loadIndex;
		}
		/// <summary>
		/// ����f�[�^�̃X�e�[�g��ݒ�
		/// </summary>
		/// <param name="stateValue"></param>
		void SetLoadTypeState(const LoadTypeState& stateValue)
		{
			m_loadState = stateValue;
		}
	};
	LoadDatas m_loadDatas;
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// ���[�h�X�e�[�g�A�b�v�f�[�g
	/// </summary>
	void LoadStateUpdate();
	/// <summary>
	/// ���[�h�v�Z
	/// </summary>
	/// <returns></returns>
	const float& LoadCalc(const float& index);
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ���[�h����
	/// </summary>
	float m_loadTimer = 0.0f;
	/// <summary>
	/// ���[�h����
	/// </summary>
	float m_loadRatio = 0.0f;
	/// <summary>
	/// �C�[�W���O�Ɏg�p����ϐ�
	/// </summary>
	float m_loadEasingMax = 0.0f;
	float m_loadEasingMin = 0.0f;
	float m_loadSpeedAttenuationRate[2];
	/// <summary>
	/// ���[�h��둤�X�v���C�g
	/// </summary>
	SpriteRender m_loadBackSideSprite;
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

