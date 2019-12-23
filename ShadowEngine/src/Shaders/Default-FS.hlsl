#include "RootSig.hlsli"
#include "Structs.hlsli"

cbuffer Mat_Data : register(b2)
{
	float4 tint;
    float4 o_color;
}

Texture2D Mat_Tex : register(t0);
TextureCube Mat_Env : register(t1);
SamplerState sampl : register(s0);

[RootSignature(RootSig0)]
float4 main(VSOutput input) :SV_Target
{
	
	/*
	

    float4 diffuse = ObjTexture.Sample( ObjSamplerState, input.TexCoord );

    

    
    
    
    return float4(finalColor, diffuse.a);
	*/
	input.normal = normalize(input.normal);
	
	
    float4 diffuse = Mat_Tex.Sample(sampl, input.texCoord) * tint;

	float3 outputColor;
	
	outputColor = diffuse * lights[0].ambient;
	
	outputColor += saturate(dot(lights[0].dir, input.normal) * lights[0].diffuse * diffuse);

	return float4(outputColor, diffuse.a);
}