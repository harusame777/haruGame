#pragma once
#include "graphics/Render/ModelRender.h"
#include "graphics/Render/ShadowMapRender.h"


namespace nsK2EngineLow {

	class ShadowMapModelRender :
		public ModelRender,
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
		void InitShadowMapModelRender(
			const char* tkmfilePath,
			EnModelUpAxis enModelUpAxis
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
	};

}