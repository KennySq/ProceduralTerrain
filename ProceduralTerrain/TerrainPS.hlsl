struct Pixel
{
    float4 Position : SV_Position;
    float3 Normal : TEXCOORD0;
    float2 UV : TEXCOORD1;
};

float4 TerrainPS(Pixel Input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}