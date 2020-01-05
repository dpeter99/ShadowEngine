#include "RootSig.hlsli"
#include "Structs.hlsli"


[RootSignature(SkyBoxSig)]
VSOutput_SkyBox main(Vertex vert)
{
	VSOutput_SkyBox o;

	float4 posW = mul(modelMat, float4(vert.position.xyz, 1));

	o.position = mul(viewProjMat, posW).xyww;
	o.texCoord = vert.position;

	o.worldPos = mul(modelMat, float4(vert.position, 1.0f));

	return o;
}