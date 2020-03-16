struct GSOutput
{
    float4 Position : SV_POSITION;
    float3 Normal : TEXCOORD0;
    float2 UV : TEXCOORD1;
};

struct Vertex
{
    float4 Position : POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD0;
    float3 WorldPosition : TEXCOORD1;
    uint InstanceID : SV_InstanceID;
};

struct Geometry
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD0;
};

Geometry AdvanceVS(Vertex Input)
{
    Geometry Output = (Geometry) 0;
    
    Input.Position = float4(Input.WorldPosition.xyz, 1.0f);
    Output.Position = Input.Position;
    Output.Normal = Input.Normal;
    Output.UV = Input.UV;
    
    return Output;
}

const float3 Directions[8]
{
    float3()  
};

[maxvertexcount(24)]
void main(
	point Geometry input[1], 
	inout TriangleStream< GSOutput > output
)
{
	for (uint i = 0; i < 24; i++)
	{
		GSOutput element;
		element.Position = input[i];
		output.Append(element);
	}
}