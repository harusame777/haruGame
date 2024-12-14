#include "stdafx.h"
#include "Load.h"

//定数等
namespace 
{
	static const float LOADBACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float LOADBACKSIDE_SPRITE_H_SIZE = 900.0f;

}

//スタート関数
bool Load::Start()
{
	SpriteInitData loadBackSideInitData;

	//画像を設定
	loadBackSideInitData.m_ddsFilePath[0] = "Assets/modelData/load/game_load_sprite_1.DDS";
	//シェーダーファイルを設定
	loadBackSideInitData.m_fxFilePath = "Assets/shader/haruharuLoadSpriteShader.fx";
	//ユーザー拡張データを設定
	loadBackSideInitData.m_expandConstantBuffer = &m_loadRange;
	loadBackSideInitData.m_expandConstantBufferSize = sizeof(m_loadRange);
	//比率を設定
	loadBackSideInitData.m_width = static_cast<UINT>(LOADBACKSIDE_SPRITE_W_SIZE);
	loadBackSideInitData.m_height = static_cast<UINT>(LOADBACKSIDE_SPRITE_H_SIZE);
	//ブレンドモードを設定
	loadBackSideInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//設定したデータをスプライトに設定
	m_loadBackSideSprite.Init(loadBackSideInitData);

	return true;
}

//アップデート関数
void Load::Update()
{
	m_loadRange = 0.4;

	//if (m_loadRange > 1.0f)
	//{
	//	m_loadRange = 0.0f;
	//}

	m_loadBackSideSprite.Update();
}

//レンダー関数
void Load::Render(RenderContext& rc)
{
	m_loadBackSideSprite.Draw(rc);
}