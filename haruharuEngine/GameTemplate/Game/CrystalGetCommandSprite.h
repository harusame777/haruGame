#pragma once

class Crystal;

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
		//�̎�t���O���I���ɂ���
		m_isCollectFlag = true;
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
	/// �R�}���h���X�g
	/// </summary>
	int m_commandList[5];
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
	/// �^�C�����~�b�g
	/// </summary>
	float m_timeLimit = 0.0f;
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
	/// �f�o�b�N�p��fontrender
	/// </summary>
	FontRender m_debugFontRender;
};

