#pragma once

struct TerrainMesh
{
	vector<Vertex> Vertices;
	vector<Index> Indices;
};

struct VoxelMesh
{
	vector<VoxelVertex> Vertices;
	vector<Index> Indices;
};

#define MAX_INSTANCE_SIZE 64
#define MAX_INSTANCE_COUNT MAX_INSTANCE_SIZE*MAX_INSTANCE_SIZE*MAX_INSTANCE_SIZE

class Terrain
{
	Cell* Cells = nullptr;

	ID3D11Buffer* MainVB = nullptr, *StreamVB = nullptr;
	ID3D11Buffer* MainIB = nullptr;
	TerrainMesh MainMesh;


	void SubDivideCells();
	void InitializeCells();

	Terrain(UINT Size);
	~Terrain();

public:
	Material* Mat = nullptr;

	UINT Size = 0;
	UINT Capacity = 0;

#ifdef _DEBUG
	ID3D11Buffer* DebugVB = nullptr;
	ID3D11Buffer* DebugIB = nullptr;
	ID3D11Buffer* DebugCB = nullptr;

	ID3D11Buffer* DebugVoxelVB = nullptr;
	ID3D11Buffer* DebugVoxelIB = nullptr;

	ID3D11Buffer* DebugInstanceBuffer = nullptr;


	TerrainMesh DebugMesh;
	VoxelMesh DebugVoxelMesh;
#endif

	ID3D11Buffer* VolumeStreamBuffer = nullptr; // D3D11_BIND_VERTEX_BUFFER
	ID3D11Buffer* VolumeStreamBackBuffer = nullptr; // D3D11_BIND_VERTEX_BUFFER

	ID3D11Buffer* VolumeUVBuffer = nullptr;

	ID3D11Buffer* CaseStreamBuffer = nullptr;

	RenderTarget3D* VolumeTexture = nullptr;
	RenderTarget3D* VertexIDVolume = nullptr;

	D3D11_INPUT_ELEMENT_DESC NoneEmptyCellsInputElement[2];
	ID3D11InputLayout* NoneEmptyCellsIL = nullptr;
	ID3D11VertexShader* NoneEmptyCellsVS = nullptr;
	ID3D11GeometryShader* NoneEmptyCellsGS = nullptr;
	ID3D11Buffer* NoneEmptyCellsSO = nullptr;

	D3D11_INPUT_ELEMENT_DESC VertexListInputElement[1];
	ID3D11InputLayout* VertexListIL = nullptr;
	ID3D11VertexShader* VertexListVS = nullptr;
	ID3D11GeometryShader* VertexListGS = nullptr;
	ID3D11Buffer* VertexListSO = nullptr;

	D3D11_INPUT_ELEMENT_DESC SplatVertexIDInputElement[1];
	ID3D11InputLayout* SplatVertexIDIL = nullptr;
	ID3D11VertexShader* SplatVertexIDVS = nullptr;
	ID3D11GeometryShader* SplatVertexIDGS = nullptr;
	ID3D11PixelShader* SplatVertexIDPS = nullptr;
	ID3D11Buffer* SplatVertexIDSO = nullptr;

	D3D11_INPUT_ELEMENT_DESC GenerateVerticesInputElements[2];
	ID3D11InputLayout* GenerateVerticesIL = nullptr;
	ID3D11VertexShader* GenerateVerticesVS = nullptr;
	ID3D11GeometryShader* GenerateVerticesGS = nullptr;
	ID3D11Buffer* GenerateVerticesSO = nullptr;

	D3D11_INPUT_ELEMENT_DESC GenerateIndicesInputElements[1];
	ID3D11InputLayout* GenerateIndicesIL = nullptr;
	ID3D11VertexShader* GenerateIndicesVS = nullptr;
	ID3D11GeometryShader* GenerateIndicesGS = nullptr;
	ID3D11Buffer* GenerateIndicesSO = nullptr;

	TerrainInstances TerrainInst;

	static void MakeTerrain(Terrain** pOutTerrain, UINT Size);
	void InitializeDebugCells();
};

