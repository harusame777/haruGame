#include "stdafx.h"
#include "CrystalGetCommandSprite.h"
#include "Crystal.h"
#include "GameSound.h"
#include "GameEffect.h"
#include "Player.h"
#include <random>
#include <algorithm>

//�萔��
namespace {
	/// <summary>
	/// �����k���̋���
	/// </summary>
	static const float SHAKE_POWER = 5.0f;
	/// <summary>
	/// �����k���̑���
	/// </summary>
	static const float SHAKE_SPEED = 20.0f;
	/// <summary>
	/// �����T�C�Y
	/// </summary>
	static const float SPRITE_W_SIZE = 150.0f;
	static const float SPRITE_H_SIZE = 150.0f;
	/// <summary>
	/// �c���n�V�X�v���C�g�T�C�Y
	/// </summary>
	static const float PICKAXE_SPRITE_W_SIZE = 200.0f;
	static const float PICKAXE_SPRITE_H_SIZE = 200.0f;
	/// <summary>
	/// ��X�v���C�g�T�C�Y
	/// </summary>
	static const float ROCK_SPRITE_W_SIZE = 600.0f;
	static const float ROCK_SPRITE_H_SIZE = 600.0f;
	/// <summary>
	/// �����̈ʒu
	/// </summary>
	static const Vector3 SPRITE_POSITION = { 0.0f,-250.0f,0.0f };
	/// <summary>
	/// �c���n�V�ʒu
	/// </summary>
	static const Vector3 PICKAXE_POSITION = { -140.0f,-150.0f,0.0f };
	/// <summary>
	/// ��ʒu
	/// </summary>
	static const Vector3 ROCK_POSITION = { 0.0f,-250.0f,0.0f };
	/// <summary>
	/// �擾�����̌v�Z�Ɏg�����
	/// </summary>
	static const float GET_RANGE_CALC = 90.0f;
	/// <summary>
	/// �f�o�b�N�����̈ʒu
	/// </summary>
	static const Vector3 DEBUG_FONT_POSITION = { 0.0f,200.0f,0.0f };
}

//�R���X�g���N�^
CrystalGetCommandSprite::CrystalGetCommandSprite()
{

}

//�f�X�g���N�^
CrystalGetCommandSprite::~CrystalGetCommandSprite()
{

}

//�X�^�[�g�֐�
bool CrystalGetCommandSprite::Start()
{
	//�Q�[���T�E���h�̃C���X�^���X���擾
	m_gameSound = FindGO<GameSound>("gameSound");

	m_gameEffect = FindGO<GameEffect>("gameEffect");

	//�v���C���[�̃C���X�^���X���擾
	m_player = FindGO<Player>("player");

	//�^�C�}�[�̃X�v���C�g�̏�����
	TimerSpriteInit();

	//���o�̃X�v���C�g�̏�����
	//�c���n�V
	m_pickaxeSprite.Init("Assets/modelData/objects/crystal/digital_pickaxe_sprite.DDS", PICKAXE_SPRITE_W_SIZE, PICKAXE_SPRITE_H_SIZE);
	m_pickaxeSprite.SetPivot({ 0.5f,0.0f });
	m_pickaxeSprite.SetPosition(PICKAXE_POSITION);
	//��
	m_rockSprite.Init("Assets/modelData/objects/crystal/digital_rock_sprite.DDS", ROCK_SPRITE_W_SIZE, ROCK_SPRITE_H_SIZE);
	m_rockSprite.SetPosition(ROCK_POSITION);

	//�{�^���̃X�v���C�g�̏�����
	m_buttonSpriteY.Init("Assets/modelData/objects/crystal/CommandSprite_Y.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteY.SetPosition(SPRITE_POSITION);

	m_buttonSpriteB.Init("Assets/modelData/objects/crystal/CommandSprite_B.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteB.SetPosition(SPRITE_POSITION);

	m_buttonSpriteA.Init("Assets/modelData/objects/crystal/CommandSprite_A.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteA.SetPosition(SPRITE_POSITION);

	m_buttonSpriteX.Init("Assets/modelData/objects/crystal/CommandSprite_X.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
	m_buttonSpriteX.SetPosition(SPRITE_POSITION);

	PickaxeEasingInit(PickaxeMoveState::en_standby);

	return true;
}

void CrystalGetCommandSprite::TimerSpriteInit()
{
	//�^�C�}�[�p�̃X�v���C�g�������f�[�^���쐬
	SpriteInitData timerSpriteData;
	//�摜��ݒ�
	timerSpriteData.m_ddsFilePath[0] = "Assets/modelData/objects/crystal/CommandSprite_Timer.DDS";
	//�V�F�[�_�[�t�@�C����ݒ�
	timerSpriteData.m_fxFilePath = "Assets/shader/haruharuCircularGaugeSprite.fx";
	//���[�U�[�g���f�[�^��ݒ�
	timerSpriteData.m_expandConstantBuffer = &m_degree;
	timerSpriteData.m_expandConstantBufferSize = sizeof(m_degree);
	//�䗦��ݒ�
	timerSpriteData.m_width = static_cast<UINT>(SPRITE_W_SIZE);
	timerSpriteData.m_height = static_cast<UINT>(SPRITE_H_SIZE);
	//�u�����h���[�h��ݒ�
	timerSpriteData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//�ݒ肵���f�[�^���X�v���C�g�ɐݒ�
	m_timerSprite.Init(timerSpriteData);

	//�ʒu��ݒ�
	m_timerSprite.SetPosition(SPRITE_POSITION);
}

//�X�v���C�g�̏�����
void CrystalGetCommandSprite::InitSprite()
{

	int nowCommandListNum;
	
	//�R�}���h���X�g��for������
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		//�R�}���h���X�g�̃i���o�[���i�[����
		nowCommandListNum = m_commandList[i];

		//�X�v���C�g�����_�[��ݒ�
		switch (nowCommandListNum)
		{
		case en_isTriggerY:
			m_sprites[i] = &m_buttonSpriteY;
			break;
		case en_isTriggerB:
			m_sprites[i] = &m_buttonSpriteB;
			break;
		case en_isTriggerA:
			m_sprites[i] = &m_buttonSpriteA;
			break;
		case en_isTriggerX:
			m_sprites[i] = &m_buttonSpriteX;
			break;
		}
	}
}

//�A�b�v�f�[�g�֐�
void CrystalGetCommandSprite::Update()
{
	//�R�}���h�̃A�b�v�f�[�g����
	CommandUpdate();
#ifdef _DEBUG 
	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"Command[%01d]",int(m_commandList[m_nowCommandNum]));

	m_debugFontRender.SetPosition(DEBUG_FONT_POSITION);

	m_debugFontRender.SetText(wcsbuf);

	//Quaternion test;

	//m_pixkaxeRotValue += 5.0f;

	//test.AddRotationDegZ(m_pixkaxeRotValue);

	//m_pickaxeSprite.SetRotation(test);

#endif
	//�R���N�g�t���O��true�Ō��݂̃R�}���h��5�ȉ���������
	if (m_isCollectFlag == true)
	{
		//�h���[�R�[��
		m_pickaxeSprite.Update();
		m_rockSprite.Update();
		m_timerSprite.Update();

		if (m_nowCommandNum >= COMMAND_MAX)
			return;
		m_sprites[m_nowCommandNum]->Update();

	}
}

//�����_�[�֐�
void CrystalGetCommandSprite::Render(RenderContext& rc)
{
	//�R���N�g�t���O��true�Ō��݂̃R�}���h��5�ȉ���������
	if (m_isCollectFlag == true)
	{
		m_pickaxeSprite.Draw(rc);
		m_rockSprite.Draw(rc);
		m_timerSprite.Draw(rc);

		if (m_nowCommandNum >= COMMAND_MAX)
			return;
		m_sprites[m_nowCommandNum]->Draw(rc);
	}
#ifdef _DEBUG 
	m_debugFontRender.Draw(rc);
#endif
}

void CrystalGetCommandSprite::CommandUpdate()
{

	//�R���N�g�t���O��false��������
	if (m_isCollectFlag == false)
	{
		//�����͂��Ȃ�
		return;
	}

	//�c���n�V�̃X�v���C�g�X�V����������
	PickaxeSpriteUpdate();

	//�{�^���������������ꂽ���ǂ����̃t���O��������
	m_isCorrectButton = false;

	//�{�^�����͂��ł��Ȃ�������
	if (m_isCommandInput == false)
	{
		//�߂�
		return;
	}

	if (m_nowCommandNum > CommandTriggerState::ButtonNum)
	{
		//�擾�������̏������s��

		//�擾�t���O��false��
		m_isCollectFlag = false;

		m_gameSound->LocalSoundOrder(GameSound::en_breakDigSound, false, 0.5f);

		//�N���X�^���{�̂ɂ��̃N���X�^���͍̎悳�ꂽ�Ɠ`����
		m_crystal->CrystalCollected();

		return;
	}

	//�^�C�����~�b�g������
	m_timeLimit -= g_gameTime->GetFrameDeltaTime();
	
	float t = std::clamp(m_timeLimit / 2.0f, 0.0f, 1.0f);

	m_degree = Leap(0, 9.5, t);


	/*m_degree -= g_gameTime->GetFrameDeltaTime();*/

	//�{�^���������ꂽ���ǂ����𔻒肵�āA�����ꂽ��
	//�R�}���h�����������𔻒肷��
	//�����{�^����������Ă��āA�R�}���h��������������
	if (IsTriggerButton() &&
		m_isCorrectButton == true)
	{
		//commandList�����ɐi�߂�
		m_nowCommandNum++;
	}

	//�����{�^����������Ă��āA�R�}���h���Ԉ���Ă�����A�܂���
	//�^�C�����~�b�g��0�b�ȉ���������
	else if(IsTriggerButton() && m_isCorrectButton == false ||
		m_timeLimit <= 0.0f)
	{
		//�Ԉ���Ă������̏���
		 
		//�̎�t���O���I�t�ɂ���
		m_isCollectFlag = false;

		//�N���X�^���{�̂ɂ��̃N���X�^���̍̎�Ɏ��s�����Ɠ`����
		m_crystal->CollectedFailure();
	}
	else if(IsRangeInPlayer() == false)
	{

		//�̎�t���O���I�t�ɂ���
		m_isCollectFlag = false;

		//�N���X�^���{�̂ɂ��̃N���X�^���̍̎�Ɏ��s�����Ɠ`����
		m_crystal->CollectedFailure();

	}

}

void CrystalGetCommandSprite::CommandMix()
{
	//random���C�u�������g�p���ă����_���Ȓl�𐶐�����
	//�V�[�h����
	std::random_device rd;
	std::mt19937 gen(rd());
	//0����3�܂ł͈̔͂ň�l���z�̐����𐶐�
	std::uniform_int_distribution<> dist(0, 3);

	//�R�}���h�������_���Ɍ��肷��
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		//�����_���Ȑ������
		m_commandList[i] = dist(gen);
	}

	//�X�v���C�g������������
	InitSprite();
}

//XYAB�{�^���������ꂽ���ǂ����𔻒肵�āA�������{�^���������ꂽ�A
// ������Ȃ��������̏���������֐��A�{�^���������ꂽ��true���A���Ă���
bool CrystalGetCommandSprite::IsTriggerButton()
{

	//����Y�{�^���������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		//�����ꂽ�{�^���ɑΉ������{�^���X�e�[�g�𑗂�
		IsJudgeingTriggerButton(CommandTriggerState::en_isTriggerY);
		return true;
	}
	//����B�{�^���������ꂽ��
	else if (g_pad[0]->IsTrigger(enButtonB))
	{
		//�����ꂽ�{�^���ɑΉ������{�^���X�e�[�g�𑗂�
		IsJudgeingTriggerButton(CommandTriggerState::en_isTriggerB);
		return true;
	}
	//����A�{�^���������ꂽ��
	else if (g_pad[0]->IsTrigger(enButtonA))
	{
		//�����ꂽ�{�^���ɑΉ������{�^���X�e�[�g�𑗂�
		IsJudgeingTriggerButton(CommandTriggerState::en_isTriggerA);
		return true;
	}
	//����X�{�^���������ꂽ��
	else if (g_pad[0]->IsTrigger(enButtonX))
	{
		//�����ꂽ�{�^���ɑΉ������{�^���X�e�[�g�𑗂�
		IsJudgeingTriggerButton(CommandTriggerState::en_isTriggerX);
		return true;
	}

	return false;
}

//�������R�}���h�����͂��ꂽ���ǂ����𔻒f����֐�
void CrystalGetCommandSprite::IsJudgeingTriggerButton(const CommandTriggerState& initCommand)
{

	//���͂��ꂽ�R�}���h�i���o�[���擾����
	int initNumber = initCommand;

	//�R�}���h���X�g�̃i���o�[���擾����
	int JudgeNum = m_commandList[m_nowCommandNum];

	//���������i���o�[��������
	if (JudgeNum == initNumber)
	{
		//�������R�}���h�����͂��ꂽ
		PickaxeEasingInit(PickaxeMoveState::en_impact);

		m_gameSound->LocalSoundOrder(GameSound::en_rockDigSound, false, 1.0f);

		m_gameEffect->LocalEffectOrder(
			GameEffect::en_hitEffect
			, m_crystal->GetPosition()
			, m_player->GetPosition()
		);

		m_isCommandInput = false;

		m_isCorrectButton = true;
	}
	else
	{
		//�Ԉ�����R�}���h�����͂��ꂽ
		PickaxeEasingInit(PickaxeMoveState::en_impact);

		m_gameSound->LocalSoundOrder(GameSound::en_hitByIronSound, false, 1.0f);

		m_isCommandInput = false;

		m_isCorrectButton = false;
	}

}

//�c���n�V�̃X�v���C�g�̃A�b�v�f�[�g�֐�
void CrystalGetCommandSprite::PickaxeSpriteUpdate()
{
	//��]�l���쐬
	Quaternion picRot;

	//�C�[�W���O�̒l���擾
	m_pixkaxeRotValue = PickaxeRotEasing(m_pickaxeMoveState);

	//��]�l������
	picRot.SetRotationDegZ(m_pixkaxeRotValue);

	//�`��ύX
	m_pickaxeSprite.SetRotation(picRot);
}

//�c���n�V�̉�]�C�[�W���O�֐�
const float CrystalGetCommandSprite::PickaxeRotEasing(const PickaxeMoveState picMoveState)
{
	//���������炷

	//�ŏI�I�ȉ�]�l
	float finalFloat;
	//����ւ��Ɏg���ϐ�
	float swap = 0.0f;

	if (picMoveState == PickaxeMoveState::en_standby)
	{
		m_pickaxeEasingRatio -= g_gameTime->GetFrameDeltaTime();

		//����������0�ȉ���������
		if (m_pickaxeEasingRatio <= 0.0f)
		{
			//���������āc
			m_pickaxeEasingRatio = 1.0f;
			//����ւ��ď�������
			swap = m_pickaxeRotStartValue;
			m_pickaxeRotStartValue = m_pickaxeRotEndValue;
			m_pickaxeRotEndValue = swap;
		}

	}
	else
	{
		m_pickaxeEasingRatio -= g_gameTime->GetFrameDeltaTime() * 2;

		//����������0�ȉ���������
		if (m_pickaxeEasingRatio <= 0.0f)
		{
			//�����c���n�V�̃X�v���C�g���A���Ă��Ă�����
			if (m_isPickaxeImpactBackFlag == true)
			{
				//0�ŏ��������āc
				m_pickaxeEasingRatio = 0.0f;
				//�t���O��false��
				m_isPickaxeImpactBackFlag = false;
				//�R�}���h����͂ł���悤��
				m_isCommandInput = true;
				//�c���n�V�̃X�v���C�g��ҋ@��Ԃɂ���
				PickaxeEasingInit(PickaxeMoveState::en_standby);
				//���`��Ԃ����l��Ԃ�	
				return finalFloat = Leap(m_pickaxeRotStartValue, m_pickaxeRotEndValue, m_pickaxeEasingRatio);
			}
			//���������āc
			m_pickaxeEasingRatio = 1.0f;

			//����ւ��ď�������
			swap = m_pickaxeRotStartValue;
			m_pickaxeRotStartValue = m_pickaxeRotEndValue;
			m_pickaxeRotEndValue = swap;
			//�c���n�V��Ԃ��悤�ɂ���
			m_isPickaxeImpactBackFlag = true;
		}

	}

	//���`��Ԃ����l��Ԃ�	
	return finalFloat = Leap(m_pickaxeRotStartValue, m_pickaxeRotEndValue, m_pickaxeEasingRatio);
}

const bool& CrystalGetCommandSprite::IsRangeInPlayer()
{
	//�v���C���[�̍��W���擾
	Vector3 playerPos = m_player->GetPosition();

	//�v���C���[�̍��W���玩�g�̍��W��������
	//���g����v���C���[�֐L�т�x�N�g�����v�Z����
	Vector3 diff = playerPos - m_crystal->GetPosition();

	//���g����v���C���[�֐L�т�x�N�g���̂Q����v�Z����
	float range = diff.LengthSq();

	//�����擾�͈͓���������
	if (range <= GET_RANGE_CALC * GET_RANGE_CALC)
	{
		//true��Ԃ�
		return true;
	}

	return false;
}