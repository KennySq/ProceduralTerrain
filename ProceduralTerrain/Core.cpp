#include "stdafx.h"
#include "Core.h"

Core::~Core()
{}

HRESULT Core::PostInitialize()
{
	UINT DeviceFlag = 0;

	HRESULT Result;

#ifdef _DEBUG
	DeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL FeatureLevel[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
	};

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.Height = Height;
	SwapChainDesc.BufferDesc.Width = Width;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.Flags = DeviceFlag;

	Result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, DeviceFlag, nullptr, 0, D3D11_SDK_VERSION, &SwapChainDesc, &SwapChain, &Device, &FeatureLevel[0], &Context);
	if (FAILED(Result))
		return Result;

	return S_OK;
}

HRESULT Core::Intialize()
{
	Resize();
	
	AllocStreamBuffer StreamBuffer;

	Material* SimpleMat = new Material();
	Material* TerrainMat = new Material();
	Instance* SimpleTerrain = new Instance();
	
	SelectedScene = new Scene();
	
	CachePrimitives();
	AllocMeshBuffer(ModelCache[1]);
	AllocConstantBuffer(ModelCache[1]);
	StreamBuffer(Device, &ModelCache[1]->ModelGeoBuffer);

	GenerateMaterial(SimpleMat, "TestShader.hlsl");
	
	CompileVertexShader(Device, "TerrainRenderVS.hlsl", "TerrainRenderVS", &TerrainRenderVS, &TerrainIL);
	CompileVertexShader(Device, "TerrainVS.hlsl","TerrainVS", &TerrainVS, &TerrainIL);
	CompileGeometryShaderForStreamOutput(Device, "TerrainGS.hlsl", "TerrainGS", &TerrainGS);
	CompilePixelShader(Device, "TerrainPS.hlsl", "TerrainPS", &TerrainPS);

	SimpleTerrain->RenderModel = ModelCache[1];

	SelectedScene->AddInstance(*SimpleTerrain);

	//ModelCache[0]->ModelMaterial = SimpleMat;
	//SimpleCube->RenderModel = ModelCache[0];
	//SelectedScene->AddInstance(*SimpleCube);

	return S_OK;
}

void Core::Update(float Delta)
{
	ClearScreen(Colors::Black);
}

void Core::Render(float Delta)
{
	static bool First = true;

	if (First)
		ExtendGSInstance(*SelectedScene->GetInstances()[0]);
	else
		DrawGSInstance(*SelectedScene->GetInstances()[0]);

	First = false;

	SwapChain->Present(0, 0);
}

void Core::Release()
{
	ReleaseBuffer();

	Device->Release();
	Context->Release();
	SwapChain->Release();
	
}

HRESULT Core::AllocConstantBuffer(Model* AllocModel)
{
	HRESULT Result;
	D3D11_BUFFER_DESC BufferDesc{};

	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(Matrices);
	
	Result = Device->CreateBuffer(&BufferDesc, nullptr, &AllocModel->ModelMeshBuffer->ConstBuffer);
	if (FAILED(Result))
		return Result;

	BufferDesc.ByteWidth = sizeof(TerrainBuffer);
	Result = Device->CreateBuffer(&BufferDesc, nullptr, &AllocModel->ModelMeshBuffer->TerrainBuffer);
	if (FAILED(Result))
		return Result;

	return S_OK;
}

HRESULT Core::AllocMeshBuffer(Model* AllocModel)
{
	HRESULT Result;
	D3D11_BUFFER_DESC BufferDesc{};

	D3D11_SUBRESOURCE_DATA SubData{};

	AllocModel->ModelMeshBuffer = new MeshBuffer();

	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(Vertex) * AllocModel->ModelMesh->Vertices.size();
	
	SubData.pSysMem = AllocModel->ModelMesh->Vertices.data();


	Result = Device->CreateBuffer(&BufferDesc, &SubData, &AllocModel->ModelMeshBuffer->VertexBuffer);

	if (FAILED(Result))
		return Result;

	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDesc.ByteWidth = sizeof(Index) * AllocModel->ModelMesh->Indices.size();

	SubData.pSysMem = AllocModel->ModelMesh->Indices.data();

	Result = Device->CreateBuffer(&BufferDesc, &SubData, &AllocModel->ModelMeshBuffer->IndexBuffer);
	
	if (FAILED(Result))
		return Result;

	CacheBuffer(*AllocModel->ModelMeshBuffer);

	return S_OK;
}

HRESULT Core::GenerateMaterial(Material*& OutMaterial, string Path)
{
	HRESULT Result;

	OutMaterial->MaterialShader->FileName = Path;

	Result = CompileVertexShader(Device, Path, OutMaterial->MaterialShader);

	if (FAILED(Result))
		return Result;

	Result = CompilePixelShader(Device, Path, OutMaterial->MaterialShader);

	if (FAILED(Result))
		return Result;

	CacheMaterial(*OutMaterial, Path);

	return S_OK;
}

void Core::BindBuffer(Instance& BindInstance)
{
	static const UINT Stride = sizeof(Vertex);
	static const UINT Offset = 0;
	
	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Context->IASetVertexBuffers(0, 1, &BindInstance.RenderModel->ModelMeshBuffer->VertexBuffer, &Stride, &Offset);
	Context->IASetInputLayout(BindInstance.ModelMaterial->MaterialShader->InputLayouts.IL);
#ifdef _INDEX16
	Context->IASetIndexBuffer(BindInstance.RenderModel->ModelMeshBuffer->IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
#endif
#ifdef _INDEX32
	Context->IASetIndexBuffer(BindInstance.RenderModel->ModelBuffer->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
#endif


}

void Core::DrawInstance(Instance& DrawObject)
{
	static Matrices ConstBuf{};

	ConstBuf.World = XMMatrixIdentity();
	ConstBuf.View = XMMatrixTranspose(SelectedScene->GetMainCamera()->GetView());
	ConstBuf.Projection = XMMatrixTranspose(SelectedScene->GetMainCamera()->GetProjection());

	Context->UpdateSubresource(DrawObject.RenderModel->ModelMeshBuffer->ConstBuffer, 0, nullptr, &ConstBuf, 0, 0);

	Context->VSSetShader(DrawObject.ModelMaterial->MaterialShader->VS, nullptr, 0);
	Context->VSSetConstantBuffers(0, 1, &DrawObject.RenderModel->ModelMeshBuffer->ConstBuffer);
	Context->PSSetShader(DrawObject.ModelMaterial->MaterialShader->PS, nullptr, 0);
	
	BindBuffer(DrawObject);

	
	Context->DrawIndexed(DrawObject.RenderModel->ModelMesh->Indices.size(), 0, 0);
	
}

void Core::DrawGSInstance(Instance& DrawInstance)
{
	static Matrices ConstBuf{};
	static ID3D11VertexShader* NullVS = nullptr;
	static ID3D11PixelShader* NullPS = nullptr;
	static ID3D11GeometryShader* NullGS = nullptr;
	static ID3D11Buffer* NullBuffer = nullptr;
	static UINT Stride = sizeof(Vertex);
	static UINT Offset = 0;

	ConstBuf.World = XMMatrixIdentity();
	ConstBuf.View = XMMatrixTranspose(SelectedScene->GetMainCamera()->GetView());
	ConstBuf.Projection = XMMatrixTranspose(SelectedScene->GetMainCamera()->GetProjection());

	Context->UpdateSubresource(DrawInstance.RenderModel->ModelMeshBuffer->ConstBuffer, 0, nullptr, &ConstBuf, 0, 0);

	Context->VSSetShader(TerrainRenderVS, nullptr, 0);
	Context->PSSetShader(TerrainPS, nullptr, 0);

	Context->IASetVertexBuffers(0, 1, &DrawInstance.RenderModel->ModelGeoBuffer->VertexStreamBuffer, &Stride, &Offset);
	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	Context->VSSetConstantBuffers(0, 1, &DrawInstance.RenderModel->ModelMeshBuffer->ConstBuffer);

	//Context->PSSetShader(TerrainGS, nullptr, 0);
	Context->DrawAuto();

	Context->IASetIndexBuffer(NullBuffer, DXGI_FORMAT_R16_UINT, 0);
	Context->IASetVertexBuffers(0, 1, &NullBuffer, &Stride, &Offset);
}

void Core::ExtendGSInstance(Instance& DrawInstance)
{
	static TerrainBuffer TBuf{};
	static ID3D11VertexShader* NullVS = nullptr;
	static ID3D11PixelShader* NullPS = nullptr;
	static ID3D11GeometryShader* NullGS = nullptr;
	static ID3D11Buffer* NullBuffer = nullptr;
	static UINT Stride = sizeof(Vertex);
	static UINT Offset = 0;
	TBuf.TerrainLength = 3.0f;

	Context->UpdateSubresource(DrawInstance.RenderModel->ModelMeshBuffer->TerrainBuffer, 0, nullptr, &TBuf, 0, 0);

	Context->VSSetShader(TerrainVS, nullptr, 0);
	Context->GSSetShader(TerrainGS, nullptr, 0);
	Context->PSSetShader(NullPS, nullptr, 0);
	Context->SOSetTargets(1, &DrawInstance.RenderModel->ModelGeoBuffer->StreamBuffer, &Offset);

	Context->IASetInputLayout(TerrainIL);
	Context->IASetVertexBuffers(0, 1, &DrawInstance.RenderModel->ModelMeshBuffer->VertexBuffer, &Stride, &Offset);
	Context->IASetIndexBuffer(DrawInstance.RenderModel->ModelMeshBuffer->IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	Context->GSSetConstantBuffers(1, 1, &DrawInstance.RenderModel->ModelMeshBuffer->TerrainBuffer);
	
	Context->DrawIndexed(1, 0, 0);

	Context->VSSetShader(NullVS, nullptr, 0);
	Context->GSSetShader(NullGS, nullptr, 0);
	Context->IASetIndexBuffer(NullBuffer, DXGI_FORMAT_R16_UINT, 0);
	Context->IASetVertexBuffers(0, 1, &NullBuffer, &Stride, &Offset);
	Context->SOSetTargets(1, &NullBuffer, &Offset);

	ID3D11Buffer* Temp = DrawInstance.RenderModel->ModelGeoBuffer->VertexStreamBuffer;
	DrawInstance.RenderModel->ModelGeoBuffer->VertexStreamBuffer = DrawInstance.RenderModel->ModelGeoBuffer->StreamBuffer;
	DrawInstance.RenderModel->ModelGeoBuffer->StreamBuffer = Temp;
}

HRESULT Core::Resize()
{
	HRESULT Result;
	static D3D11_TEXTURE2D_DESC TexDesc{};
	static D3D11_RENDER_TARGET_VIEW_DESC RTVDesc{};
	static D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc{};
	static D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc{};
	

	ReleaseBuffer();

	SwapChainBuffer = new RenderTarget2D();
	Viewport = new D3D11_VIEWPORT();

	DSVDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DSVDesc.Texture2D.MipSlice = 0;

	TexDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	TexDesc.Height = Height;
	TexDesc.Width = Width;
	TexDesc.Usage = D3D11_USAGE_DEFAULT;
	TexDesc.SampleDesc.Count = 1;

	Viewport->Width = (float)Width;
	Viewport->Height = (float)Height;
	Viewport->MinDepth = 0.0f;
	Viewport->MaxDepth = 1.0f;
	Viewport->TopLeftX = 0.0f;
	Viewport->TopLeftY = 0.0f;

	Context->RSSetViewports(1, Viewport);

	RTVDesc.Format = TexDesc.Format;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	SRVDesc.Format = TexDesc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&SwapChainBuffer->Tex);
	if (FAILED(Result))
		return Result;

	Result = Device->CreateRenderTargetView(SwapChainBuffer->Tex, nullptr, &SwapChainBuffer->RTV);
	if (FAILED(Result))
		return Result;
#ifndef _DEFERRED

	DepthStencil = new DepthStencil2D();

	TexDesc = {};
	TexDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	TexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	TexDesc.Width = Width;
	TexDesc.Height = Height;
	TexDesc.SampleDesc.Count = 1;
	TexDesc.MipLevels = 1;
	TexDesc.ArraySize = 1;

	SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	Result = Device->CreateTexture2D(&TexDesc, nullptr, &DepthStencil->Tex);
	if (FAILED(Result))
		return Result;
	
	Result = Device->CreateDepthStencilView(DepthStencil->Tex, &DSVDesc, &DepthStencil->DSV);
	if (FAILED(Result))
		return Result;

	Result = Device->CreateShaderResourceView(DepthStencil->Tex, &SRVDesc, &DepthStencil->SRV);
	if (FAILED(Result))
		return Result;

#else

	GBufferFormats.push_back(DXGI_FORMAT_R24_UNORM_X8_TYPELESS);
	GBufferFormats.push_back(DXGI_FORMAT_R32G32B32A32_FLOAT);
	GBufferFormats.push_back(DXGI_FORMAT_R32G32B32A32_FLOAT);

	BufferCount = GBufferFormats.size();

	TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
	TexDesc.Usage = D3D11_USAGE_DEFAULT;
	TexDesc.Width = Width;
	TexDesc.Height = Height;
	TexDesc.CPUAccessFlags = 0;
	TexDesc.MipLevels = 0;
	TexDesc.SampleDesc.Count = 1;
	TexDesc.SampleDesc.Quality = 0;
	TexDesc.ArraySize = 0;
	GBuffer.push_back(new DepthStencil2D());
	GBuffer.push_back(new RenderTarget2D[BufferCount - 1]);

	GBufferRTVPtr = new ID3D11RenderTargetView*[BufferCount - 1];

	for (int i = 0; i < BufferCount; i++)
	{
		TexDesc.Format = GBufferFormats[i];

		Result = Device->CreateTexture2D(&TexDesc, nullptr, &GBuffer[i]->Tex);
		if (FAILED(Result))
			return Result;

		if (i > 0)
		{
			SRVDesc.Format = TexDesc.Format;
			SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

			Result = Device->CreateRenderTargetView(GBuffer[i]->Tex, &RTVDesc, &GBuffer[i]->ToRenderTarget()->RTV);
			if (FAILED(Result))
				return Result;

			GBufferRTVPtr[i - 1] = GBuffer[i]->ToRenderTarget()->RTV;
		}
		else
		{
			SRVDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

			Result = Device->CreateDepthStencilView(GBuffer[i]->Tex, &DSVDesc, &GBuffer[i]->ToDepthStencil()->DSV);
			if (FAILED(Result))
				return Result;

			Result = Device->CreateShaderResourceView(GBuffer[i]->Tex, &SRVDesc, &GBuffer[i]->SRV);
			if (FAILED(Result))
				return Result;


		}


	}

#endif

	return S_OK;
}

void Core::ReleaseBuffer()
{
	if (SwapChainBuffer)
	{
		SwapChainBuffer->Tex->Release();
		SwapChainBuffer->RTV->Release();

		SwapChainBuffer->Tex = nullptr;
		SwapChainBuffer->RTV = nullptr;
	}

	delete SwapChainBuffer;
	SwapChainBuffer = nullptr;

	delete Viewport;
	Viewport = nullptr;

#ifndef _DEFERRED

	if (DepthStencil)
	{
		DepthStencil->Tex->Release();
		DepthStencil->DSV->Release();
		DepthStencil->SRV->Release();

		DepthStencil->Tex = nullptr;
		DepthStencil->DSV = nullptr;
		DepthStencil->SRV = nullptr;
	}

	delete DepthStencil;

#else
	if (!GBuffer.empty())
	{
		for (int i = 0; i < BufferCount; i++)
		{
			GBuffer[i]->Tex->Release();

			GBuffer[i]->SRV->Release();

			if (i > 0)
			{
				GBuffer[i]->ToRenderTarget()->RTV->Release();

				GBuffer[i]->Tex = nullptr;
				GBuffer[i]->ToRenderTarget()->RTV = nullptr;
				GBuffer[i]->SRV = nullptr;
			}
			else
			{
				GBuffer[i]->ToDepthStencil()->DSV->Release();

				GBuffer[i]->Tex = nullptr;
				GBuffer[i]->ToDepthStencil()->DSV = nullptr;
				GBuffer[i]->SRV = nullptr;
			}


		}
	}

	GBuffer.clear();
	delete GBufferRTVPtr;


#endif



}

void Core::CachePrimitives()
{
	Model* Cube = new Model();
	Model* Terrain = new Model();

	CreateCube(&Cube);
	CreateTerrain(&Terrain);
	ModelCache.push_back(Cube);
	ModelCache.push_back(Terrain);

}
