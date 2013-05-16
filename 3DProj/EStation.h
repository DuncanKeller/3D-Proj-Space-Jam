#ifndef ESTATION_H
#define ESTATION_H

#include "Entity.h"
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"
#include "Mesh.h"


#include "EFighter.h"

class EFighter;
class EStation  : public Entity
{
public:
	EStation(void);
	~EStation(void);
	void Init(ID3D11Device* device,World* w, XMFLOAT3 startPos, Mesh* m);
	void Update();
	bool SpawnFighter();
	void Fire();
	void KillFighter(EFighter* f);

	int fighterTimer;

	std::vector<EFighter*> GetFighters();
		std::vector<EFighter*> fighters;

private:
	int currentFighters;

	
	World* gWorld;
	ID3D11Device* device;
};
#endif

