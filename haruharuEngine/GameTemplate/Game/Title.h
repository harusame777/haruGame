#pragma once

class Load;

class Title : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Title(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Title(){}
	/// <summary>
	/// �Q�[���^�C�g�����I��������
	/// </summary>
	/// <returns></returns>
	const bool& IsEndGameTitle()
	{
		return m_isGameIn;
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
	/// �t�H���g�̃A�b�v�f�[�g
	/// </summary>
	void FontUpdate();
	/// <summary>
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �w�i
	/// </summary>
	SpriteRender m_backSideSprite;
	/// <summary>
	/// ���C������
	/// </summary>
	FontRender m_mainFont;
	/// <summary>
	/// �T�u����
	/// </summary>
	FontRender m_subFont;
	/// <summary>
	/// �^�C�g��
	/// </summary>
	FontRender m_title;
	/// <summary>
	/// ���[�h��ʂ̃C���X�^���X
	/// </summary>
	Load* m_load;
	/// <summary>
	/// �^�C�g���I�����ăQ�[���C���ɓ���
	/// </summary>
	bool m_isGameIn = false;
};

