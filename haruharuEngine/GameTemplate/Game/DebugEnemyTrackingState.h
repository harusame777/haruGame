#pragma once

class WarriorDataHolder;

class DebugEnemyTrackingState : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DebugEnemyTrackingState();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DebugEnemyTrackingState();
	/// <summary>
	/// �f�[�^������
	/// </summary>
	/// <param name="data"></param>
	void InitWarriorListData(std::shared_ptr<WarriorDataHolder> data)
	{
		m_warriorDataHolder = data;
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
	/// �h���[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �}�[�J�[�̈ʒu���X�V����֐�
	/// </summary>
	void MarkerPositionUpdate();
	/// <summary>
	/// �`��X�V
	/// </summary>
	void SpriteUpdate();
	/// <summary>
	/// �X�e�[�g�}�[�J�[
	/// </summary>
	struct StateMarker
	{
		/// <summary>
		/// �X�e�[�g�i���o�[
		/// </summary>
		int m_warriorTrackingStateNum = 0;
		/// <summary>
		/// �X�v���C�g�̈ʒu
		/// </summary>
		Vector2 m_spritePosition;
		/// <summary>
		/// �E�H���A�[�̈ʒu
		/// </summary>
		Vector3 m_warriorPosition;
		/// <summary>
		/// �}�[�J�[�̐F
		/// </summary>
		SpriteRender* m_makerColor[4];
	};
	/// <summary>
	/// �X�e�[�g�}�[�J�[�̔z��
	/// </summary>
	StateMarker m_stateMarkers[3];
	SpriteRender m_grayMarker;
	SpriteRender m_redMarker;
	SpriteRender m_yellowMarker;
	SpriteRender m_greenMarker;
	/// <summary>
	/// �E�H���A�[�̋��ʃf�[�^�z���_�`
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
};

