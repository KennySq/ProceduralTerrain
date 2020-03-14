cbuffer ConstBuffers : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

cbuffer TerrainBuffers : register(b1)
{
    float TerrainLength;
    float3 Padding;
};

struct GSOutput
{
    float4 Position : SV_Position;
    float3 Normal : TEXCOORD0;
    float2 UV : TEXCOORD1;
};

// 한번에 전달 가능한 양은 최대 1024 byte
[maxvertexcount(64)]
void TerrainGS(point GSOutput input[1], inout TriangleStream< GSOutput > output)
{
    GSOutput element;
    float3 Start = float3(0.0f, 0.0f, 0.0f);
    uint Size = (uint)TerrainLength;

    float3 NewStart = Start;
    float3 Tripoints[4];
    float UVOffset = 1.0f / Size;
    
    element.Normal = input[0].Normal;
    
    for (uint YIndex = 0; YIndex < Size; YIndex++)
    {
        for (uint XIndex = 0; XIndex < Size; XIndex++)
        {
            NewStart = float3(Start.x + XIndex, 0.0f, Start.z + YIndex);
            Tripoints[0] = NewStart;
    
            Tripoints[1] = NewStart;
            Tripoints[1].x += 1.0f;
    
            Tripoints[2] = NewStart;
            Tripoints[2].z += 1.0f;
    
            Tripoints[3] = NewStart;
            Tripoints[3].x += 1.0f;
            Tripoints[3].z += 1.0f;
    
            element.Position = float4(Tripoints[2].xyz, 1.0f);
            element.UV.x = UVOffset * XIndex;
            element.UV.y = UVOffset * (YIndex + 1);
            

            output.Append(element);
            
            element.Position = float4(Tripoints[1].xyz, 1.0f);
            element.UV.x = UVOffset * (XIndex + 1);
            element.UV.y = UVOffset * YIndex;
            output.Append(element);
            
            element.Position = float4(Tripoints[0].xyz, 1.0f);
            element.UV.x = UVOffset * XIndex;
            element.UV.y = UVOffset * YIndex;
            output.Append(element);
            
            output.RestartStrip();
           
            element.Position = float4(Tripoints[3].xyz, 1.0f);
            element.UV.x = UVOffset * (XIndex + 1);
            element.UV.y = UVOffset * YIndex;

            output.Append(element);
            element.Position = float4(Tripoints[2].xyz, 1.0f);
            element.UV.x = UVOffset * XIndex;
            element.UV.y = UVOffset * (YIndex + 1);
            output.Append(element);
            element.Position = float4(Tripoints[1].xyz, 1.0f);
            element.UV.x = UVOffset * (XIndex + 1);
            element.UV.y = UVOffset * (YIndex + 1);
            output.Append(element);
            output.RestartStrip();
        
        }
    }
	
}