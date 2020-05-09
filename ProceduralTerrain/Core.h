#pragma once

#ifndef _CORE_H_
#define _CORE_H_

using namespace std;
using namespace DirectX;

class Core
{
	UINT Width;
	UINT Height;

	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	vector<Model*> ModelCache;
	
	HWND WindowHandle;
	HINSTANCE HandleInstance;

	RenderTarget2D* SwapChainBuffer = nullptr;
	D3D11_VIEWPORT* Viewport = nullptr;

	Scene* SelectedScene = nullptr;

	Shader* TerrainVoxelShader = nullptr;
	
	ID3D11VertexShader* TerrainVS = nullptr;
	ID3D11VertexShader* TerrainRenderVS = nullptr;

	ID3D11PixelShader* TerrainPS = nullptr;
	ID3D11GeometryShader* TerrainGS = nullptr;
	ID3D11InputLayout* TerrainIL = nullptr;

	ID3D11VertexShader* QuadVS = nullptr;
	ID3D11InputLayout* QuadIL = nullptr;
	ID3D11GeometryShader* QuadGS = nullptr;
	ID3D11PixelShader* QuadPS = nullptr;

	ID3D11VertexShader* NonEmptyCellListVS = nullptr;
	ID3D11GeometryShader* NonEmptyCellListGS = nullptr;

	ID3D11VertexShader* VertexEdgeListVS = nullptr;
	ID3D11GeometryShader* VertexEdgeListGS = nullptr;

	ID3D11RasterizerState* RSDefault = nullptr;
	ID3D11RasterizerState* RSNoDepthCull = nullptr;

	Terrain* MainTerrain = nullptr;

#ifndef _DEFERRED
	DepthStencil2D* DepthStencil = nullptr;
#endif
#ifdef _DEFERRED
	ID3D11RenderTargetView** GBufferRTVPtr = nullptr;
	vector<Texture2D*> GBuffer;
	UINT BufferCount = 0;
	vector<DXGI_FORMAT> GBufferFormats;
#endif


private:
	HRESULT Resize();
	void ReleaseBuffer();

	void CachePrimitives();

	void InitRasterrizerStates();
public:
	CustomModel<VolumeSliceVertex>* ScreenQuad = nullptr;

	Core(HWND InWindowHandle, HINSTANCE InHandleInstance, UINT InWidth, UINT InHeight) : 
		WindowHandle(InWindowHandle), HandleInstance(InHandleInstance), Width(InWidth), Height(InHeight) { }
	~Core();

	HRESULT PostInitialize();

	HRESULT Intialize();
	void Update(float Delta);
	void Render(float Delta);
	void Release();

	_inline void ClearScreen(XMVECTORF32 Color)
	{
		Context->ClearRenderTargetView(SwapChainBuffer->RTV, Color);
	#ifndef _DEFERRED
		Context->ClearDepthStencilView(DepthStencil->DSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	#else
		for (int i = 1; i < BufferCount; i++)
		{
			Context->ClearRenderTargetView(GBufferRTVPtr[i], Color);
		}
		Context->ClearDepthStencilView(GBuffer[0]->ToDepthStencil()->DSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	#endif

		SetRenderToDirect();

	}

	HRESULT AllocTerrainMeshBuffer(Terrain** AllocTerrain);
	HRESULT AllocTerrainInstanceBuffer(Terrain** AllocTerrain);
	HRESULT AllocTerrainVoxelInstanceDebugBuffer(Terrain** AllocTerrain);

	HRESULT AllocVolumeSliceBuffer(CustomModel<VolumeSliceVertex>** Quad);
	HRESULT AllocVolumeSliceStreamBuffer(Terrain** AllocTerrain);
	HRESULT AllocTerrainStreamBuffers(Terrain** AllocTerrain);

	HRESULT AllocConstantBuffer(Model* AllocModel);
	HRESULT AllocMeshBuffer(Model* AllocModel);
	HRESULT GenerateMaterial(Material*& OutMaterial, string Path);

	HRESULT AllocCaseStreamBuffer();

	void BindBuffer(Instance& BindInstance);
	void DrawInstance(Instance& DrawInstance);
	void DrawGSInstance(Instance& DrawInstance);
	void ExtendGSInstance(Instance& DrawInstance);
	
#ifdef _DEBUG
	void DrawTerrainDebug(Terrain* DrawTerrain);
#endif

#ifdef _DEBUG
	_inline void SetDebugName(ID3D11DeviceChild* Resource, string Name) { HRESULT Result = Resource->SetPrivateData(WKPDID_D3DDebugObjectName, lstrlenA(Name.c_str()), Name.c_str());
	Result;
	}
#endif

	void DrawVolume();
	void CreateVoxelMesh();

	void DrawInstanceInstanced(Instance& DrawObject, UINT InstanceCount);

	_inline void CacheInstance(Instance& Inst) { assert(&Inst); SelectedScene->AddInstance(Inst); }
	_inline void CacheBuffer(MeshBuffer& Buffer) { assert(&Buffer); SelectedScene->AddMeshBuffer(Buffer); }
	_inline void CacheMaterial(Material& Mat, string Name) { assert(&Mat); SelectedScene->AddMaterial(Name, &Mat); }


#ifdef _FORWARD
	_inline void SetRenderToDirect() { Context->OMSetRenderTargets(1, &SwapChainBuffer->RTV, DepthStencil->DSV); }
#endif
#ifdef _DEFERRED
	_inline void SetRenderToDirect() { Context->OMSetRenderTargets(1, &SwapChainBuffer->RTV, nullptr); }
	_inline void SetRenderToGBuffer() { Context->OMSetRenderTargets(BufferCount, GBufferRTVPtr, GBuffer[0]->ToDepthStencil()->DSV); }

#endif

};

#endif