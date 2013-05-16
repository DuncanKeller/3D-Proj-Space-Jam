#include "DXUT.h"
#include "EStation.h"
#include "EmptyProject.h"
#include "World.h"

const int NUM_FIGHTERS= 15;
const int FIGHTER_MAX_TIME = 500000;
EStation::EStation(void)
{
}

EStation::~EStation(void)
{
}

<<<<<<< HEAD
void EStation::Init(ID3D11Device* device,World* w, XMFLOAT3 startPos, Mesh* m)
=======
std::vector<EFighter*> EStation::GetFighters()
{
	return fighters;
}

void EStation::Init(ID3D11Device* device,World* w, XMFLOAT3 startPos)
>>>>>>> c8b06dd58383fbac1c7a452c7ddc078b99dd926f
{
	mesh = m;
	//device = aDevice;
	pos = XMFLOAT3(startPos.x, startPos.y, startPos.z);
	scale = XMFLOAT3(10,10,10);
	//pos = XMFLOAT3(0,0,0);
#pragma region meshing

	XMVECTOR scaleVect=  XMLoadFloat3(&scale);
	XMStoreFloat4x4(&mWorldNoTransl,XMMatrixIdentity()*XMMatrixScalingFromVector(scaleVect));

	vertNum = mesh->numInd;

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
	int num = NUM_FIGHTERS;
	for(int i = 0; i < num; i++)
	{
		fighters.push_back(new EFighter());
	}
<<<<<<< HEAD
	for(int i = 0; i < NUM_FIGHTERS; i++)
		fighters[i]->Init(device, w, pos,&(w->shipMesh));
=======
	for(int i = 0; i < num; i++)
		fighters[i]->Init(device, w, pos);
>>>>>>> c8b06dd58383fbac1c7a452c7ddc078b99dd926f
	fighterTimer = FIGHTER_MAX_TIME;
	currentFighters = 0;

	HR(D3DX11CreateShaderResourceViewFromFile(device,mesh->texturePath,0,0,&mDiffuseSRV,0));


}

void EStation::KillFighter(EFighter* f)
{
	fighters.erase(std::remove(fighters.begin(), fighters.end(), f));
	//worldPTR->entities.erase(std::remove(worldPTR->entities.begin(), worldPTR->entities.end(), f));
}

void EStation::Update()
{
	for(int i = 0; i < currentFighters; i++)
	{
		fighters[i]->Update();
	}
	
	fighterTimer --;
}

bool EStation::SpawnFighter()
{
	if(fighterTimer <= 0)
	{
		int i = 0;
		while(true)
		{
			if(i ==  NUM_FIGHTERS)
				return false;
			if(!fighters[i]->IsActive())
			{
				fighters[i]->GoActive();
				//worldPTR->AddEntity(fighters[i]);
				fighterTimer = FIGHTER_MAX_TIME;
				currentFighters++;
				return true;
			}
			i++;
		}
	}
}