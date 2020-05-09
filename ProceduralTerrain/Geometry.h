#pragma once



#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#ifdef _INDEX16
typedef WORD Index;
#endif

#ifdef _INDEX32
typedef UINT Index;
#endif

using namespace DirectX;
using namespace std;

struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 UV;
};

struct VolumeSliceUV
{
	XMFLOAT2 UV;
};

struct VolumeSliceVertex
{
	XMFLOAT3 Position;
	XMFLOAT2 UV;
};

struct VoxelVertex
{
	XMFLOAT3 Position;
	XMINT4 Idx;
};

struct TerrainInstanceData
{
	XMFLOAT3 WorldPosition; // [64]{3}
	float Density[8];
};

struct PolygonCaseCode
{
	UINT Z8Y8X8Flag;
};


struct TerrainInstances
{
	TerrainInstanceData* Instances = nullptr;
};

struct InputLayout
{
	vector<D3D11_INPUT_ELEMENT_DESC> InputElements;
	ID3D11InputLayout* IL = nullptr;


};

#ifdef _DEFERRED
struct Quad
{

};
#endif

struct Mesh
{
	vector<Vertex> Vertices;
	vector<Index> Indices;

};

template<class _VertTy>
struct CustomMesh
{
	vector<_VertTy> Vertices;
	vector<Index> Indices;

};

struct Shader
{
	ID3D11VertexShader* VS = nullptr;
	ID3D11PixelShader* PS = nullptr;
	ID3D11GeometryShader* GS = nullptr;
	ID3D11ComputeShader* CS = nullptr;
	ID3D11HullShader* HS = nullptr;

	string VSEntry = "VS";
	string PSEntry = "PS";
	string GSEntry = "GS";
	string CSEntry = "CS";
	string HSEntry = "HS";

	string FileName;

	InputLayout InputLayouts;

};

struct Material
{
	Shader* MaterialShader = nullptr;
	string* FileName = &MaterialShader->FileName;

	Material() { MaterialShader = new Shader(); }
};

struct Model
{
	Mesh* ModelMesh = nullptr;
	MeshBuffer* ModelMeshBuffer = nullptr;
	GeometryBuffer* ModelGeoBuffer = nullptr;
};

template<class _VertTy>
struct CustomModel
{
	CustomMesh<_VertTy>* QuadMesh = nullptr;
	MeshBuffer* ModelMeshBuffer = nullptr;
	GeometryBuffer* ModelGeoBuffer = nullptr;
};

void CreateCube(Model** OutModel);
void CreateTerrain(Model** OutModel);
void CreateQuad(CustomModel<VolumeSliceVertex>** QuadModel);

#endif