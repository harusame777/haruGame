#include "stdafx.h"
#include "CrystalGetCommandSprite.h"
#include "Crystal.h"
#include <random>

//�����L���ɂ���ƃf�o�b�O���[�h�ɂȂ�
#define DEBUG_MODE

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
	/// �R�}���h���X�g�̍ő�l
	/// </summary>
	static const int COMMAND_MAX = 5;
	/// <summary>
	/// �{�^���̍ő�l
	/// </summary>
	static const int BUTTON_MAX = 4;
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
	//�t�@�C���p�X�̃��X�g������������
	m_FilePaths[CommandTriggerState::en_isTriggerY] = "Assets/modelData/objects/crystal/testCommandSprite_Y.DDS";

	m_FilePaths[CommandTriggerState::en_isTriggerB] = "Assets/modelData/objects/crystal/testCommandSprite_B.DDS";

	m_FilePaths[CommandTriggerState::en_isTriggerA] = "Assets/modelData/objects/crystal/testCommandSprite_A.DDS";

	m_FilePaths[CommandTriggerState::en_isTriggerX] = "Assets/modelData/objects/crystal/testCommandSprite_X.DDS";

	return true;
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

		SpriteRender* newSprite = new SpriteRender;

		newSprite->Init(m_FilePaths[nowCommandListNum], 500.0f, 500.0f);

		m_buttonSprites[i]->m_bottonSprite = newSprite;
	}
}

//�A�b�v�f�[�g�֐�
void CrystalGetCommandSprite::Update()
{
	//�R�}���h�̃A�b�v�f�[�g����
	CommandUpdate();
#ifdef DEBUG_MODE
	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"Command[%01d]",int(m_commandList[m_nowCommandNum]));

	m_debugFontRender.SetText(wcsbuf);
#endif

}

//�����_�[�֐�
void CrystalGetCommandSprite::Render(RenderContext& rc)
{
#ifdef DEBUG_MODE
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

	if (m_nowCommandNum > CommandTriggerState::ButtonNum)
	{
		//�擾�������̏������s��
		m_timeLimit = 0.0f;
	}

	//�{�^���������������ꂽ���ǂ����̃t���O��������
	m_isCorrectButton = false;

	//�^�C�����~�b�g������
	m_timeLimit -= g_gameTime->GetFrameDeltaTime();

	//�{�^���������ꂽ���ǂ����𔻒肵�āA�����ꂽ��
	//�R�}���h�����������𔻒肷��
	//�����{�^����������Ă��āA�R�}���h��������������
	if (IsTriggerButton() &&
		m_isCorrectButton == true)
	{
		//�^�C�����~�b�g��������
		m_timeLimit = 2.0f;
		//commandList�����ɐi�߂�
		m_nowCommandNum++;
	}
	//�����{�^����������Ă��āA�R�}���h���Ԉ���Ă�����A�܂���
	//�^�C�����~�b�g��0�b�ȉ���������
	else if(IsTriggerButton() && m_isCorrectButton == false ||
		m_timeLimit <= 0.0f)
	{
		//�Ԉ���Ă������̏���
		m_timeLimit = 0.0f;
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
		m_isCorrectButton = true;
	}
	else
	{
		//�Ԉ�����R�}���h�����͂��ꂽ
		m_isCorrectButton = false;
	}

}
