#pragma once
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"
#include "Mesh.h"

class World;
class Entity
{
public:
	Entity(void);
	~Entity(void);
	// modify to return normal and color
	bool Intersects(/* add ray */);
	virtual void Init(ID3D11Device*,World*);
	void Draw(ID3D11DeviceContext*, ID3DX11EffectTechnique*);

	XMFLOAT3 pos;
	XMFLOAT3 scale;
	XMFLOAT3 fwd;
	XMFLOAT3 up;
	XMFLOAT3 right;
	XMFLOAT4 color;

	XMFLOAT4X4 mWorldNoTransl;
	XMFLOAT4X4 mWorld;
	World* worldPTR;
	Material mat;
	ID3D11ShaderResourceView* mDiffuseSRV;
protected:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int vertNum;
private:
	
	
};

