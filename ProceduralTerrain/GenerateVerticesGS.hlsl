struct GeometryInput
{
    float4 WorldSpacePosition : TEXCOORD1;
    float3 WorldSpaceNormal : NORMAL0;
};

struct GeometryOutput
{
    float4 WorldPosition : SV_Position;
    float4 WorldNormal : TEXCOORD0;
};

[maxvertexcount(1)]
void GenerateVerticesGS(
	point GeometryInput Input[1], 
	inout PointStream< GeometryOutput > Stream
)
{
    GeometryOutput Output = (GeometryOutput) 0;
    
    Output.WorldPosition = Input[0].WorldSpacePosition;
    Output.WorldNormal = float4(Input[0].WorldSpaceNormal, 0);
    Stream.Append(Output);

}