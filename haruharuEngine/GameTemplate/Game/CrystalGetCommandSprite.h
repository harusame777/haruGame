#pragma once
class CrystalGetCommandSprite : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CrystalGetCommandSprite();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CrystalGetCommandSprite();
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
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
};

