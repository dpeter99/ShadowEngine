#include "RootSig.hlsli"
#include "Structs.hlsli"

[RootSignature(RootSig0)]
float4 main(VSOutput input):SV_Target
{
	return input.color;
}