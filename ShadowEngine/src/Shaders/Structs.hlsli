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

cbuffer PerFrameCb : register(b0)
{
	float4x4 viewProjMat;
	float4x4 rayDir;
	float4 cameraPos;
}

cbuffer PerObjectCb : register(b1) {
	float4x4 modelMat;
    float4x4 modelMatInverse;
}
