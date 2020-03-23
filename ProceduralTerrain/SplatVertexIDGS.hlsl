struct GeometryInput
{
	float4 Projection : POSITION0;
    uint2 VertexIDSlice : TEXCOORD2;
};

struct GeometryOutput
{
    float4 Projection : POSITION0;
    uint VertexID : TEXCOORD2;
    uint RTIndex : SV_RenderTargetArrayIndex;
};

[maxvertexcount(1)]
void SplatVertexIDGS(point GeometryInput Input[1], inout PointStream<GeometryOutput> Stream)
{
    GeometryOutput Output;
    
    Output.Projection = Input[0].Projection;
    Output.VertexID = Input[0].VertexIDSlice.x;
    Output.RTIndex = Input[0].VertexIDSlice.y;
    Stream.Append(Output);

}