#pragma once



#ifndef _HLSL_COMPILER_H_
#define _HLSL_COMPILER_H_



static HRESULT CompileVertexShader(ID3D11Device* Device, string Path, Shader*& OutShader)
{
	USES_CONVERSION;

	UINT Flag = 0;
	HRESULT Result;

	ID3DBlob* VBlob, *ErrBlob;

	D3D11_INPUT_ELEMENT_DESC InputElements[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},

		{"TEXCOORD", 1, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"TEXCOORD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 2, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{"TEXCOORD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 2, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		
		
	};

	/*
	LPCSTR SemanticName;
    UINT SemanticIndex;
    DXGI_FORMAT Format;
    UINT InputSlot;
    UINT AlignedByteOffset;
    D3D11_INPUT_CLASSIFICATION InputSlotClass;
    UINT InstanceDataStepRate;
	
	*/

#ifdef _DEBUG
	Flag |= D3DCOMPILE_DEBUG;
#endif

	Result = D3DCompileFromFile(A2W(Path.c_str()), nullptr, nullptr, OutShader->VSEntry.c_str(), "vs_5_0", 0, Flag, &VBlob, &ErrBlob);
	
	if (FAILED(Result))
	{
		ErrBlob->Release();

		return Result;
	}

	Result = Device->CreateInputLayout(InputElements, ARRAYSIZE(InputElements), 
									   VBlob->GetBufferPointer(), VBlob->GetBufferSize(), 
									   &OutShader->InputLayouts.IL);
	if (FAILED(Result))
		return Result;

	Result = Device->CreateVertexShader(VBlob->GetBufferPointer(), VBlob->GetBufferSize(), nullptr, &OutShader->VS);

	VBlob->Release();

	if (FAILED(Result))
		return Result;

	return Result;
}

static HRESULT CompileVertexShader(ID3D11Device* Device, string Path, string Entry, ID3D11VertexShader** pOutVS, ID3D11InputLayout** pOutIL)
{
	USES_CONVERSION;

	UINT Flag = 0;
	HRESULT Result;

	ID3DBlob* VBlob, * ErrBlob;

	D3D11_INPUT_ELEMENT_DESC InputElements[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R16G16_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

#ifdef _DEBUG
	Flag |= D3DCOMPILE_DEBUG;
#endif

	Result = D3DCompileFromFile(A2W(Path.c_str()), nullptr, nullptr, Entry.c_str(), "vs_5_0", 0, Flag, &VBlob, &ErrBlob);

	if (FAILED(Result))
	{
		ErrBlob->Release();

		return Result;
	}

	Result = Device->CreateInputLayout(InputElements, ARRAYSIZE(InputElements),
									   VBlob->GetBufferPointer(), VBlob->GetBufferSize(),
									   pOutIL);
	if (FAILED(Result))
		return Result;

	Result = Device->CreateVertexShader(VBlob->GetBufferPointer(), VBlob->GetBufferSize(), nullptr, pOutVS);

	VBlob->Release();

	if (FAILED(Result))
		return Result;

	return Result;
}

static HRESULT CompilePixelShader(ID3D11Device* Device, string Path, Shader*& OutShader)
{
	USES_CONVERSION;

	UINT Flag = 0;
	HRESULT Result;

	ID3DBlob* PBlob, *ErrBlob;

#ifdef _DEBUG
	Flag |= D3DCOMPILE_DEBUG;
#endif

	Result = D3DCompileFromFile(A2W(Path.c_str()), nullptr, nullptr, OutShader->PSEntry.c_str(), "ps_5_0", 0, Flag, &PBlob, &ErrBlob);
	
	if (FAILED(Result))
	{
		ErrBlob->Release();

		return Result;
	}

	Result = Device->CreatePixelShader(PBlob->GetBufferPointer(), PBlob->GetBufferSize(), nullptr, &OutShader->PS);

	PBlob->Release();

	if (FAILED(Result))
		return Result;


	return Result;
}

static HRESULT CompilePixelShader(ID3D11Device* Device, string Path, string Entry, ID3D11PixelShader** pOutPS)
{
	USES_CONVERSION;

	UINT Flag = 0;
	HRESULT Result;

	ID3DBlob* PBlob, * ErrBlob;

#ifdef _DEBUG
	Flag |= D3DCOMPILE_DEBUG;
#endif

	Result = D3DCompileFromFile(A2W(Path.c_str()), nullptr, nullptr, Entry.c_str(), "ps_5_0", 0, Flag, &PBlob, &ErrBlob);

	if (FAILED(Result))
	{
		ErrBlob->Release();

		return Result;
	}

	Result = Device->CreatePixelShader(PBlob->GetBufferPointer(), PBlob->GetBufferSize(), nullptr, pOutPS);

	PBlob->Release();

	if (FAILED(Result))
		return Result;


	return Result;
}

static HRESULT CompileGeometryShaderForStreamOutput(ID3D11Device* Device, string Path,string Entry, ID3D11GeometryShader** pOutGS)
{
	USES_CONVERSION;
	
	HRESULT Result;

	UINT CompileFlag = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* GBlob = nullptr, * ErrBlob = nullptr;

#ifdef _DEBUG
	CompileFlag = D3DCOMPILE_DEBUG;
#endif

	D3D11_SO_DECLARATION_ENTRY Entries[] =
	{
		{0, "SV_POSITION", 0, 0, 3, 0},											//		UINT Stream;
		{0, "TEXCOORD", 0, 0, 3, 0},												//LPCSTR SemanticName;
		{0, "TEXCOORD", 1, 0, 2, 0},												//UINT SemanticIndex;
														//BYTE StartComponent;
														//BYTE ComponentCount;
														//BYTE OutputSlot;
	};

	UINT Stride[1] = { sizeof(Vertex) };
	
	Result = D3DCompileFromFile(A2W(Path.c_str()), nullptr, nullptr, Entry.c_str(), "gs_5_0", 0, CompileFlag, &GBlob, &ErrBlob);
	assert(Result == S_OK && "Failed to compile GS");

	Result = Device->CreateGeometryShaderWithStreamOutput(GBlob->GetBufferPointer(), GBlob->GetBufferSize(), Entries, _countof(Entries), Stride, _countof(Stride), 0, nullptr, pOutGS);
	assert(Result == S_OK && "Failed to create GS with SO");



	return S_OK;
	
}

#endif