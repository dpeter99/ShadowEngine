#include "RootSig.hlsli"
#include "Structs.hlsli"


[RootSignature(RootSig0)]
VSOutput main( Vertex vert )
{
    VSOutput o;
    o.position = float4(vert.position.xyz, 1);
    o.normal = vert.normal;
    o.texCoord = vert.texCoord;
    o.color = vert.color;

	return o;
}