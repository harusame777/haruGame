#pragma once

class GameEffect : public IGameObject
{
public: 
	enum EffectListNum
	{
		//直撃エフェクト
		en_hitEffect,
	};
	/// <summary>
	/// エフェクトを指定して出現させる
	/// </summary>
	/// <param name="listNum"></param>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	void LocalEffectOrder(
		const EffectListNum& listNum,
		const Vector3& pos,
		const Quaternion& rot
	);
	/// <summary>
	/// エフェクトを指定してターゲットAに向けて出現させる
	/// </summary>
	/// <param name="listNum"></param>
	/// <param name="effectPos"></param>
	/// <param name="targetPosA"></param>
	/// <param name="targetPosB"></param>
	void LocalEffectOrder(
		const EffectListNum& listNum,
		const Vector3& effectPos,
		const Vector3& targetPosA
	);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameEffect(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameEffect(){}
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
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);

};

