SamplerState SampleState : register(s0);

cbuffer Matrices : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};

struct Voxel
{
    float4 Position : POSITION;
    float Density : TEXCOORD0;
    
    float3 WorldPosition : TEXCOORD1;
};

struct Vertex
{
    float4 Position : POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD0;
    
    float3 WorldPosition : TEXCOORD1;
    row_major float2x4 Densities : TEXCOORD2;
    
    uint InstanceID : SV_InstanceID;
};

struct Pixel
{
    float4 Projected : SV_POSITION;
    float3 Normal : TEXCOORD0;
    float2 UV : TEXCOORD1;
    row_major float2x4 Density : DENSITY0;
    uint InstanceID : SV_InstanceID;
    
};

Pixel VS(Vertex Input)
{
    Pixel Output = (Pixel) 0;
    
    Input.Position.w = 1.0f;
    
    Input.Position.x = Input.WorldPosition.x;
    Input.Position.y = Input.WorldPosition.y;
    Input.Position.z = Input.WorldPosition.z;
    
	Output.Projected = mul(Input.Position, World);
    
    Output.Projected = mul(Output.Projected, View);
    Output.Projected = mul(Output.Projected, Projection);
    
	Output.Normal = normalize(mul(Input.Normal, World));
    
  //  Output.UV = Input.UV;
    
    Output.Density = Input.Densities;
    
   // Output.InstanceID = Input.InstanceID;
    
    return Output;

}

Pixel VoxelVS(Voxel Input)
{
    Pixel Output = (Pixel) 0;
    
    float4 WorldPos;
    float4 CornerPos;
    
    Input.Position.w = 1.0f;
    
    WorldPos = float4(Input.WorldPosition, 1.0f);
    CornerPos = Input.Position;
    
    WorldPos = float4(WorldPos.xyz + CornerPos.xyz, 1.0f);
    
    Output.Projected = mul(WorldPos, World);
    Output.Projected = mul(Output.Projected, View);
    Output.Projected = mul(Output.Projected, Projection);
    
    
   // Output.InstanceID = Input.InstanceID;
    //Output.Density = Input.Density;
    
    return Output;

}

float4 PS(Pixel Input) : SV_Target0
{
    float4 FinalColor;
    float4 Density;
    
    FinalColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    //switch (Input.InstanceID)
    //{
    //    case 0:
    //        Density = Input.Density[0][0];
    //        break;
    //    case 1:
    //        Density = Input.Density[0][1];
    //        break;
    //    case 2:
    //        Density = Input.Density[0][2];
    //        break;
    //    case 3:
    //        Density = Input.Density[0][3];
    //        break;
        
    //    case 4:
    //        Density = Input.Density[1][0];
    //        break;
    //    case 5:
    //        Density = Input.Density[1][1];
    //        break;
    //    case 6:
    //        Density = Input.Density[1][2];
    //        break;
    //    case 7:
    //        Density = Input.Density[1][3];
    //        break;
    //}
    
    return FinalColor;
}