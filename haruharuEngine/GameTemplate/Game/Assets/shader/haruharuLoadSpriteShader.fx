/*!
 * @brief	画像を表示するためのシェーダー
 */


cbuffer alphaCB : register(b1)
{
    float range;
}

cbuffer cb : register(b0){
    float4x4 mvp;		//MVP行列
    float4 mulColor;	//乗算カラー
};
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
    float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
	
    float distance = length(float2(0.5f, 0.5f) - In.uv);
	
    float affect = 1.0f - 1.0f / range * distance;
		
    affect *= -1.0f;
		
    color.a *= affect;
	
    return color;
}