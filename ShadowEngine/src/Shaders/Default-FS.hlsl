#include "RootSig.hlsli"
#include "Structs.hlsli"

cbuffer PerFrameCb : register(b0)
{
	float4x4 viewProjMat;
	float4x4 rayDir;
	float4 cameraPos;
}

cbuffer Shaderdata : register(b0)
{
	float4 tint;
}

[RootSignature(RootSig0)]
float4 main(VSOutput input):SV_Target
{
	return input.color * tint;
}