struct CaseCode
{
    uint Z8Y8X8Case8 : TEXCOORD2;
};

struct Geometry
{
    uint Z8Y8X8Null5EdgeFlags3 : TEXCOORD2;
};

Geometry VertexListVS(CaseCode Input)
{
    Geometry Output = (Geometry) 0;
    
    int CubeCase = (int) (Input.Z8Y8X8Case8 & 0xFF);
    int Bit0 = (CubeCase) & 1;
    int Bit3 = (CubeCase >> 3) & 1;
    int Bit1 = (CubeCase >> 1) & 1;
    int Bit4 = (CubeCase >> 4) & 1;
    int3 BuildVertOnEdge = abs(int3(Bit3, Bit1, Bit4) - Bit0.xxx);
    
    uint Bits = Input.Z8Y8X8Case8 & 0xFFFFFF00;
    
    if (BuildVertOnEdge.x != 0)
        Bits |= 1;
    if (BuildVertOnEdge.y != 0)
        Bits |= 2;
    if (BuildVertOnEdge.z != 0)
        Bits |= 4;
    
    Output.Z8Y8X8Null5EdgeFlags3 = Bits;
    
    return Output;
}