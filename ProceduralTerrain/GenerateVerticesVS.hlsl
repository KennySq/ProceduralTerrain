#include<master.hlsli>

struct VertexInput
{
    uint Z8Y8X8Null4EdgeNum4 : TEXCOORD2;
};

struct Geometry
{
    float4 WorldSpacePositionAmbient : TEXCOORD1;
    float3 WorldSpaceNormal : NORMAL0;
};

struct Vertex
{
    float4 WorldPositionAmbient : POSITION0;
    float3 WorldNormal : NORMAL0;
};

cbuffer ChunkBuffer
{
    float3 WorldSpaceChunkPosition = float3(0.0f, 0.0f, 0.0f);
    float Opacity = 1.0f;
};

Texture3D DensityVolume;
SamplerState NearestClamp;

Vertex PlaceVertOnEdge(float3 WorldSpace_LL, float3 UVW_LL, int EdgeNum)
{
    Vertex Output = (Vertex) 0;
    
    float Str0 = DensityVolume.SampleLevel(NearestClamp, UVW_LL + InvVoxelDimPlusMarginsMinusOne.xxx * float3(EdgeStart[EdgeNum].xyz), 0).x;
    float Str1 = DensityVolume.SampleLevel(NearestClamp, UVW_LL + InvVoxelDimPlusMarginsMinusOne.xxx * float3(Edge_End[EdgeNum].xyz), 0).x;
    float t = saturate(Str0 / (Str0 - Str1));
    
    float3 PositionWithinCell = float3(EdgeStart[EdgeNum].xyz) + t.xxx * float3(EdgeDirection[EdgeNum].xyz);
    float3 WorldSpacePosition = WorldSpace_LL + PositionWithinCell * VoxelSize.xxx;
    float3 UVW = UVW_LL + PositionWithinCell * InvVoxelDimPlusMarginsMinusOne.xxx;
    
    Output.WorldPositionAmbient.xyz = WorldSpacePosition.xyz;

    return Output;
}

Geometry GenerateVerticesVS(VertexInput Input)
{
    uint3 UnpackedPosition;
    UnpackedPosition.x = (Input.Z8Y8X8Null4EdgeNum4 >> 8) & 0xFF;
    UnpackedPosition.y = (Input.Z8Y8X8Null4EdgeNum4 >> 16) & 0xFF;
    UnpackedPosition.z = (Input.Z8Y8X8Null4EdgeNum4 >> 24) & 0xFF;
    
    float3 ChunkPositionWrite = (float3) UnpackedPosition * InvVoxelDimPlusMarginsMinusOne.xxx;
    float3 ChunkPositionRead = (Margin + VoxelDimMinusOne * ChunkPositionWrite) * InvVoxelDimPlusMarginsMinusOne.xxx;
    
    float3 WorldSpacePosition = WorldSpaceChunkPosition + ChunkPositionWrite * ChunkSize;
    
    float3 UVW = ChunkPositionRead + InvVoxelDimPlusMarginsMinusOne.xxx * 0.25f;
    UVW.xyz *= (VoxelDimPlusMargins.x - 1) * InvVoxelDimPlusMargins.x;
    
    int EdgeNum = (Input.Z8Y8X8Null4EdgeNum4 & 0x0F);
    Vertex V = PlaceVertOnEdge(WorldSpacePosition, UVW, EdgeNum);
    
    Geometry Output;
    
    Output.WorldSpacePositionAmbient = V.WorldPositionAmbient;
    Output.WorldSpaceNormal = 0;
	return Output;
}