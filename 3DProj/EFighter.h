#ifndef EFIGHTER_H
#define EFIGHTER_H
#include "Entity.h"
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dUtil.h"
#include "Mesh.h"

class EStation;
class EFighter : public Entity
{
public:
	EFighter(void);
	~EFighter(void);
	void Init(ID3D11Device* device,World* w, XMFLOAT3 startPos, Mesh* m);
	void Update();
	void Attack();
	bool IsActive();
	void GoActive();
private:
	EStation* station;
	Entity* target;
	float distanceToTarget;
	bool active;
	int attackTimer;
};
#endif



