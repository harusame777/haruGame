#pragma once
#include "physics/PhysicsGhostObject.h"

namespace nsK2EngineLow {

	//他のコリジョンと当たり判定を行うクラス
	class CollisionObject : public IGameObject
	{
	public:
		//コンストラクタ
		CollisionObject();
		//デストラクタ
		~CollisionObject();
		//スタート関数
		bool Start();
		//アップデート関数
		void Update();

		/// <summary>
		/// ボックス形状のゴーストオブジェクトを作成
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="size"></param>
		void CreateBox(Vector3 pos, Quaternion rot, Vector3 size)
		{
			m_psysicsGhostObject.CreateBox(pos, rot, size);
		}
		/// <summary>
		/// カプセル形状のゴーストオブジェクトを作成
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="radius"></param>
		/// <param name="height"></param>
		void CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height)
		{
			m_psysicsGhostObject.CreateCapsule(pos, rot, radius, height);
		}
		/// <summary>
		/// 球形状のゴーストオブジェクトを作成
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="radius"></param>
		void CreateSphere(Vector3 pos, Quaternion rot, float radius)
		{
			m_psysicsGhostObject.CreateSphere(pos, rot, radius);
		}
		/// <summary>
		/// メッシュ形状のゴーストオブジェクトを作成
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="model"></param>
		/// <param name="worldMatrix"></param>
		void CreateMesh(Vector3 pos, Quaternion rot, const Model& model, const Matrix& worldMatrix)
		{
			m_psysicsGhostObject.CreateMesh(pos, rot, model, worldMatrix);
		}
		/// <summary>
		/// 設定した時間(秒)が経過すると自動で削除されます。0.0fを設定したら1フレーム経過で削除されます。
		/// </summary>
		/// <param name="timeLimit"></param>
		void SetTimeLimit(const float timeLimit)
		{
			m_timeLimit = timeLimit;
		}
		/// <summary>
		/// 名前を設定
		/// </summary>
		/// <param name="name"></param>
		void SetName(const char* name)
		{
			m_name = name;
		}
		/// <summary>
		/// 名前を取得
		/// </summary>
		/// <returns></returns>
		const char* GetName() const
		{
			return m_name;
		}
		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_psysicsGhostObject.SetPosition(position);
		}
		/// <summary>
		/// 回転を設定
		/// </summary>
		/// <param name="rotation"></param>
		void SetRotation(const Quaternion& rotation)
		{
			m_psysicsGhostObject.SetRotation(rotation);
		}
		/// <summary>
		/// 行列を設定
		/// </summary>
		/// <param name="matrix"></param>
		void SetWorldMatrix(const Matrix& matrix)
		{
			Vector3 position;
			position.x = matrix.m[3][0];
			position.y = matrix.m[3][1];
			position.z = matrix.m[3][2];
			SetPosition(position);
			Quaternion rotation;
			rotation.SetRotation(matrix);
			SetRotation(rotation);
		}
		/// <summary>
		/// 自動で削除するかどうかを設定する。
		/// </summary>
		/// <param name="isFlag"></param>
		void SetIsEnableAutoDelete(bool isFlag)
		{
			m_isEnableAutoDelete = isFlag;
		}
		/// <summary>
		/// コリジョンオブジェクトとキャラコンの当たり判定。
		/// </summary>
		/// <param name="characterController"></param>
		/// <returns></returns>
		const bool IsHit(CharacterController& characterController) const
		{
			bool isCollision = false;
			PhysicsWorld::GetInstance()->ContactTest(characterController, [&](const btCollisionObject& contactObject) {
				if (m_psysicsGhostObject.IsSelf(contactObject) == true) {
					isCollision = true;
				}
				});
			return isCollision;
		}
		/// <summary>
		/// ゴーストオブジェクトを取得
		/// </summary>
		/// <returns></returns>
		PhysicsGhostObject& GetGhostObject()
		{
			return m_psysicsGhostObject;
		}
		/// <summary>
		/// btコリジョンオブジェクトを取得
		/// </summary>
		/// <returns></returns>
		btCollisionObject& GetCollisionObject()
		{
			return m_psysicsGhostObject.GetbtCollisionObject();
		}
		/// <summary>
		/// あたり判定が有効かどうか設定する
		/// </summary>
		/// <param name="isEnable"></param>
		void SetIsEnable(bool isEnable)
		{
			m_isEnable = isEnable;
		}
		/// <summary>
		/// あたり判定が有効かどうかを調べる
		/// </summary>
		/// <returns></returns>
		const bool IsEnable() const
		{
			return m_isEnable;
		}

	private:
		PhysicsGhostObject		m_psysicsGhostObject;	//ゴーストオブジェクト
		const char*				m_name = nullptr;		//名前
		float					m_timer = 0.0f;			//タイマー
		float					m_timeLimit = 0.0f;		//削除されるまでの時間
		bool					m_isEnableAutoDelete;	//自動で削除されるならtrue
		bool					m_isEnable = true;		//trueならあたり判定有効
	};

	class CollisionObjectManager
	{
	public:
		CollisionObjectManager();
		~CollisionObjectManager();
		/// <summary>
		/// コリジョンオブジェクトを追加
		/// </summary>
		/// <param name="collisionObject"></param>
		void AddCollisionObject(CollisionObject* collisionObject)
		{
			m_collisionObjectVector.push_back(collisionObject);
		}
	private:
		std::vector<CollisionObject*> m_collisionObjectVector;
		std::vector<CollisionObject*> m_findsCollisionObjectVector;
		std::vector<CollisionObject*> m_findMatchForwardNameCollisionObjectVector;
	};
}
