// Block 하나의 볼륨을 출력하는 PS 단계.

struct Pixel
{
    // Per Vertex
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};

struct VolumeInstance
{
    float Density : SV_Target0;
};

VolumeInstance QuadPS(Pixel Input)
{
    VolumeInstance Output = (VolumeInstance)0;
    Output.Density = 1.0f;
    
    return Output;
}