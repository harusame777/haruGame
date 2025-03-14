/*!
 * @brief	画像を表示するためのシェーダー
 */

cbuffer cb : register(b0){
    float4x4 mvp;		//MVP行列
    float4 mulColor;	//乗算カラー
};

//追加した角度のレジスタ
cbuffer degreeCb : register(b1)
{
    float degree;
}

struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0); // カラーテクスチャ
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
    float PI = 3.14159f;
	
	//中心点
    float2 center = { 0.5f, 0.5f };
	//上方向
    float2 up = { 0.5f, 1.0f };
	
    float2 vector1 = { 0.0f, -1.0f };
	
    float2 vector2 = In.uv - center;
    vector1 = normalize(vector1);
    vector2 = normalize(vector2);
	
    float Deg = acos(dot(vector1, vector2));
	
    Deg = abs(Deg);
	
	//中心からピクセルの座標へのベクトルと中心から上方向へのベクトルの内積を求め
	//逆コサインをとり、設定した角度より小さければ表示、大きければピクセルを破棄する
	if(vector2.x < vector1.x)
    {
        Deg = PI + (PI - Deg);
    }
	
	if(Deg >= degree)
    {
		//ピクセルを破棄
        clip(-1);
    }
	
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
}