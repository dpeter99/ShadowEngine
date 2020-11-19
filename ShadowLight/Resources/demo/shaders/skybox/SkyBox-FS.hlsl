#include "../RootSig.hlsli"
#include "../Structs.hlsli"

cbuffer Mat_Data : register(b2)
{
	float4 tint;
}

TextureCube Mat_Env : register(t0);
SamplerState sampl : register(s0);

[RootSignature(SkyBoxSig)]
float4 main(VSOutput_SkyBox input) : SV_Target
{
	
	float3 viewDir = normalize(cameraPos.xyz - input.worldPos.xyz);
	float4 color = Mat_Env.Sample(sampl, input.texCoord);

	color *= tint;

	return color;
}