#pragma once

class WarriorDataHolder;

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
	/// <summary>
	/// ステートマーカー
	/// </summary>
	struct StateMarker
	{
		/// <summary>
		/// ステートナンバー
		/// </summary>
		int m_warriorTrackingStateNum = 0;
		/// <summary>
		/// スプライトの位置
		/// </summary>
		Vector2 m_spritePosition;
		/// <summary>
		/// ウォリアーの位置
		/// </summary>
		Vector3 m_warriorPosition;
		/// <summary>
		/// マーカーの色
		/// </summary>
		SpriteRender* m_makerColor[4];
	};
	/// <summary>
	/// ステートマーカーの配列
	/// </summary>
	StateMarker m_stateMarkers[3];
	SpriteRender m_grayMarker;
	SpriteRender m_redMarker;
	SpriteRender m_yellowMarker;
	SpriteRender m_greenMarker;
	/// <summary>
	/// ウォリアーの共通データホルダ～
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
};

