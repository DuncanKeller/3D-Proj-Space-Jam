#include "DXUT.h"
#include "EFighter.h"
#include "EStation.h"
#include "EmptyProject.h"
#include "World.h"

const int ATK_COOLDOWN = 30;
EFighter::EFighter(void)
{
	mesh = Mesh();
}


EFighter::~EFighter(void)
{
}

void EFighter::Init(ID3D11Device* device,World* w, XMFLOAT3 startPos)
{
	pos = XMFLOAT3(startPos.x, startPos.y, startPos.z);
	//pos.y + 5;
#pragma region meshing
	mesh.Load("Assets/SpaceShipTex.obj");

	XMStoreFloat4x4(&mWorldNoTransl,XMMatrixIdentity());

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

	mat.Ambient = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	mat.Diffuse = XMFLOAT4(0.77f, 0.77f, 1.0f, 1.0f);
	mat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);
#pragma endregion

	worldPTR = w;

	HR(D3DX11CreateShaderResourceViewFromFile(device,mesh.texturePath,0,0,&mDiffuseSRV,0));


}

bool EFighter::IsActive()
{
	return active;
}

void EFighter::Update()
{
	if(active)
	{
		attackTimer++;
		//do stuff
	}
}

void EFighter::Attack()
{
	if(attackTimer > ATK_COOLDOWN)
	{
		attackTimer = 0;
	}
}