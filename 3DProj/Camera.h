#pragma once
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include "Entity.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);
	void Init(XMFLOAT4X4* view, Entity* targ);
	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);

	void Update();

	XMFLOAT3 pos;
	XMFLOAT3 up;
	XMFLOAT3 right;
	XMFLOAT3 target;

	float fwdOffset;
	float upOffset;

	Entity* targetEntity;

	XMFLOAT4X4* viewMat;
};

