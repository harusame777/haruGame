#pragma once

namespace nsK2EngineLow {
	class DirectionalLight : Noncopyable
	{
	public:
		//�R���X�g���N�^
		DirectionalLight();
		//�f�X�g���N�^
		~DirectionalLight();

		//���C�g�r���[�v���W�F�N�V�����̏�����
		void InitLigVP(const Vector3& basepoint);

		//������ݒ�
		void SetDirection(const Vector3& direction)
		{
			m_directionLight->SetDirection(direction);
		}
		void SetDirection(float x, float y, float z)
		{
			m_directionLight->SetDirection({ x,y,z });
		}
		//�������擾
		const Vector3& GetDirection()
		{
			return m_directionLight->GetDirection();
		}
		//�����𐳋K��
		void LightDirectionNormalize()
		{
			m_directionLight->LightDirectionNormalize();
		}
		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			m_directionLight->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			m_directionLight->SetColor({ r,g,b });
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return m_directionLight->GetColor();
		}
		//�e���L���X�g����悤�ɂ���
		void CastShadow()
		{
			m_directionLight->CastShadow();
		}
		//�e���L���X�g���Ȃ��悤�ɂ���
		void UnCastShadow()
		{
			m_directionLight->UnCastShadow();
		}
		//���C�g�̃r���[�v���W�F�N�V�������쐬����悤�ɂ���
		void MakeLVP()
		{
			m_directionLight->MakeLVP();
		}
		//���C�g�̃r���[�v���W�F�N�V�������쐬���Ȃ��悤�ɂ���
		void UnMakeLVP()
		{
			m_directionLight->UnMakeLVP();
		}

	private:
		//�f�B���N�V�������C�g�̍\����
		SDirectionLight* m_directionLight = nullptr;
	};
}

