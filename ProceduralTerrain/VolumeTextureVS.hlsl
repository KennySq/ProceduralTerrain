struct Quad
{
    // Per Vertex
    float4 Position : POSITION;
    float2 UV : TEXCOORD0;
   
};

struct Pixel
{
    // Per Vertex
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};

Pixel QuadVS( Quad Input)
{
    Pixel Output = (Pixel) 0;
    
    Output.Position = Input.Position;
    Output.UV = Input.UV;
    
	return Output;
}