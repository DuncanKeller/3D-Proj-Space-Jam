#include "DXUT.h"
#include "EFighter.h"
#include "EStation.h"
#include "EmptyProject.h"
#include "Projectile.h"
#include "World.h"

const int ATK_COOLDOWN = 30;
const float MAX_SPEED = .005;
EFighter::EFighter(void)
{
}


EFighter::~EFighter(void)
{
}

void EFighter::Init(ID3D11Device* device,World* w, XMFLOAT3 startPos, Mesh* m)
{
	mesh=m;
	pos = XMFLOAT3(startPos.x, startPos.y, startPos.z);
	
	scale = XMFLOAT3(.25,.25,.25);
	active = false;
	//pos.y + 5;
	up = XMFLOAT3(0,1,0);
	right = XMFLOAT3(-1,0,0);
#pragma region meshing

	XMVECTOR scaleVect=  XMLoadFloat3(&scale);
	XMStoreFloat4x4(&mWorldNoTransl,XMMatrixIdentity()*XMMatrixScalingFromVector(scaleVect));
	//XMStoreFloat4x4(&mWorldNoTransl,XMMatrixIdentity());

<<<<<<< HEAD
	vertNum = mesh->numInd;
=======
	mesh.texturePath =(L"Assets/EnemyShip.bmp");
	vertNum = mesh.numInd;
>>>>>>> c8b06dd58383fbac1c7a452c7ddc078b99dd926f

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * mesh->numVerts;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = mesh->vertices;
	HR(device->CreateBuffer(&vbd, &vinitData, &vertexBuffer));

	D3D11_BUFFER_DESC ibd2;
	ibd2.Usage = D3D11_USAGE_IMMUTABLE;
	ibd2.ByteWidth = sizeof(UINT) * mesh->numInd;
	ibd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd2.CPUAccessFlags = 0;
	ibd2.MiscFlags = 0;
	ibd2.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData2;
	iinitData2.pSysMem = mesh->indices;
	HR(device->CreateBuffer(&ibd2, &iinitData2, &indexBuffer));

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mWorld, I);

	mat.Ambient = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	mat.Diffuse = XMFLOAT4(0.77f, 0.77f, 1.0f, 1.0f);
	mat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);
#pragma endregion

	worldPTR = w;

	HR(D3DX11CreateShaderResourceViewFromFile(device,mesh->texturePath,0,0,&mDiffuseSRV,0));


}

bool EFighter::IsActive()
{
	return active;
}

void EFighter::GoActive()
{
	active = true;
}

void EFighter::Update()
{
	if(active)
	{
		attackTimer++;
		//do stuff
		XMFLOAT3 stuff(worldPTR->playerShip->pos.x - pos.x, worldPTR->playerShip->pos.y - pos.y, worldPTR->playerShip->pos.z - pos.z);
		XMVECTOR forward = XMLoadFloat3(&stuff);
		float mag = sqrt(stuff.x*stuff.x + stuff.y*stuff.y + stuff.z*stuff.z);
		stuff.x = (stuff.x/mag)*MAX_SPEED;
		stuff.y = (stuff.y/mag)*MAX_SPEED;
		stuff.z = (stuff.z/mag)*MAX_SPEED;

		pos = XMFLOAT3(pos.x + stuff.x, pos.y + stuff.y, pos.z + stuff.z);

	}

	//std::vector<Projectile*> projs = worldPTR->projManager.GetProjs();

	

}

void EFighter::Attack()
{
	if(attackTimer > ATK_COOLDOWN)
	{

		attackTimer = 0;
	}
}