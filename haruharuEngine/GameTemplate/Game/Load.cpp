#include "stdafx.h"
#include "Load.h"

//�萔��
namespace 
{
	static const float LOADBACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float LOADBACKSIDE_SPRITE_H_SIZE = 900.0f;

}

//�X�^�[�g�֐�
bool Load::Start()
{
	SpriteInitData loadBackSideInitData;

	//�摜��ݒ�
	loadBackSideInitData.m_ddsFilePath[0] = "Assets/modelData/load/game_load_sprite_1.DDS";
	//�V�F�[�_�[�t�@�C����ݒ�
	loadBackSideInitData.m_fxFilePath = "Assets/shader/haruharuLoadSpriteShader.fx";
	//���[�U�[�g���f�[�^��ݒ�
	loadBackSideInitData.m_expandConstantBuffer = &m_loadRange;
	loadBackSideInitData.m_expandConstantBufferSize = sizeof(m_loadRange);
	//�䗦��ݒ�
	loadBackSideInitData.m_width = static_cast<UINT>(LOADBACKSIDE_SPRITE_W_SIZE);
	loadBackSideInitData.m_height = static_cast<UINT>(LOADBACKSIDE_SPRITE_H_SIZE);
	//�u�����h���[�h��ݒ�
	loadBackSideInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//�ݒ肵���f�[�^���X�v���C�g�ɐݒ�
	m_loadBackSideSprite.Init(loadBackSideInitData);

	return true;
}

//�A�b�v�f�[�g�֐�
void Load::Update()
{
	m_loadRange = 0.4;

	//if (m_loadRange > 1.0f)
	//{
	//	m_loadRange = 0.0f;
	//}

	m_loadBackSideSprite.Update();
}

//�����_�[�֐�
void Load::Render(RenderContext& rc)
{
	m_loadBackSideSprite.Draw(rc);
}