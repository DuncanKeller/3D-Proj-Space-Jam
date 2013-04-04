#include "DXUT.h"
#include "Ship.h"
#include "EmptyProject.h"
#include "World.h"
Ship::Ship(void)
{
	mesh = Mesh();
}

Ship::~Ship(void)
{

}

void Ship::Init(ID3D11Device* device,World* w)
{
	pos = XMFLOAT3(0,0,0);
	scale = XMFLOAT3(1,1,1);
	fwd = XMFLOAT3(0,0,-1);
	up = XMFLOAT3(0,1,0);
	right = XMFLOAT3(-1,0,0);

	XMStoreFloat4x4(&mWorldNoTransl,XMMatrixIdentity());
	mesh.Load("Assets/SpaceShipTex.obj");

	mesh.texturePath =(L"Assets/ShipTex2.bmp");
	vertNum = mesh.numInd;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * mesh.numVerts;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = mesh.vertices;
	HR(device->CreateBuffer(&vbd, &vinitData, &vertexBuffer));

	D3D11_BUFFER_DESC ibd2;
	ibd2.Usage = D3D11_USAGE_IMMUTABLE;
	ibd2.ByteWidth = sizeof(UINT) * mesh.numInd;
	ibd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd2.CPUAccessFlags = 0;
	ibd2.MiscFlags = 0;
	ibd2.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData2;
	iinitData2.pSysMem = mesh.indices;
	HR(device->CreateBuffer(&ibd2, &iinitData2, &indexBuffer));

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mWorld, I);

	mat.Ambient  = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	mat.Diffuse  = XMFLOAT4(0.77f, 0.77f, 1.0f, 1.0f);
	mat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);
	worldPTR = w;

	HR(D3DX11CreateShaderResourceViewFromFile(device,mesh.texturePath,0,0,&mDiffuseSRV,0));

	
}
