#include "RootSig.hlsli"
#include "Structs.hlsli"


[RootSignature(SkyBoxSig)]
VSOutput_SkyBox main(Vertex vert)
{
	VSOutput_SkyBox o;
	o.position = float4(mul(modelMat, float4(vert.position.xyz, 1)).xyz, 1);
	o.texCoord = vert.position;

	o.worldPos = mul(modelMat, float4(vert.position, 1.0f));

	return o;
}