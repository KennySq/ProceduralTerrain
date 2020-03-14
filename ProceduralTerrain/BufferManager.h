#pragma once
struct AllocStreamBuffer
{
	void operator()(ID3D11Device* Device, GeometryBuffer** pOutGeoBuffer)
	{
		HRESULT Result;

		pOutGeoBuffer[0] = new GeometryBuffer();

		D3D11_BUFFER_DESC BufferDesc{};
		BufferDesc.ByteWidth = 2048;
		BufferDesc.BindFlags = D3D11_BIND_STREAM_OUTPUT | D3D11_BIND_VERTEX_BUFFER;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//BufferDesc.StructureByteStride = sizeof(Vertex);

		Result = Device->CreateBuffer(&BufferDesc, nullptr, &pOutGeoBuffer[0]->StreamBuffer);
		assert(Result == S_OK && "Stream Buffer failed to alloc");
	
		Result = Device->CreateBuffer(&BufferDesc, nullptr, &pOutGeoBuffer[0]->VertexStreamBuffer);
		assert(Result == S_OK && "Vertex stream Buffer failed to alloc");
	}
};

// 스트림버퍼는 Terrain 의 정점을 조작할때 사용할 것이다.

// VB로 바인드 했기 때문에 GS단계로 버퍼가 바인드될때는 투영이 되어서는 안된다. 기본형의 좌표 그대로 전달해야한다.