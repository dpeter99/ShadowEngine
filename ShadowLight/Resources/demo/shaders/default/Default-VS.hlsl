#include "../RootSig.hlsli"
#include "../Structs.hlsli"


[RootSignature(RootSig0)]
VSOutput main( Vertex vert )
{
    VSOutput o;
    o.position = mul(viewProjMat, mul(modelMat, float4(vert.position.xyz, 1)));
    o.normal = vert.normal;
    o.texCoord = vert.texCoord;
    o.color = vert.color;

    o.worldPos = mul(modelMat, float4(vert.position, 1.0f));

	return o;
}