#include "RootSig.hlsl"

[RootSignature(RootSig0)]
float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}