#include<master.hlsli>

cbuffer ChunkBuffer : register(b0)
{
    float3 ChunkPosition = float3(0.0f, 0.0f, 0.0f);
    float Opacity = 1;
}

struct Quad
{
    // Per Vertex
    float4 Position : POSITION;
    float2 UV : TEXCOORD0;
    uint InstanceID : SV_InstanceID;
};

struct Geometry
{
    // Per Vertex
    float4 Position : SV_POSITION;
    float4 WorldSpace : TEXCOORD0;
    float3 ChunkPosition : TEXCOORD1;
    
    uint InstanceID : SV_InstanceID;
};

Geometry QuadVS(Quad Input)
{
    Geometry Output = (Geometry) 0;
    
    Output.Position = Input.Position;
    
    float4 Projection = float4(Input.Position.xy, 0.5f, 1);
    Projection.y *= -1;
    
    float3 Chunk = float3(Input.UV.xy, Input.InstanceID * InvVoxelDimPlusMargins.x);
    
    Chunk.xyz *= VoxelDim.x * InvVoxelDimPlusMarginsMinusOne.x;
    
    float3 ExternalChunk = (Chunk * VoxelDimPlusMargins.x - Margin) * InvVoxelDim.x;
    float3 ws = ChunkPosition + ExternalChunk * ChunkSize;
    
    Output.WorldSpace = float4(ws, 1.0f);
    Output.ChunkPosition = Chunk;
    Output.InstanceID = Input.InstanceID;
    
	return Output;
}