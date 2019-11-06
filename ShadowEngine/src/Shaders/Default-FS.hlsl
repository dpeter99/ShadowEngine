#include "RootSig.hlsli"
#include "Structs.hlsli"

cbuffer MaterialData : register(b2)
{
	float4 tint;
}

[RootSignature(RootSig0)]
float4 main(VSOutput input) :SV_Target
{
    float4 color = input.color;

	color = color * tint;

	return color;
}