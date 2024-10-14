#include "stdafx.h"
#include "EnemyAIConColPlayer.h"
#include "Player.h"
#include "EnemyBase.h"

//スタート関数
void EnemyAIConColPlayer::Start()
{
	m_player = FindGO<Player>("player");
}

//条件実行関数
bool EnemyAIConColPlayer::Execution()
{

}

