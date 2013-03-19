#include "DXUT.h"
#include "Entity.h"

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

void Entity::Init(ID3D11Device* md3dDevice)
{
	// Create vertex buffer
    Vertex vertices[] =
    {
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), (const float*)&Colors::White   },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), (const float*)&Colors::Black   },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), (const float*)&Colors::Red     },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), (const float*)&Colors::Green   }
    };

    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(Vertex) * 4;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = vertices;
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &vertexBuffer));

	// index buffer
	UINT ground[] = {
		 0, 1, 2,
		 0, 2, 3
	};

	D3D11_BUFFER_DESC ibd2;
    ibd2.Usage = D3D11_USAGE_IMMUTABLE;
    ibd2.ByteWidth = sizeof(UINT) * 6;
    ibd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd2.CPUAccessFlags = 0;
    ibd2.MiscFlags = 0;
	ibd2.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData2;
    iinitData2.pSysMem = ground;
    HR(md3dDevice->CreateBuffer(&ibd2, &iinitData2, &indexBuffer));

}

void Entity::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	D3DX11_TECHNIQUE_DESC techDesc;
    tech->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        tech->GetPassByIndex(p)->Apply(0, context);
        
		// 6 indices for the box.
		context->DrawIndexed(vertNum, 0, 0);
    }
}