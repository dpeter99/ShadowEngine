#include "RootSig.hlsli"
#include "Structs.hlsli"

cbuffer MaterialData : register(b2)
{
	float4 tint;
    float4 o_color;
}

Texture2D txt : register(t0);
SamplerState sampl : register(s0);

[RootSignature(RootSig0)]
float4 main(VSOutput input) :SV_Target
{
    float4 color = float4(1,1, 1, 1);

	color *= tint;

	return tint;
}