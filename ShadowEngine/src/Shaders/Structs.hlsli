#ifndef __STRUCTS_HLSL__
#define __STRUCTS_HLSL__

struct Vertex
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float4 color : COLOR;
};

struct VSOutput
{
    float4 position : SV_Position;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float4 color : COLOR;

    float4 worldPos : WORLD;
};

struct VSOutput_SkyBox
{
	float4 position : SV_Position;
	float3 texCoord : TEXCOORD;
	float4 worldPos : WORLD;
};

struct Light
{
	uint type; float3 pos;
	float4 dir;
	float4 ambient;
	float4 diffuse;
	float3 att; float range;
};

cbuffer PerFrameCb : register(b0)
{
	float4x4 viewProjMat;
	float4x4 rayDir;
	float4 cameraPos;
    
	Light lights[5];
}

cbuffer PerObjectCb : register(b1) {
	float4x4 modelMat;
    float4x4 modelMatInverse;
}

#endif // __STRUCTS_HLSL__