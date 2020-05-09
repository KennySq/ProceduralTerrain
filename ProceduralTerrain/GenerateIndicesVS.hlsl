struct Vertex
{
    uint Z8Y8X8Case8 : TEXCOORD2;
};

struct Geometry
{
    uint Z8Y8X8Case8 : TEXCOORD2;
};

Geometry GenerateIndicesVS(Vertex Input)
{
    Geometry Output = (Geometry) 0;
    
    Output.Z8Y8X8Case8 = Input.Z8Y8X8Case8;

	return Output;
}