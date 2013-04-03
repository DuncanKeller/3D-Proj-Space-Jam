#pragma once
#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>

class Camera
{
public:
	Camera(void);
	~Camera(void);
	void Render();

	XMFLOAT3 pos;
	XMFLOAT3 up;
	XMFLOAT3 right;
	XMFLOAT3 target;

};

