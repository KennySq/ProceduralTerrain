// Block �ϳ��� ������ ����ϴ� PS �ܰ�.

struct Pixel
{
    // Per Vertex   
    float4 Position : SV_POSITION;
    float4 WorldSpace : TEXCOORD0;
    float3 ChunkPosition : TEXCOORD1;
   
};

float4 QuadPS(Pixel Input) : SV_TARGET0
{
    float Density = 1.0f;
    
    return Density;
}