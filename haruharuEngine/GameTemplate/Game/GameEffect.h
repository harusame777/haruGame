#pragma once

class GameEffect : public IGameObject
{
public: 
	enum EffectListNum
	{
		//�����G�t�F�N�g
		en_hitEffect,
	};
	/// <summary>
	/// �G�t�F�N�g���w�肵�ďo��������
	/// </summary>
	/// <param name="listNum"></param>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	void LocalEffectOrder(
		const EffectListNum& listNum,
		const Vector3& pos,
		const Quaternion& rot
	);
	/// <summary>
	/// �G�t�F�N�g���w�肵�ă^�[�Q�b�gA�Ɍ����ďo��������
	/// </summary>
	/// <param name="listNum"></param>
	/// <param name="effectPos"></param>
	/// <param name="targetPosA"></param>
	/// <param name="targetPosB"></param>
	void LocalEffectOrder(
		const EffectListNum& listNum,
		const Vector3& effectPos,
		const Vector3& targetPosA
	);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameEffect(){}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameEffect(){}
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

