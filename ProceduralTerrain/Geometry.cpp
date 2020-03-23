#include "stdafx.h"

void CreateCube(Model** OutModel)
{
	OutModel[0]->ModelMesh = new Mesh();

	Vertex V[]{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f) , XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
	};

	UINT I[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	for (int i = 0; i < ARRAYSIZE(V); i++)
	{
		OutModel[0]->ModelMesh->Vertices.push_back(V[i]);
	}

	for (int i = 0; i < ARRAYSIZE(I); i++)
	{
		OutModel[0]->ModelMesh->Indices.push_back(I[i]);
	}
}

void CreateTerrain(Model** OutModel)
{
	OutModel[0]->ModelMesh = new Mesh();

	Vertex V[]
	{
		{XMFLOAT3(0.0f,0.0f,0.0f), XMFLOAT3(0.0f,1.0f,0.0f), XMFLOAT2(0.0f,0.0f) }
	};

	UINT I[] =
	{
		0
	};

	OutModel[0]->ModelMesh->Vertices.push_back(V[0]);
	OutModel[0]->ModelMesh->Indices.push_back(I[0]);

	return;
}

void CreateQuad(CustomModel<VolumeSliceVertex>** QuadModel)
{
	QuadModel[0]->QuadMesh = new CustomMesh<VolumeSliceVertex>();

	VolumeSliceVertex V[] =
	{
		{{-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
		{{-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
		{{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f}}
	};

	Index I[] =
	{
		0,2,3,
		3,1,0
	};

	QuadModel[0]->QuadMesh->Vertices.push_back(V[0]);
	QuadModel[0]->QuadMesh->Vertices.push_back(V[1]);
	QuadModel[0]->QuadMesh->Vertices.push_back(V[2]);
	QuadModel[0]->QuadMesh->Vertices.push_back(V[3]);

	QuadModel[0]->QuadMesh->Indices.push_back(I[2]);
	QuadModel[0]->QuadMesh->Indices.push_back(I[1]);
	QuadModel[0]->QuadMesh->Indices.push_back(I[0]);
	QuadModel[0]->QuadMesh->Indices.push_back(I[5]);
	QuadModel[0]->QuadMesh->Indices.push_back(I[4]);
	QuadModel[0]->QuadMesh->Indices.push_back(I[3]);

	return;
}
