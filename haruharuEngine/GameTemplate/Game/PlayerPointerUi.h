#pragma once
#include "PlayerUIBase.h"

class Elevator;

class PlayerPointerUi : public PlayerUIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerPointerUi() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerPointerUi() {};
	/// <summary>
	/// �`��ł��邩�ݒ�
	/// </summary>
	/// <param name="setDraw"></param>
	void SetPointerDraw(bool setDraw)
	{
		m_isPointerDraw = setDraw;
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
	/// �|�C���^�̈ʒu�X�V
	/// </summary>
	void PointerPositionUpdate();
	/// <summary>
	/// �X�v���C�g�̍X�V
	/// </summary>
	void SpriteUpdate();
	/// <summary>
	/// �J�������ɃX�v���C�g�����邩���ׂ�
	/// </summary>
	/// <returns></returns>
	bool IsSpriteInCamera();
	/// <summary>
	/// �h���[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �|�C���^
	/// </summary>
	SpriteRender m_pointer;
	/// <summary>
	/// �t�H���g�����_�[
	/// </summary>
	FontRender m_font;
	/// <summary>
	/// �|�C���^
	/// </summary>
	bool m_isPointerDraw = false;
	/// <summary>
	/// �X�v���C�g�̈ʒu
	/// </summary>
	Vector2 m_spritePosition;
	/// <summary>
	/// �G���x�[�^�[�̃C���X�^���X
	/// </summary>
	Elevator* m_elevator = nullptr;
};

