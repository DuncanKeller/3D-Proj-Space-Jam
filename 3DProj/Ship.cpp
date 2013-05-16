#include "DXUT.h"
#include "Ship.h"
#include "EmptyProject.h"
#include "World.h"
Ship::Ship(void)
{
}

Ship::~Ship(void)
{

}

void Ship::Init(ID3D11Device* device,World* w, Mesh* m)
{
	mesh = m;
	pos = XMFLOAT3(0,0,0);
	vel = XMFLOAT3(0,0,0);
	scale = XMFLOAT3(1,1,1);
	fwd = XMFLOAT3(0,0,-1);
	up = XMFLOAT3(0,1,0);
	right = XMFLOAT3(-1,0,0);

	fireCooldown = .5f;
	timeSinceFire=0;
	canFire=true;

	maxVel2 = .028;
	vdec = .9999;

	XMStoreFloat4x4(&mWorldNoTransl,XMMatrixIdentity());

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

	mat.Ambient  = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	mat.Diffuse  = XMFLOAT4(0.77f, 0.77f, 1.0f, 1.0f);
	mat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);
	worldPTR = w;

	HR(D3DX11CreateShaderResourceViewFromFile(device,mesh->texturePath,0,0,&mDiffuseSRV,0));

	
}

void Ship::push(float speed)
{
	vel.x += fwd.x*(speed/100);
	vel.y += fwd.y*(speed/100);
	vel.z += fwd.z*(speed/100);

	// calculate velocity squared
	float vel2 = vel.x * vel.x + vel.y * vel.y + vel.z * vel.z;

	if (vel2 >= maxVel2)
	{
		// temporarily use vel2 for the sake of clamping
		vel2 = sqrt(vel2);
		float tempvel = sqrt(maxVel2);

		vel.x = (vel.x / vel2) * tempvel;
		vel.y = (vel.y / vel2) * tempvel;
		vel.z = (vel.z / vel2) * tempvel;
	}
// 	vel.x = fwd.x*.1;
// 	vel.y = fwd.y*.1;
// 	vel.z = fwd.z*.1;
}

void Ship::strafe(float speed)
{
// 	vel.x += right.x*(speed/1000);
// 	vel.y += right.y*(speed/1000);
// 	vel.z += right.z*(speed/1000);
// 
// 	// calculate velocity squared
// 	float vel2 = vel.x * vel.x + vel.y * vel.y + vel.z * vel.z;
// 
// 	if (vel2 >= maxVel2)
// 	{
// 		// temporarily use vel2 for the sake of clamping
// 		vel2 = sqrt(vel2);
// 
// 		vel.x = (vel.x / vel2) * maxVel2;
// 		vel.y = (vel.y / vel2) * maxVel2;
// 		vel.z = (vel.z / vel2) * maxVel2;
// 	}
}

void Ship::update(float dt)
{
	if(canFire==false)
	{
		timeSinceFire+=dt;
		if(timeSinceFire>fireCooldown)
		{
			timeSinceFire=0;
			canFire=true;
		}
	}
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;

	vel.x *= vdec;
	vel.y *= vdec;
	vel.z *= vdec;
// 	vel.x=0;
// 	vel.y=0;
// 	vel.z=0;
}