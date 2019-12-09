#include "RootSig.hlsli"
#include "Structs.hlsli"

cbuffer Mat_Data : register(b2)
{
	float4 tint;
    float4 o_color;
}

Texture2D Mat_Tex : register(t0);
SamplerState sampl : register(s0);

[RootSignature(RootSig0)]
float4 main(VSOutput input) :SV_Target
{
    float4 color = Mat_Tex.Sample(sampl, input.texCoord);

	color *= tint;

	return color;
}