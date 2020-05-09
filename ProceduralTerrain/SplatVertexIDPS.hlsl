struct Pixel
{
    float4 Projection : SV_POSITION;
    uint VertexID : TEXCOORD2;
};

uint SplatVertexIDPS(Pixel Input) : SV_TARGET0
{
    return Input.VertexID;
}