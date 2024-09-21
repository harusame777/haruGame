#pragma once

namespace nsK2EngineLow {
	class DirectionalLight : Noncopyable
	{
	public:
		//コンストラクタ
		DirectionalLight();
		//デストラクタ
		~DirectionalLight();

		//ライトビュープロジェクションの初期化
		void InitLigVP(const Vector3& basepoint);

		//方向を設定
		void SetDirection(const Vector3& direction)
		{
			m_directionLight->SetDirection(direction);
		}
		void SetDirection(float x, float y, float z)
		{
			m_directionLight->SetDirection({ x,y,z });
		}
		//方向を取得
		const Vector3& GetDirection()
		{
			return m_directionLight->GetDirection();
		}
		//方向を正規化
		void LightDirectionNormalize()
		{
			m_directionLight->LightDirectionNormalize();
		}
		//カラーを設定
		void SetColor(const Vector3& color)
		{
			m_directionLight->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			m_directionLight->SetColor({ r,g,b });
		}
		//カラーを取得
		const Vector3& GetColor() const
		{
			return m_directionLight->GetColor();
		}
		//影をキャストするようにする
		void CastShadow()
		{
			m_directionLight->CastShadow();
		}
		//影をキャストしないようにする
		void UnCastShadow()
		{
			m_directionLight->UnCastShadow();
		}
		//ライトのビュープロジェクションを作成するようにする
		void MakeLVP()
		{
			m_directionLight->MakeLVP();
		}
		//ライトのビュープロジェクションを作成しないようにする
		void UnMakeLVP()
		{
			m_directionLight->UnMakeLVP();
		}

	private:
		//ディレクションライトの構造体
		SDirectionLight* m_directionLight = nullptr;
	};
}

