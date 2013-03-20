#ifndef MESH_H
#define MESH_H

#include "DXUT.h"
#include <d3dx11.h>
#include <xnamath.h>
#include <string>
#include <vector>
#include "d3dUtil.h"

#include "Sphere.h"
/*struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct TStruct
{
	Vertex v0, v1, v2;
};*/

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);

	bool Load(std::string path);

	Vertex* vertices;
	TStruct* triangles;
	int* indices;

	std::string filePath;
};

#endif