struct Vertex
{
    float4 Position : POSITION;
    float3 Normal : NORMAL0;
    float2 UV : TEXCOORD0;
};

struct Geometry
{
    float4 Position : SV_Position;
    float3 Normal : TEXCOORD0;
    float2 UV : TEXCOORD1;
};

Geometry TerrainVS(in Vertex Input )
{
    Geometry Output = (Geometry) 0;
    
    Output.Position = Input.Position;
    Output.Normal = Input.Normal;
    Output.UV = Input.UV;
	
	return Output;
}