#pragma once

namespace nsK2EngineLow {
	class DirectionalLight : Noncopyable
	{
	public:
		//�R���X�g���N�^
		DirectionalLight();
		//�f�X�g���N�^
		~DirectionalLight();
	private:
		//�f�B���N�V�������C�g�̍\����
		SDirectionLight* m_directionLight;
	};
}

