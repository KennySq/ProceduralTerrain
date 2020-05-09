struct GeometryInput
{
    uint Z8Y8X8Case : TEXCOORD2;
};

struct GeometryOutput
{
    uint Z8Y8X8Case : TEXCOORD2;
};

[maxvertexcount(1)]
void NoneEmptyCellsGS(
	point GeometryInput Input[1], 
	inout PointStream< GeometryOutput> Stream
)
{
    uint CubeCase = (Input[0].Z8Y8X8Case & 0xFF);
    if (CubeCase * (255 - CubeCase) > 0)
    {
        GeometryOutput Output;
        
        Output.Z8Y8X8Case = Input[0].Z8Y8X8Case;
        Stream.Append(Output);

    }

}