struct GeometryInput
{
    uint Z8Y8X8Null5EdgeFlags3 : TEXCOORD2;
};

struct GeometryOutput
{
    uint Z8Y8X8Null4EdgeNum4 : TEXCOORD2;
};

[maxvertexcount(3)]
void VertexListGS(point GeometryInput Input[1], inout PointStream<GeometryOutput> Stream)
{
    GeometryOutput Output = (GeometryOutput) 0;
	
    uint Z8Y8X8Null8 = Input[0].Z8Y8X8Null5EdgeFlags3 & 0xFFFFFF00;
	
    if (Input[0].Z8Y8X8Null5EdgeFlags3 & 1)
    {
        Output.Z8Y8X8Null4EdgeNum4 = Z8Y8X8Null8 | 3;
        Stream.Append(Output);
    }
    if (Input[0].Z8Y8X8Null5EdgeFlags3 & 2)
    {
        Output.Z8Y8X8Null4EdgeNum4 = Z8Y8X8Null8 | 0;
        Stream.Append(Output);
    }
    if (Input[0].Z8Y8X8Null5EdgeFlags3 & 4)
    {
        Output.Z8Y8X8Null4EdgeNum4 = Z8Y8X8Null8 | 8;
        Stream.Append(Output);
    }
}