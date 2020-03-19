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

	ID3D11Texture3D* DensityTexture = nullptr;


	TerrainInstances TerrainInst;
	//XMFLOAT3* WorldPosition = nullptr;

	//TerrainMesh* const GetTerrainDebugMesh() { return &DebugMesh; }

	static void MakeTerrain(Terrain** pOutTerrain, UINT Size);
	void InitializeDebugCells();
};

