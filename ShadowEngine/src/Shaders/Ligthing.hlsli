#include "Structs.hlsli"

float4 CalcDirectionalLight(Light l, float3 normal)
{
	
	return lights[0].ambient + dot(l.dir, normal) * lights[0].diffuse;
}
