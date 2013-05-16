#include "DXUT.h"
#include "Skybox.h"
#include "World.h"
#include "EmptyProject.h"


Skybox::Skybox( void )
{

}

Skybox::~Skybox( void )
{

}

void Skybox::Init( ID3D11Device* device, World* w, Mesh* m )
{
	mesh = m;

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

	worldPTR = w;
}

void Skybox::Update()
{
	XMVECTOR translate = XMLoadFloat3(&(worldPTR->playerShip->pos));
	XMMATRIX scale = XMMatrixScalingFromVector(XMLoadFloat3(&XMFLOAT3(500.0f,500.0f,500.0f)));
	XMMATRIX I=XMMatrixIdentity();
	I=I*scale*XMMatrixTranslationFromVector(translate);
	XMStoreFloat4x4(&mWorld,I);
}

void Skybox::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	XMMATRIX world = XMLoadFloat4x4(&mWorld);
	XMMATRIX view  = XMLoadFloat4x4(&(worldPTR->mainApp->mView));
	XMMATRIX proj  = XMLoadFloat4x4(&(worldPTR->mainApp->mProj));
	XMMATRIX worldViewProj = world*view*proj;

	XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);

	worldPTR->mainApp->mfxWorld->SetMatrix(reinterpret_cast<float*>(&world));
	worldPTR->mainApp->mfxWorldInvTranspose->SetMatrix(reinterpret_cast<float*>(&worldInvTranspose));
	worldPTR->mainApp->mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	worldPTR->mainApp->mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));


	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc( &techDesc );
	for(UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech->GetPassByIndex(p)->Apply(0, context);

		context->DrawIndexed(vertNum, 0, 0);
	}
}
