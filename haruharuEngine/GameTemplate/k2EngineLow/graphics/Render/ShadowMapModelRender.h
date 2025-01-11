#pragma once
#include "graphics/Render/ShadowMapRender.h"

namespace nsK2EngineLow {

	class ShadowMapModelRender :
		public ShadowMapRender,
		Noncopyable
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		ShadowMapModelRender();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~ShadowMapModelRender();
		/// <summary>
		/// �V���h�E�}�b�v�̃��f����������
		/// </summary>
		const Model& InitShadowMapModelRender(
			const char* tkmfilePath,
			EnModelUpAxis enModelUpAxis,
			AnimationClip* animationClips,
			const Light& ligPtr
		);
	private:
		/// <summary>
		/// �V���h�E�}�b�v�̃p�����[�^�[�\����
		/// </summary>
		struct ShadowMapParam
		{
			Matrix mLVP;
			Vector3 ligPos;
		};
		/// <summary>
		/// �X�P���g��
		/// </summary>
		Skeleton m_skeleton;
		/// <summary>
		/// �V���h�E�}�b�v�̃��f��
		/// </summary>
		Model m_shadowMapModel;
		/// <summary>
		/// �|�W�V����
		/// </summary>
		Vector3 m_position = Vector3::Zero;
		/// <summary>
		/// ��]
		/// </summary>
		Quaternion m_rotation = Quaternion::Identity;
		/// <summary>
		/// �g�嗦
		/// </summary>
		Vector3 m_scale = Vector3::One;
	};
}