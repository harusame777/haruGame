#pragma once

class WarriorDataHolder;
class EnemySM_Warrior;

//�萔��
namespace {
	/// <summary>
	/// �����T�C�Y
	/// </summary>
	static const float SPRITE_W_SIZE = 150.0f;
	static const float SPRITE_H_SIZE = 150.0f;
}

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
	struct StateMarker
	{
		/// <summary>
		/// �}�[�J�[�̐F
		/// </summary>
		SpriteRender m_makerColor;
	};
	struct EnemyDebugStruct
	{
		EnemySM_Warrior* m_enemySM = nullptr;
		StateMarker* m_colorList[4];
		StateMarker m_grayMarker;
		StateMarker m_redMarker;
		StateMarker m_yellowMarker;
		StateMarker m_greenMarker;
		/// <summary>
		/// �X�v���C�g�̈ʒu
		/// </summary>
		Vector2 m_spritePosition;
		/// <summary>
		/// �E�H���A�[�̈ʒu
		/// </summary>
		Vector3 m_warriorPosition;
		/// <summary>
		/// �X�e�[�g�i���o�[
		/// </summary>
		int m_warriorTrackingStateNum = 0;
	public:
		void InitColor()
		{	
			//�D�F�}�[�J�[��ݒ�
			m_grayMarker.m_makerColor.Init("Assets/modelData/debug/testWarriorTrackingStateGray.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
			m_colorList[0] = &m_grayMarker;
			//�ԐF�}�[�J�[��ݒ�
			m_redMarker.m_makerColor.Init("Assets/modelData/debug/testWarriorTrackingStateRed.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
			m_colorList[1] = &m_redMarker;
			//���F�}�[�J�[��ݒ�
			m_yellowMarker.m_makerColor.Init("Assets/modelData/debug/testWarriorTrackingStateYellow.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
			m_colorList[2] = &m_yellowMarker;
			//�ΐF�}�[�J�[��ݒ�
			m_greenMarker.m_makerColor.Init("Assets/modelData/debug/testWarriorTrackingStateGreen.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
			m_colorList[3] = &m_greenMarker;
		}
	};
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
	const bool IsInCamera(EnemyDebugStruct* ptr);
	/// <summary>
	/// �X�e�[�g�}�[�J�[
	/// </summary>
	std::vector<EnemyDebugStruct*> m_enemyDebugSpriteList;
	/// <summary>
	/// �E�H���A�[�̋��ʃf�[�^�z���_�`
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
};

