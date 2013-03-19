#pragma once
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);
	// modify to return normal and color
	bool Intersects(/* add ray */);
	virtual void Init(ID3D11Device*);
	void Draw(ID3D11DeviceContext*, ID3DX11EffectTechnique*);

	XMFLOAT3 pos;
	XMFLOAT4 color;

protected:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int vertNum;
private:
	
	
};

