#pragma once

namespace nsK2EngineLow {
	class DirectionalLight : Noncopyable
	{
	public:
		//コンストラクタ
		DirectionalLight();
		//デストラクタ
		~DirectionalLight();
	private:
		//ディレクションライトの構造体
		SDirectionLight* m_directionLight;
	};
}

