#pragma once

#include "graphics/light/SceneLight.h"

namespace nsK2EngineLow {
	/// <summary>
	/// ���f����`�悷�邽�߂̃��c
	/// </summary>
	class ModelRender : public IRenderer{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		ModelRender();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~ModelRender();

		struct ShadowLightData
		{
		public:
			Light m_light;
			Matrix m_mt;
		};

		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="tkmfilePath">���f���̃t�@�C���p�X</param>
		/// <param name="animationClips">�A�j���[�V�����N���b�v</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐�</param>
		/// <param name="enModelUpAxis">���f���̏����</param>
		/// <param name="dithering">�f�B�U�����O�t���O�Ature�Ȃ�f�B�U�����O���s��</param>
		/// <param name="isRecieverShadow">�e�𗎂Ƃ������߂�t���O�Ature�Ȃ�e��������</param>
		void Init(
			const char* tkmfilePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool isRecieveShadow = false
		);

		void InitNormalModel(
			const char* tkmfilePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool isRecieveShadow = false
		);

		void InitShadowModel(
			const char* tkmfilePath,
			EnModelUpAxis modelUpAxis
		);

		/// <summary>
		/// GBuffer�`��p�̃��f�����������B
		/// </summary>
		/// <param name="renderingEngine">�����_�����O�G���W��</param>
		/// <param name="tkmFilePath">tkm�t�@�C���p�X</param>
		void InitModelOnRenderGBuffer(
			RenderingEngine& renderingEngine,
			const char* tkmFilePath,
			EnModelUpAxis enModelUpAxis,
			bool isShadowReciever
		);

		//�X�P���g���̏�����
		void InitSkeleton(const char* filePath);

		//�A�j���[�V�����̏�����
		void InitAnimation(
			AnimationClip* animationClips,
			int numAnimationClips
		);

		//�A�j���[�V�����Đ�
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		//�A�j���[�V�������Đ������ǂ���
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		//�A�j���[�V�����̑��x��ݒ�
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		//�A�j���[�V�����C�x���g(��Œ��ׂ�)
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}

		//�X�V����
		void Update();

		//���W��ݒ�
		void SetPosition(Vector3 pos)
		{
			m_position = pos;
		}

		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//��]��ݒ�
		void SetRotation(Quaternion rot)
		{
			m_rotation = rot;
		}

		//�g�嗦��ݒ�
		void SetScale(Vector3 scale)
		{
			m_scale = scale;
		}

		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}

		Model& GetModel()
		{
			return m_model;
		}

		//�`�揈��
		void Draw(RenderContext& rc);

		//3D���f���̕`�揈��
		void OnRenderModel(RenderContext& rc) override;

		//�V���h�E�}�b�v�ւ̕`��p�X����Ă΂�鏈��
		void OnRenderShadowMap(RenderContext& rc, const Matrix& lvpMatrix) override;

		//G-Buffer�`��p�X����Ă΂�鏈��
		void OnRenderToGBuffer(RenderContext& rc) override;

		//�e��`�悷�邩���Ȃ�����ݒ�
		void SetShadowChasterFlag(bool flag)
		{
			m_isShadowChaster = flag;
		}

	private:
		//���f�������_�[�ɐݒ肳��Ă��郂�f��
		Model m_model;
		//���f�������_�[�ɐݒ肳��Ă���X�P���g��
		Skeleton m_skeleton;
		//���f�������_�[�ɐݒ肳��Ă���A�j���[�V�����N���b�v
		AnimationClip* m_animationClips = nullptr;
		//�A�j���[�V�����N���b�v�̐�
		int m_numAnimationClips = 0;
		//�A�j���[�V�����X�s�[�h
		float m_animationSpeed = 1.0f;
		//�A�j���[�V�����N���X
		Animation m_animation;

		//���f�������_�[�ɐݒ肳��Ă�����W
		Vector3 m_position = Vector3::Zero;
		//���f�������_�[�ɐݒ肳��Ă����]�l
		Quaternion m_rotation = Quaternion::Identity;
		//���f�������_�[�ɐݒ肳��Ă��郂�f���̑傫��
		Vector3 m_scale = Vector3::One;
		
		Model m_shadowModel;

		Model m_gBufferModel;

		ShadowLightData m_shadowLigData;

		//�e�𗎂Ƃ����Ǘ�����t���O
		bool m_isShadowChaster = true;		
	};
}
