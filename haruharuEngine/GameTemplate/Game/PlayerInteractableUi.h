#pragma once
#include "PlayerUIBase.h"

class PlayerInteractableUi : public PlayerUIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerInteractableUi(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerInteractableUi(){}
	/// <summary>
	/// �C���^���N�g�\�X�v���C�g�`��t���O�ݒ�
	/// </summary>
	/// <param name="drawFlag"></param>
	void SetInteractableDrawFlag(const bool& drawFlag)
	{
		if (m_interactableDarwFlag == true)
		{
			return;
		}

		m_interactableDarwFlag = drawFlag;
	}
	/// <summary>
	/// �C���^���N�g�\�X�v���C�g�`��t���O�擾
	/// </summary>
	/// <returns></returns>
	const bool& GetInteractableDrawFlag() const
	{
		return m_interactableDarwFlag;
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
	/// �����_�[�֐�
	/// </summary>
	void Render(RenderContext& rc);
	/// <summary>
	/// �C���^���N�g�\�X�v���C�g�`��t���O
	/// </summary>
	bool m_interactableDarwFlag = false;
	/// <summary>
	/// �C���^���N�g�\�X�v���C�g
	/// </summary>
	FontRender m_interactableFontSprite;
};

