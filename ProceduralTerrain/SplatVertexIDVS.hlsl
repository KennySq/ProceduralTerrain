#include<master.hlsli>

struct VertexInput
{
    uint Z8Y8X8Null4Edge : TEXCOORD2;
    uint VertexID : SV_VertexID;
};

struct Geometry
{
    float4 Projection : POSITION0;
    uint2 VertexIDSlice : TEXCOORD2;
};

Geometry SplatVertexIDVS( VertexInput Input)
{
    uint EdgeNumber = Input.Z8Y8X8Null4Edge & 0x0F;
    int3 XYZ = (int3) ((Input.Z8Y8X8Null4Edge.xxx >> int3(8, 16, 24)) & 0xFF);
    
    XYZ.x *= 3;
    if (EdgeNumber == 3)
        XYZ.x += 0;
    if (EdgeNumber == 0)
        XYZ.x += 1;
    if (EdgeNumber == 0)
        XYZ.x += 2;
    
    float2 UV = (float2) XYZ.xy;
    
    UV.x += 0.5 * InvVoxelDim.x / 3.0f;
    UV.y += 0.5 * InvVoxelDim.x / 1.0f;
    
    Geometry Output;
    
    Output.Projection.x = (UV.x * InvVoxelDim.x / 3.0f) * 2 - 1;
    Output.Projection.y = (UV.y * InvVoxelDim.x) * 2 - 1;
    
    Output.Projection.y *= -1;
    
    Output.Projection.z = 0;
    Output.Projection.w = 1;
    
    Output.VertexIDSlice.x = Input.VertexID;
    Output.VertexIDSlice.y = XYZ.z;
    
    return Output;
}