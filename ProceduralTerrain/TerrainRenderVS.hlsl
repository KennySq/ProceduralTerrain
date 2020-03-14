cbuffer ConstBuffers : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

struct Vertex
{
    float4 Position : POSITION;
    float3 Normal : NORMAL0;
    float2 UV : TEXCOORD0;
};

struct Pixel
{
    float4 Position : SV_Position;
    float3 Normal : TEXCOORD0;
    float2 UV : TEXCOORD1;
};

Pixel TerrainRenderVS(Vertex Input)
{
    Pixel Output = (Pixel) 0;
    
    Output.Position = mul(Input.Position, World);
    Output.Position = mul(Output.Position, View);
    Output.Position = mul(Output.Position, Projection);
    
    Output.UV = Input.UV;
    
	return Output;
}