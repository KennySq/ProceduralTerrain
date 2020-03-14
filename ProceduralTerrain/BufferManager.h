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

// ��Ʈ�����۴� Terrain �� ������ �����Ҷ� ����� ���̴�.

// VB�� ���ε� �߱� ������ GS�ܰ�� ���۰� ���ε�ɶ��� ������ �Ǿ�� �ȵȴ�. �⺻���� ��ǥ �״�� �����ؾ��Ѵ�.