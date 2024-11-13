#pragma once

class WarriorDataHolder;
class EnemySM_Warrior;

//定数等
namespace {
	/// <summary>
	/// 文字サイズ
	/// </summary>
	static const float SPRITE_W_SIZE = 150.0f;
	static const float SPRITE_H_SIZE = 150.0f;
}

class DebugEnemyTrackingState : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DebugEnemyTrackingState();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~DebugEnemyTrackingState();
	/// <summary>
	/// データ初期化
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
		/// マーカーの色
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
		/// スプライトの位置
		/// </summary>
		Vector2 m_spritePosition;
		/// <summary>
		/// ウォリアーの位置
		/// </summary>
		Vector3 m_warriorPosition;
		/// <summary>
		/// ステートナンバー
		/// </summary>
		int m_warriorTrackingStateNum = 0;
	public:
		void InitColor()
		{	
			//灰色マーカーを設定
			m_grayMarker.m_makerColor.Init("Assets/modelData/debug/testWarriorTrackingStateGray.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
			m_colorList[0] = &m_grayMarker;
			//赤色マーカーを設定
			m_redMarker.m_makerColor.Init("Assets/modelData/debug/testWarriorTrackingStateRed.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
			m_colorList[1] = &m_redMarker;
			//黄色マーカーを設定
			m_yellowMarker.m_makerColor.Init("Assets/modelData/debug/testWarriorTrackingStateYellow.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
			m_colorList[2] = &m_yellowMarker;
			//緑色マーカーを設定
			m_greenMarker.m_makerColor.Init("Assets/modelData/debug/testWarriorTrackingStateGreen.DDS", SPRITE_W_SIZE, SPRITE_H_SIZE);
			m_colorList[3] = &m_greenMarker;
		}
	};
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ドロー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// マーカーの位置を更新する関数
	/// </summary>
	void MarkerPositionUpdate();
	/// <summary>
	/// 描画更新
	/// </summary>
	void SpriteUpdate();
	const bool IsInCamera(EnemyDebugStruct* ptr);
	/// <summary>
	/// ステートマーカー
	/// </summary>
	std::vector<EnemyDebugStruct*> m_enemyDebugSpriteList;
	/// <summary>
	/// ウォリアーの共通データホルダ～
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
};

