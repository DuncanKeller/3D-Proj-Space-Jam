#include "DXUT.h"
#include "Triangle.h"

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};


Triangle::Triangle(float* v)
{
	verts = v;
	vertNum = 3;
}

Triangle::~Triangle(void)
{

}

void Triangle::Init(ID3D11Device* device)
{
	// Create vertex buffer
    Vertex vertices[] =
    {
		{ XMFLOAT3(verts[0], verts[1], verts[2]), (const float*)&Colors::Green   },
		{ XMFLOAT3(verts[3], verts[4], verts[5]), (const float*)&Colors::Yellow   },
		{ XMFLOAT3(verts[6], verts[7], verts[8]), (const float*)&Colors::Black     }
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
	HR(device->CreateBuffer(&vbd, &vinitData, &vertexBuffer));

	// index buffer
	UINT ground[] = {
		 0, 1, 2
	};

	D3D11_BUFFER_DESC ibd2;
    ibd2.Usage = D3D11_USAGE_IMMUTABLE;
    ibd2.ByteWidth = sizeof(UINT) * 3;
    ibd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd2.CPUAccessFlags = 0;
    ibd2.MiscFlags = 0;
	ibd2.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData2;
    iinitData2.pSysMem = ground;
    HR(device->CreateBuffer(&ibd2, &iinitData2, &indexBuffer));
}