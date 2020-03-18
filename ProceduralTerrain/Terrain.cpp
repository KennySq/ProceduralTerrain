#include "stdafx.h"
#include "Terrain.h"

void Terrain::MakeTerrain(Terrain** pOutTerrain, UINT Size)
{
	*pOutTerrain = new Terrain(Size);
	pOutTerrain[0]->InitializeCells();
	pOutTerrain[0]->InitializeDebugCells();
	//pOutTerrain[0]->SubDivideCells();
}

void Terrain::InitializeDebugCells()
{
	
	DebugVoxelMesh.Vertices.resize(8);

	VoxelVertex V;

	UINT Index = 0;
	XMFLOAT3 Pos[8] = { 
			{ -1.0f, 1.0f, 1.0f }, // -++
		{ 1.0f, 1.0f, 1.0f }, // +++
		{ 1.0f, 1.0f, -1.0f }, // ++-
		{ -1.0f, 1.0f, -1.0f }, // -+-
		{ -1.0f, -1.0f, 1.0f }, // --+
		{ 1.0f, -1.0f, 1.0f }, // +-+
		{ 1.0f, -1.0f, -1.0f }, // +--
		{ -1.0f, -1.0f, -1.0f }, // ---
	};

	V.Position = Pos[0];
	DebugVoxelMesh.Vertices[0] = V;

	V.Position = Pos[1];
	DebugVoxelMesh.Vertices[1] = V;


	V.Position = Pos[2];
	DebugVoxelMesh.Vertices[2] = V;


	V.Position = Pos[3];
	DebugVoxelMesh.Vertices[3] = V;


	V.Position = Pos[4];
	DebugVoxelMesh.Vertices[4] = V;

	V.Position = Pos[5];
	DebugVoxelMesh.Vertices[5] = V;


	V.Position = Pos[6];
	DebugVoxelMesh.Vertices[6] = V;


	V.Position = Pos[7];
	DebugVoxelMesh.Vertices[7] = V;

	DebugVoxelMesh.Indices.push_back(0);
	DebugVoxelMesh.Indices.push_back(0);
	DebugVoxelMesh.Indices.push_back(0);
	DebugVoxelMesh.Indices.push_back(0);
	DebugVoxelMesh.Indices.push_back(0);
	DebugVoxelMesh.Indices.push_back(0);
	DebugVoxelMesh.Indices.push_back(0);
	DebugVoxelMesh.Indices.push_back(0);
	//DebugVoxelMesh.Indices.push_back(1);
	//DebugVoxelMesh.Indices.push_back(2);
	//DebugVoxelMesh.Indices.push_back(3);
	//DebugVoxelMesh.Indices.push_back(4);
	//DebugVoxelMesh.Indices.push_back(5);
	//DebugVoxelMesh.Indices.push_back(6);
	//DebugVoxelMesh.Indices.push_back(7);


	//DebugVoxelMesh.Indices.push_back(1);
	//DebugVoxelMesh.Indices.push_back(3);
	//DebugVoxelMesh.Indices.push_back(2);

	//DebugVoxelMesh.Indices.push_back(1);
	//DebugVoxelMesh.Indices.push_back(0);
	//DebugVoxelMesh.Indices.push_back(3);

	//DebugVoxelMesh.Indices.push_back(5);
	//DebugVoxelMesh.Indices.push_back(7);
	//DebugVoxelMesh.Indices.push_back(6);

	//DebugVoxelMesh.Indices.push_back(5);
	//DebugVoxelMesh.Indices.push_back(4);
	//DebugVoxelMesh.Indices.push_back(7);

	//DebugVoxelMesh.Indices.push_back(2);
	//DebugVoxelMesh.Indices.push_back(7);
	//DebugVoxelMesh.Indices.push_back(6);

	//DebugVoxelMesh.Indices.push_back(2);
	//DebugVoxelMesh.Indices.push_back(3);
	//DebugVoxelMesh.Indices.push_back(7);

	//DebugVoxelMesh.Indices.push_back(1);
	//DebugVoxelMesh.Indices.push_back(5);
	//DebugVoxelMesh.Indices.push_back(0);

	//DebugVoxelMesh.Indices.push_back(5);
	//DebugVoxelMesh.Indices.push_back(4);
	//DebugVoxelMesh.Indices.push_back(0);

	//DebugVoxelMesh.Indices.push_back(3);
	//DebugVoxelMesh.Indices.push_back(0);
	//DebugVoxelMesh.Indices.push_back(7);

	//DebugVoxelMesh.Indices.push_back(0);
	//DebugVoxelMesh.Indices.push_back(4);
	//DebugVoxelMesh.Indices.push_back(7);

	//DebugVoxelMesh.Indices.push_back(1);
	//DebugVoxelMesh.Indices.push_back(2);
	//DebugVoxelMesh.Indices.push_back(5);

	//DebugVoxelMesh.Indices.push_back(2);
	//DebugVoxelMesh.Indices.push_back(6);
	//DebugVoxelMesh.Indices.push_back(5);

}

//void Terrain::SubDivideCells()
//{
//	static XMVECTOR Origin = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//	static Vertex DebugVertex;
//	static float HalfSize = (float)Size / 2.0f;
//	static XMVECTOR NewPosition;
//	static Index Idx = 0;
//	for (int z = 0; z < Size; z++)
//	{
//		for (int y = 0; y < Size; y++)
//		{
//			for (int x = 0; x < Size; x++)
//			{
//				NewPosition = XMVectorSet((Origin.m128_f32[0] - HalfSize)*(x+1), (Origin.m128_f32[1] + HalfSize) * (y + 1), (Origin.m128_f32[2] + HalfSize) * (z + 1), 1.0f);
//				Cells[z][y][x].CellPoints[0] = NewPosition;
//				NewPosition = XMVectorSet((Origin.m128_f32[0] + HalfSize)*(x+1), (Origin.m128_f32[1] + HalfSize) * (y + 1), (Origin.m128_f32[2] + HalfSize) * (z + 1), 1.0f);
//				Cells[z][y][x].CellPoints[1] = NewPosition;
//				NewPosition = XMVectorSet((Origin.m128_f32[0] + HalfSize) * (x + 1), (Origin.m128_f32[1] + HalfSize) * (y + 1), (Origin.m128_f32[2] - HalfSize) * (z + 1), 1.0f);
//				Cells[z][y][x].CellPoints[2] = NewPosition;
//				NewPosition = XMVectorSet((Origin.m128_f32[0] - HalfSize) * (x + 1), (Origin.m128_f32[1] + HalfSize) * (y + 1), (Origin.m128_f32[2] - HalfSize) * (z + 1), 1.0f);
//				Cells[z][y][x].CellPoints[3] = NewPosition;
//
//				NewPosition = XMVectorSet((Origin.m128_f32[0] - HalfSize) * (x + 1), (Origin.m128_f32[1] - HalfSize) * (y + 1), (Origin.m128_f32[2] + HalfSize) * (z + 1), 1.0f);
//				Cells[z][y][x].CellPoints[4] = NewPosition;
//				NewPosition = XMVectorSet((Origin.m128_f32[0] + HalfSize) * (x + 1), (Origin.m128_f32[1] - HalfSize) * (y + 1), (Origin.m128_f32[2] + HalfSize) * (z + 1), 1.0f);
//				Cells[z][y][x].CellPoints[5] = NewPosition;
//				NewPosition = XMVectorSet((Origin.m128_f32[0] + HalfSize) * (x + 1), (Origin.m128_f32[1] - HalfSize) * (y + 1), (Origin.m128_f32[2] - HalfSize) * (z + 1), 1.0f);
//				Cells[z][y][x].CellPoints[6] = NewPosition;
//				NewPosition = XMVectorSet((Origin.m128_f32[0] - HalfSize) * (x + 1), (Origin.m128_f32[1] - HalfSize) * (y + 1), (Origin.m128_f32[2] - HalfSize) * (z + 1), 1.0f);
//				Cells[z][y][x].CellPoints[7] = NewPosition;
//
//				XMStoreFloat3(&DebugVertex.Position, Cells[z][y][x].CellPoints[0]);
//				DebugMesh.Vertices.push_back(DebugVertex);
//
//				XMStoreFloat3(&DebugVertex.Position, Cells[z][y][x].CellPoints[1]);
//				DebugMesh.Vertices.push_back(DebugVertex);
//
//				XMStoreFloat3(&DebugVertex.Position, Cells[z][y][x].CellPoints[2]);
//				DebugMesh.Vertices.push_back(DebugVertex);
//
//				XMStoreFloat3(&DebugVertex.Position, Cells[z][y][x].CellPoints[3]);
//				DebugMesh.Vertices.push_back(DebugVertex);
//
//				XMStoreFloat3(&DebugVertex.Position, Cells[z][y][x].CellPoints[4]);
//				DebugMesh.Vertices.push_back(DebugVertex);
//
//				XMStoreFloat3(&DebugVertex.Position, Cells[z][y][x].CellPoints[5]);
//				DebugMesh.Vertices.push_back(DebugVertex);
//
//				XMStoreFloat3(&DebugVertex.Position, Cells[z][y][x].CellPoints[6]);
//				DebugMesh.Vertices.push_back(DebugVertex);
//
//				XMStoreFloat3(&DebugVertex.Position, Cells[z][y][x].CellPoints[7]);
//				DebugMesh.Vertices.push_back(DebugVertex);
//
//				DebugMesh.Indices.push_back(Idx);
//
//				Idx++;
//			}
//		}
//	}
//
//
//
//
//	// -++
//	// +++
//	// ++-
//	// -+-
//
//	// --+
//	// +-+
//	// +--
//	// ---
//}

void Terrain::InitializeCells()
{
	assert(Size < MAX_INSTANCE_SIZE);

	static XMVECTOR Origin = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	static Vertex DebugVertex;
	static int FlatIndex;
	static XMVECTOR DebugVectors[4][4][4];

	Capacity = Size * Size * Size;

	for (int z = 0; z < Size; z++)
	{
		for (int y = 0; y < Size; y++)
		{
			for (int x = 0; x < Size; x++)
			{
				FlatIndex = x + Size * (y + Size * z);

				TerrainInst.Instances[FlatIndex].WorldPosition = XMFLOAT3(Origin.m128_f32[0] + x,
													 Origin.m128_f32[1] + y,
													 Origin.m128_f32[2] + z);
				
				

				Cells[FlatIndex].Density[0] = rand() % 10 * 0.1f;
				Cells[FlatIndex].Density[1] = rand() % 10 * 0.1f;
				Cells[FlatIndex].Density[2] = rand() % 10 * 0.1f;
				Cells[FlatIndex].Density[3] = rand() % 10 * 0.1f;
				Cells[FlatIndex].Density[4] = rand() % 10 * 0.1f;
				Cells[FlatIndex].Density[5] = rand() % 10 * 0.1f;
				Cells[FlatIndex].Density[6] = rand() % 10 * 0.1f;
				Cells[FlatIndex].Density[7] = rand() % 10 * 0.1f;

				TerrainInst.Instances[FlatIndex].Density[0] = Cells[FlatIndex].Density[0];
				TerrainInst.Instances[FlatIndex].Density[1] = Cells[FlatIndex].Density[1];
				TerrainInst.Instances[FlatIndex].Density[2] = Cells[FlatIndex].Density[2];
				TerrainInst.Instances[FlatIndex].Density[3] = Cells[FlatIndex].Density[3];
				TerrainInst.Instances[FlatIndex].Density[4] = Cells[FlatIndex].Density[4];
				TerrainInst.Instances[FlatIndex].Density[5] = Cells[FlatIndex].Density[5];
				TerrainInst.Instances[FlatIndex].Density[6] = Cells[FlatIndex].Density[6];
				TerrainInst.Instances[FlatIndex].Density[7] = Cells[FlatIndex].Density[7];

			}
		}
	}
	DebugVertex.Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	DebugMesh.Vertices.push_back(DebugVertex);
	DebugMesh.Indices.push_back(0);


}

Terrain::Terrain(UINT Size_)
{
	Size = Size_;

	long CellCount = (Size * Size * Size);

	TerrainInst.Instances = new TerrainInstanceData[CellCount];

	//for (int i = 0; i < CellCount; i++)
	//{
	//	TerrainInst.Density[i] = new float[8];
	//}
	//WorldPosition = new XMFLOAT3 **[Size];
	//for (int i = 0; i < Size; i++)
	//{
	//	WorldPosition[i] = new XMFLOAT3 *[Size];
	//	for (int j = 0; j < Size; j++)
	//	{
	//		WorldPosition[i][j] = new XMFLOAT3[Size];
	//	}
	//}

	//Cells = new Cell**[CellCount];
	//for (int i = 0; i < CellCount; i++)
	//{
	//	Cells[i] = new Cell * [CellCount];
	//	for (int j = 0; j < CellCount; j++)
	//	{
	//		Cells[i][j] = new Cell[CellCount];
	//	}
	//}

	Cells = new Cell[CellCount];

	


}

Terrain::~Terrain()
{
	delete Cells;
}
