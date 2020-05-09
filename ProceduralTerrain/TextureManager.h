#pragma once


static HRESULT CreateTexture3D(ID3D11Device* Device, ID3D11Texture3D** pOutTexture3D)
{
	HRESULT Result;
	D3D11_TEXTURE3D_DESC TexDesc{};

	
	TexDesc.Format = DXGI_FORMAT_R32_FLOAT;
	TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	TexDesc.Width = 33;
	TexDesc.Height = 33;
	TexDesc.Depth = 33;
	TexDesc.Usage = D3D11_USAGE_DEFAULT;

	Result = Device->CreateTexture3D(&TexDesc, nullptr, pOutTexture3D);
	assert(Result == S_OK || Result == S_FALSE && "Failed to create ID3D11Texture3D.");
		
	return S_OK;
};

static HRESULT CreateTexture3D(ID3D11Device* Device, ID3D11Texture3D** pOutTexture3D, UINT Size, DXGI_FORMAT Format)
{
	HRESULT Result;
	D3D11_TEXTURE3D_DESC TexDesc{};


	TexDesc.Format = Format;
	TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	TexDesc.Width = Size;
	TexDesc.Height = Size;
	TexDesc.Depth = Size;
	TexDesc.Usage = D3D11_USAGE_DEFAULT;

	Result = Device->CreateTexture3D(&TexDesc, nullptr, pOutTexture3D);
	assert(Result == S_OK || Result == S_FALSE && "Failed to create ID3D11Texture3D.");

	return S_OK;
};


static HRESULT CreateRenderTargetView3D(ID3D11Device* Device, ID3D11Texture3D* InTexture3D, ID3D11RenderTargetView** pOutRTV)
{
	HRESULT Result;
	D3D11_RENDER_TARGET_VIEW_DESC Desc{};
	D3D11_TEXTURE3D_DESC TexDesc{};

	InTexture3D->GetDesc(&TexDesc);

	Desc.Format = TexDesc.Format;
	Desc.Texture3D.WSize = TexDesc.Depth;
	Desc.Texture3D.FirstWSlice = 0;
	Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;

	Result = Device->CreateRenderTargetView(InTexture3D, &Desc, pOutRTV);
	assert(Result == S_OK || Result == S_FALSE && "Failed to create RTV from ID3D11Texture3D.");

	return S_OK;
}

static HRESULT CreateShaderResourceView3D(ID3D11Device* Device, ID3D11Texture3D* InTexture3D, ID3D11ShaderResourceView** pOutSRV)
{
	HRESULT Result;
	D3D11_TEXTURE3D_DESC TexDesc{};
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc{};

	InTexture3D->GetDesc(&TexDesc);

	SRVDesc.Format = TexDesc.Format;
	SRVDesc.Texture3D.MipLevels = 1;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
	SRVDesc.Texture3D.MostDetailedMip = 0;
	Result = Device->CreateShaderResourceView(InTexture3D, &SRVDesc, pOutSRV);
	assert(Result == S_OK || Result == S_FALSE && "Failed to create SRV from ID3D11Texture3D.");

	return S_OK;
}