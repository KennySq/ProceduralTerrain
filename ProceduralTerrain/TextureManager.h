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
	//TexDesc.MipLevels = 1;
		
	Result = Device->CreateTexture3D(&TexDesc, nullptr, pOutTexture3D);
	assert(Result == S_OK && "Failed to create ID3D11Texture3D.");
		
	return S_OK;
};