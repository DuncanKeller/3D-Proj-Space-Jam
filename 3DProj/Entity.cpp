#include "DXUT.h"
#include "Entity.h"
#include "EmptyProject.h"
#include "World.h"

Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

void Entity::Init(ID3D11Device* md3dDevice,World* w)
{
	
//     D3D11_BUFFER_DESC vbd;
//     vbd.Usage = D3D11_USAGE_IMMUTABLE;
//     vbd.ByteWidth = sizeof(Vertex) * 4;
//     vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//     vbd.CPUAccessFlags = 0;
//     vbd.MiscFlags = 0;
// 	vbd.StructureByteStride = 0;
//     D3D11_SUBRESOURCE_DATA vinitData;
//     vinitData.pSysMem = vertices;
// 	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &vertexBuffer));
// 
// 	// index buffer
// 	UINT ground[] = {
// 		 0, 1, 2,
// 		 0, 2, 3
// 	};
// 
// 	D3D11_BUFFER_DESC ibd2;
//     ibd2.Usage = D3D11_USAGE_IMMUTABLE;
//     ibd2.ByteWidth = sizeof(UINT) * 6;
//     ibd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
//     ibd2.CPUAccessFlags = 0;
//     ibd2.MiscFlags = 0;
// 	ibd2.StructureByteStride = 0;
//     D3D11_SUBRESOURCE_DATA iinitData2;
//     iinitData2.pSysMem = ground;
//     HR(md3dDevice->CreateBuffer(&ibd2, &iinitData2, &indexBuffer));
	worldPTR = w;
}

void Entity::Update()
{
}

void Entity::Draw(ID3D11DeviceContext* context, ID3DX11EffectTechnique* tech)
{
	//XMMATRIX I = XMMatrixIdentity();
	XMVECTOR translate = XMLoadFloat3(&pos);
	//XMVECTOR scaleVect=  XMLoadFloat3(&scale);

	XMMATRIX I=XMLoadFloat4x4(&mWorldNoTransl);
	I=I*XMMatrixTranslationFromVector(translate);
	XMStoreFloat4x4(&mWorld, I);
	

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
	worldPTR->mainApp->mfxMaterial->SetRawValue(&mat, 0, sizeof(mat));

	worldPTR->mainApp->mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	worldPTR->mainApp->SetDiffuseMap(mDiffuseSRV);

	D3DX11_TECHNIQUE_DESC techDesc;
    tech->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        tech->GetPassByIndex(p)->Apply(0, context);
        
		// 6 indices for the box.
		context->DrawIndexed(vertNum, 0, 0);
    }
}