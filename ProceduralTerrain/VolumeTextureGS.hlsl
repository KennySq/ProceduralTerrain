struct VSInput
{
    float4 pos : SV_POSITION;
    float4 WorldSpace : TEXCOORD0;
    float3 ChunkPosition : TEXCOORD1;
	
    uint Index : SV_InstanceID;
	
};

struct GSOutput
{
	float4 pos : SV_POSITION;
    float4 WorldSpace : TEXCOORD0;
    float3 ChunkPosition : TEXCOORD1;
	
    uint Index : SV_RenderTargetArrayIndex;
};

[maxvertexcount(3)]
void QuadGS(
	triangle VSInput input[3], 
	inout TriangleStream< GSOutput > output
)
{
	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
		element.pos = input[i].pos;
        element.ChunkPosition = input[i].ChunkPosition;
        element.WorldSpace = input[i].WorldSpace;
        element.Index = input[i].Index;
		
		output.Append(element);
	}
	
  //  output.RestartStrip();

}