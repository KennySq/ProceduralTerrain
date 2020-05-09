#include<master.hlsli>

struct GeometryInput
{
    uint Z8Y8X8Case8 : TEXCOORD2;
};

struct GeometryOutput
{
    uint Index : TEXCOORD2;
};

Texture3D<uint> VertexIDVol;
SamplerState NearestClamp;

[maxvertexcount(15)]
void GenerateIndicesGS(point GeometryInput Input[1], inout TriangleStream<GeometryOutput> Stream )
{
    GeometryOutput Output = (GeometryOutput) 0;
    
    uint CubeCase = (Input[0].Z8Y8X8Case8 & 0xFF);
    uint NumPolys = CaseNumpolys[CubeCase].x;
    int3 XYZ = (int3) ((Input[0].Z8Y8X8Case8.xxx >> uint3(8, 16, 24)) & 0xFF);
    
    if (max(max(XYZ.x, XYZ.y), XYZ.z) >= (uint) VoxelDimMinusOne.x)
    {
        NumPolys = 0;
    }
    
    for (uint i = 0; i < NumPolys;i++)
    {
        int3 EdgeNumsForTriangle = TriangleTable[CubeCase * 5 + i].xyz;
        
        int3 XYZEdge;
        int3 VertexID;
        
        XYZEdge = XYZ + (int3) EdgeStart[EdgeNumsForTriangle.x].xyz;
        XYZEdge.x = XYZEdge.x * 3 + Edge_Axis[EdgeNumsForTriangle.x].x;
        VertexID.x = VertexIDVol.Load(int4(XYZEdge, 0)).x;
        
        XYZEdge = XYZ + (int3) EdgeStart[EdgeNumsForTriangle.y].xyz;
        XYZEdge.x = XYZEdge.x * 3 + Edge_Axis[EdgeNumsForTriangle.y].x;
        VertexID.y = VertexIDVol.Load(int4(XYZEdge, 0)).x;
        
        XYZEdge = XYZ + (int3) EdgeStart[EdgeNumsForTriangle.z].xyz;
        XYZEdge.x = XYZEdge.x * 3 + Edge_Axis[EdgeNumsForTriangle.z].x;
        VertexID.z = VertexIDVol.Load(int4(XYZEdge, 0)).x;
        
        Output.Index = VertexID.x;
        Stream.Append(Output);
        Output.Index = VertexID.y;
        Stream.Append(Output);
        Output.Index = VertexID.z;
        Stream.Append(Output);
        Stream.RestartStrip();

    }
    

}