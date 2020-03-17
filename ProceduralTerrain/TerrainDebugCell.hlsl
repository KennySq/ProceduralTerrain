struct GSOutput
{
    float4 Position : SV_POSITION;
    float Density : TEXCOORD2;
    float3 Normal : TEXCOORD0;
    float2 UV : TEXCOORD1;
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

struct Geometry
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD0;
};

Geometry AdvanceVS(Vertex Input)
{
    Geometry Output = (Geometry) 0;
    
    Input.Position = float4(Input.WorldPosition.xyz, 1.0f);
    
    
    Output.Position = Input.Position;
    Output.Normal = Input.Normal;
    Output.UV = Input.UV;
    
    return Output;
}

const float3 Directions[8] =
{
    { -1.0f, 1.0f, 1.0f }, // -++
    { 1.0f, 1.0f, 1.0f }, // +++
    { 1.0f, 1.0f, -1.0f }, // ++-
    { -1.0f, 1.0f, -1.0f }, // -+-
    { -1.0f, -1.0f, 1.0f }, // --+
    { 1.0f, -1.0f, 1.0f }, // +-+
    { 1.0f, -1.0f, -1.0f }, // +--
    { -1.0f, -1.0f, -1.0f }, // ---
    
};
/*
상단
+++
-+-
++-

+++
-++
-+-

하단

+-+
---
+--

+-+
--+
---

전면
++-
---
+--

++-
-+-
---

후면
+++
+-+
-++

+-+
--+
-++

좌측면
-+-
-++
---

-++
--+
---

우측면
+++
++-
+-+

++-
+--
+-+
*/
[maxvertexcount(36)]
void MakeDebugVoxelGS(
	point Geometry input[1], 
	inout TriangleStream< GSOutput > output
)
{
    GSOutput element;
    
    // 상단
    element.Position = float4(input[0].Position.xyz + Directions[1], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[3], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[2], 1.0f);
    output.Append(element);
    output.RestartStrip();
    
    //-----------------------------/
    element.Position = float4(input[0].Position.xyz + Directions[1], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[0], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[3], 1.0f);
    output.Append(element);
    output.RestartStrip();
    
    
    // 하단
    element.Position = float4(input[0].Position.xyz + Directions[5], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[7], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[6], 1.0f);
    output.Append(element);
    output.RestartStrip();
    //------------------------------------//
    element.Position = float4(input[0].Position.xyz + Directions[5], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[4], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[7], 1.0f);
    output.Append(element);
    output.RestartStrip();
    
    
    // 전면
    element.Position = float4(input[0].Position.xyz + Directions[2], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[7], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[6], 1.0f);
    output.Append(element);
    output.RestartStrip();
    //------------------------------------//
    element.Position = float4(input[0].Position.xyz + Directions[2], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[3], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[7], 1.0f);
    output.Append(element);
    output.RestartStrip();
    
    // 후면
    element.Position = float4(input[0].Position.xyz + Directions[1], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[5], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[0], 1.0f);
    output.Append(element);
    output.RestartStrip();
    //------------------------------------//
    element.Position = float4(input[0].Position.xyz + Directions[5], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[4], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[0], 1.0f);
    output.Append(element);
    output.RestartStrip();
    
    // 좌측면
    element.Position = float4(input[0].Position.xyz + Directions[3], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[0], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[7], 1.0f);
    output.Append(element);
    output.RestartStrip();
    //------------------------------------//
    element.Position = float4(input[0].Position.xyz + Directions[0], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[4], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[7], 1.0f);
    output.Append(element);
    output.RestartStrip();
    
    // 우측면
    element.Position = float4(input[0].Position.xyz + Directions[1], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[2], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[5], 1.0f);
    output.Append(element);
    output.RestartStrip();
    //------------------------------------//
    element.Position = float4(input[0].Position.xyz + Directions[2], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[6], 1.0f);
    output.Append(element);
    element.Position = float4(input[0].Position.xyz + Directions[5], 1.0f);
    output.Append(element);
    output.RestartStrip();
}

/*
우측면
+++
++-
+-+

++-
+--
+-+
*/

/*
const float3 Directions[8] =
{
    { -1.0f, 1.0f, 1.0f }, // -++
    { 1.0f, 1.0f, 1.0f }, // +++
    { 1.0f, 1.0f, -1.0f }, // ++-
    { -1.0f, 1.0f, -1.0f }, // -+-

    { -1.0f, -1.0f, 1.0f }, // --+
    { 1.0f, -1.0f, 1.0f }, // +-+
    { 1.0f, -1.0f, -1.0f }, // +--
    { -1.0f, -1.0f, -1.0f }, // ---
    
};
*/