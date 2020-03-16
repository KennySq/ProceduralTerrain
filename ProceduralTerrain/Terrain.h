#pragma once

struct TerrainMesh
{
	vector<Vertex> Vertices;
	vector<Index> Indices;
};

#define MAX_INSTANCE_SIZE 64
#define MAX_INSTANCE_COUNT MAX_INSTANCE_SIZE*MAX_INSTANCE_SIZE*MAX_INSTANCE_SIZE

class Terrain
{
	Cell*** Cells = nullptr;
	Cell* BlockCells = nullptr;

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

	ID3D11Buffer* DebugInstanceBuffer = nullptr;

	TerrainMesh DebugMesh;
#endif
	XMFLOAT3* WorldPosition = nullptr;

	//TerrainMesh* const GetTerrainDebugMesh() { return &DebugMesh; }

	static void MakeTerrain(Terrain** pOutTerrain, UINT Size);



};
