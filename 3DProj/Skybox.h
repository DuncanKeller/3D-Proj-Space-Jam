#ifndef SKYBOX_H
#define SKYBOX_H
#include "Entity.h"
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"
#include "Mesh.h"

class World;

class Skybox
{
public:
	Skybox(void);
	~Skybox(void);
	void Init(ID3D11Device* device, World* w, Mesh* m);
	void Update();
	void Draw(ID3D11DeviceContext*, ID3DX11EffectTechnique*);

private:
	World* gWorld;
	ID3D11Device* device;
	XMFLOAT4X4 mWorld;
	World* worldPTR;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int vertNum;
	Mesh* mesh;
};


#endif