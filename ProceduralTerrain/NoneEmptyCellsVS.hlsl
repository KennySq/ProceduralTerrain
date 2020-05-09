#include<master.hlsli>
struct Vertex
{
    float2 UV : POSITION0;
    uint InstanceID : SV_InstanceID;
};

struct Geometry
{
    uint Z8Y8X8Case : TEXCOORD2;
};

cbuffer ChunkBuffer
{
    float3 WorldChunkPosition = float3(0.0f, 0.0f, 0.0f);
    float Opacity = 1;
};

Texture3D DensityVolume0;
SamplerState LinearClamp;
SamplerState NearestClamp;

Geometry NoneEmptyCellsVS(Vertex Input)
{
    Geometry Output = (Geometry) 0;
	
    int Inst = Input.InstanceID;
    
    float2 UVRead = float2((Input.UV.x * VoxelDimMinusOne + Margin) * InvVoxelDimPlusMarginsMinusOne.x, (Input.UV.y * VoxelDimMinusOne + Margin) * InvVoxelDimPlusMarginsMinusOne.x);
    float2 UVWrite = float2(Input.UV.x, Input.UV.y);

    float3 ChunkPositionRead = float3(UVRead.x, UVRead.y, (Input.InstanceID + Margin) * InvVoxelDimPlusMargins.x);
    float3 ChunkPositionWrite = float3(UVWrite.x, UVWrite.y, Input.InstanceID * InvVoxelDim.x);
    
    float3 WorldSpace = WorldChunkPosition + ChunkPositionWrite * ChunkSize;
    
    float3 uvw = ChunkPositionRead + InvVoxelDimPlusMarginsMinusOne.xxx * 0.125f;
    
    uvw.xy *= ((VoxelDimPlusMargins.x - 1) * InvVoxelDimPlusMargins.x).xx;
    
    float4 Field0123;
    float4 Field4567;
    
    Field0123.x = DensityVolume0.SampleLevel(NearestClamp, uvw + InvVoxelDimPlusMarginsMinusOne.yyy, 0).x;
    Field0123.y = DensityVolume0.SampleLevel(NearestClamp, uvw + InvVoxelDimPlusMarginsMinusOne.yxy, 0).x;
    Field0123.z = DensityVolume0.SampleLevel(NearestClamp, uvw + InvVoxelDimPlusMarginsMinusOne.xxy, 0).x;
    Field0123.w = DensityVolume0.SampleLevel(NearestClamp, uvw + InvVoxelDimPlusMarginsMinusOne.xyy, 0).x;
    
    Field4567.x = DensityVolume0.SampleLevel(NearestClamp, uvw + InvVoxelDimPlusMarginsMinusOne.yxy, 0).x;
    Field4567.y = DensityVolume0.SampleLevel(NearestClamp, uvw + InvVoxelDimPlusMarginsMinusOne.yxx, 0).x;
    Field4567.z = DensityVolume0.SampleLevel(NearestClamp, uvw + InvVoxelDimPlusMarginsMinusOne.xxx, 0).x;
    Field4567.w = DensityVolume0.SampleLevel(NearestClamp, uvw + InvVoxelDimPlusMarginsMinusOne.xyx, 0).x;
    
    uint4 i0123 = (uint4) saturate(Field0123*99999);
    uint4 i4567 = (uint4) saturate(Field4567*99999);
    int CubeCase = (i0123.x) | (i0123.y << 1) | (i0123.z << 2) | (i0123.w << 3) |
                   (i4567.x << 4) | (i4567.y << 5) | (i4567.z << 6) | (i4567.w << 7);
    
    uint3 Uint3Position = uint3(UVWrite.xy * VoxelDimMinusOne.xx, Input.InstanceID);
    
    Output.Z8Y8X8Case = (Uint3Position.z << 24) |
                        (Uint3Position.y << 16) |
                        (Uint3Position.x << 8) |
                        (CubeCase);
    
    return Output;
}