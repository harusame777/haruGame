#pragma once

class Crystal;
class GameSound;
class GameEffect;
class Player;

//�萔��
namespace {
	/// <summary>
	/// �c���n�V�C�[�W���O
	/// </summary>
	/// �ҋ@���
	static const float  PICKAXE_STANDBY_RATIO_MIN = 40.0f;
	static const float  PICKAXE_STANDBY_RATIO_MAX = 20.0f;
	/// <summary>
	/// �c���n�V�C�[�W���O
	/// </summary>
	/// �̌@���
	static const float PICKAXE_IMPACT_RATIO_MIN = -80.0f;
	static const float PICKAXE_IMPACT_RATIO_MAX = 40.0f;
}

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
	/// <summary>
	/// �̎�J�n
	/// </summary>
	/// <param name="crystal"></param>
	void CrystalCollectStart(Crystal* crystal)
	{
		//�̎撆�������珈�����Ȃ�
		if (m_isCollectFlag == true)
		{
			return;
		}
		//�̎悳���N���X�^���̃C���X�^���X��o�^����
		m_crystal = crystal;
		//�R�}���h�����X�g���X�V����
		CommandMix();
		//�������Ԃ�������
		m_timeLimit = 2.0f;
		//���݂̃R�}���h���X�g�̏ꏊ��������
		m_nowCommandNum = 0;
		//�c���n�V�̃C�[�W���O������������
		PickaxeEasingInit(PickaxeMoveState::en_standby);
		//��]��������
		Quaternion startRot;
		startRot.SetRotationDegZ(PICKAXE_STANDBY_RATIO_MIN);
		m_pickaxeSprite.SetRotation(startRot);
		//�̎�t���O���I���ɂ���
		m_isCollectFlag = true;
		//�R�}���h����͂ł���悤��
		m_isCommandInput = true;
	}

	const bool& GetCollectFlag() const
	{
		return m_isCollectFlag;
	}

private:
	/// <summary>
	/// �c���n�V�̉�]�X�e�[�g
	/// </summary>
	enum PickaxeMoveState
	{
		/// <summary>
		/// �ҋ@
		/// </summary>
		en_standby,
		/// <summary>
		/// �@��
		/// </summary>
		en_impact,
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
	/// �����_�[�֐�
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �R�}���h�A�b�v�f�[�g
	/// </summary>
	void CommandUpdate();
	/// <summary>
	/// �R�}���h���X�g�ɃR�}���h�������_���Ɍ��肷��֐�
	/// </summary>
	void CommandMix();
	/// <summary>
	/// �X�v���C�g��ݒ�
	/// </summary>
	void InitSprite();
	/// <summary>
	/// �c���n�V�X�v���C�g�̃A�b�v�f�[�g�֐�
	/// </summary>
	void PickaxeSpriteUpdate();
	/// <summary>
	/// �c���n�V�̉�]�C�[�W���O�֐�
	/// </summary>
	const float PickaxeRotEasing(const PickaxeMoveState picMoveState);
	/// <summary>
	/// �v���C���[���̎�\�͈͓��ɂ��邩�ǂ����𔻒�
	/// </summary>
	/// <returns></returns>
	const bool& IsRangeInPlayer();
	/// <summary>
	/// ���{�^���������ꂽ���𔻒肷��X�e�[�g
	/// </summary>
	enum CommandTriggerState
	{
		//�������ꂽ�̂�Y�{�^��
		en_isTriggerY,
		//�������ꂽ�̂�B�{�^��
		en_isTriggerB,
		//�������ꂽ�̂�A�{�^��
		en_isTriggerA,
		//�������ꂽ�̂�X�{�^��
		en_isTriggerX,
		//�{�^����
		ButtonNum
	};
	/// <summary>
	/// �R�}���h���X�g�̍ő�l
	/// </summary>
	static const int COMMAND_MAX = 5;
	/// <summary>
	/// �R�}���h���X�g
	/// </summary>
	int m_commandList[COMMAND_MAX];
	/// <summary>
	/// ���݂̃R�}���h�i���o�[
	/// </summary>
	int m_nowCommandNum = 0;
	/// <summary>
	/// �������{�^���������ꂽ���ǂ����̃t���O
	/// </summary>
	bool m_isCorrectButton = false;
	/// <summary>
	/// �̎�t���O
	/// </summary>
	bool m_isCollectFlag = false;
	/// <summary>
	/// �R�}���h���͂ł��邩
	/// </summary>
	bool m_isCommandInput = true;
	/// <summary>
	/// �c���n�V�̃X�v���C�g���߂��Ă��邩
	/// </summary>
	bool m_isPickaxeImpactBackFlag = false;
	/// <summary>
	/// �^�C�����~�b�g
	/// </summary>
	float m_timeLimit = 0.0f;
	/// <summary>
	/// �c���n�V�̃X�v���C�g
	/// </summary>
	SpriteRender m_pickaxeSprite;
	/// <summary>
	/// �c���n�V�̉�]�X�e�[�g�̕ϐ�\
	/// </summary>
	PickaxeMoveState m_pickaxeMoveState = PickaxeMoveState::en_standby;
	/// <summary>
	/// �c���n�V�̉�]�l
	/// </summary>
	float m_pixkaxeRotValue = 0.0f;
	/// <summary>
	/// �c���n�V�C�[�W���O����
	/// </summary>
	float m_pickaxeEasingRatio = 0.0f;
	/// <summary>
	/// �C�[�W���O�J�n�l
	/// </summary>
	float m_pickaxeRotStartValue = 0.0f;
	/// <summary>
	/// �C�[�W���O�I���l
	/// </summary>
	float m_pickaxeRotEndValue = 0.0f;
	/// <summary>
	/// �c���n�V�C�[�W���O�������ݒ�֐�
	/// </summary>
	/// <param name="picMoveState"></param>
	void PickaxeEasingInit(const PickaxeMoveState picMoveState)
	{
		m_pickaxeMoveState = picMoveState;

		if (picMoveState == PickaxeMoveState::en_standby)
		{
			m_pickaxeRotStartValue = PICKAXE_STANDBY_RATIO_MIN;

			m_pickaxeRotEndValue = PICKAXE_STANDBY_RATIO_MAX;
		}
		else
		{
			m_pickaxeRotStartValue = PICKAXE_IMPACT_RATIO_MIN;

			m_pickaxeRotEndValue = PICKAXE_IMPACT_RATIO_MAX;
		}

		m_pickaxeEasingRatio = 1.0f;
	}

	/// <summary>
	///	�΂̃X�v���C�g
	/// </summary>
	SpriteRender m_rockSprite;
	/// <summary>
	/// �^�C�}�[�̃X�v���C�g
	/// </summary>
	SpriteRender m_timerSprite;
	/// <summary>
	/// �^�C�}�[�̃X�v���C�g�̏���������
	/// </summary>
	void TimerSpriteInit();
	/// <summary>
	/// �^�C�}�[�̃X�v���C�g�̊p�x
	/// </summary>
	float m_degree = 9.45f;
	/// <summary>
	/// �{�^���̃X�v���C�g�̔z��
	/// </summary>
	SpriteRender* m_sprites[COMMAND_MAX];
	/// <summary>
	/// �{�^���̃X�v���C�gY
	/// </summary>
	SpriteRender m_buttonSpriteY;
	/// <summary>
	/// �{�^���̃X�v���C�gB
	/// </summary>
	SpriteRender m_buttonSpriteB;
	/// <summary>
	/// �{�^���̃X�v���C�gA
	/// </summary>
	SpriteRender m_buttonSpriteA;
	/// <summary>
	/// �{�^���̃X�v���C�gX
	/// </summary>
	SpriteRender m_buttonSpriteX;
	/// <summary>
	/// �N���X�^���̃C���X�^���X
	/// </summary>
	Crystal* m_crystal;
	/// <summary>
	/// XYAB�{�^���������ꂽ���ǂ����𔻒肵�āA�������{�^���������ꂽ�A
	/// ������Ȃ��������̏���������֐��A�{�^���������ꂽ��true���A���Ă���
	/// </summary>
	/// <returns></returns>
	bool IsTriggerButton();
	/// <summary>
	/// �������R�}���h�����͂��ꂽ���ǂ����𔻒f����
	/// </summary>
	void IsJudgeingTriggerButton(const CommandTriggerState& initCommand);
	/// <summary>
	/// �Q�[���T�E���h�̃C���X�^���X
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// �Q�[���G�t�F�N�g�̃C���X�^���X
	/// </summary>
	GameEffect* m_gameEffect = nullptr;
	/// <summary>
	/// �v���C���[�̃C���X�^���X
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// �f�o�b�N�p��fontrender
	/// </summary>
	FontRender m_debugFontRender;
	/// <summary>
	/// flaot�p���`���
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}
};

