#pragma once

/// <summary>
/// エネミーの追跡ステート
/// </summary>
enum WarriorTrackingState
{
	//非追跡状態
	en_nonTracking,
	//後ろから普通に追う
	en_chaseFromBehind,
	//回り込む
	en_wrapAround,
};