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
private:
	enum LoadState
	{
		en_ordinaryLoad,

		en_circularLoad
	};
	LoadState m_loadState;
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
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
	/// <summary>
	/// �����l
	/// </summary>
	float m_loadRange = 0.0f;
	/// <summary>
	/// ���[�h��둤�X�v���C�g
	/// </summary>
	SpriteRender m_loadBackSideSprite;
};

