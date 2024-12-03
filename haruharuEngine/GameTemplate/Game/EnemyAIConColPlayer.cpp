#include "stdafx.h"
#include "EnemyAIConColPlayer.h"
#include "Player.h"
#include "EnemyBase.h"

//スタート関数
void EnemyAIConColPlayer::InitData()
{
	m_player = FindGO<Player>("player");
}

//条件実行関数
bool EnemyAIConColPlayer::Execution()
{
	//エネミーのコリジョンを取得する
	const auto& enemyCollision = g_collisionObjectManager->FindCollisionObject("enemy_col");

	//もしエネミーのコリジョンが
	//プレイヤーのキャラコンに衝突したら
	if (enemyCollision->IsHit(m_player->GetCharacterController()))
	{
		return true;
	}

	return false;
}

