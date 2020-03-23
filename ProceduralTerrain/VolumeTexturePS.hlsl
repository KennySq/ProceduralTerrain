// Block 하나의 볼륨을 출력하는 PS 단계.

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