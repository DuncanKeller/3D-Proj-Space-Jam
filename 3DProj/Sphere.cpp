#include "DXUT.h"
#include "Sphere.h"

Sphere::Sphere(float cx, float cy, float cz, float r)
{
	centerx = cx;
	centery = cy;
	centerz = cz;
	radius = r;
	vertNum = 60;
}

Sphere::~Sphere(void)
{

}

std::vector<TStruct> Sphere::Divide(std::vector<TStruct> t)
{
	std::vector<TStruct> newTri;
	for(int i = 0; i < t.size(); i++)
	{
		XMFLOAT3 ta(t[i].v0.Pos);
		XMFLOAT3 tb(t[i].v1.Pos);
		XMFLOAT3 tc(t[i].v1.Pos);

		Vertex va;
		va.Pos = ta;
		va.Color = (const float*)&Colors::Green;
		Vertex vb;
		vb.Pos = tb;
		vb.Color = (const float*)&Colors::Green;
		Vertex vc;
		vc.Pos = tc;
		vc.Color = (const float*)&Colors::Green;

		Vertex vert1;
		vert1.Pos = XMFLOAT3(ta.x + tb.x, ta.y + tb.y, ta.z + tb.z);
		vert1.Color = (const float*)&Colors::Green;
		Vertex vert2;
		vert2.Pos = XMFLOAT3(ta.x + tc.x, ta.y + tc.y, ta.z + tc.z);
		vert2.Color = (const float*)&Colors::Green;
		Vertex vert3;
		vert3.Pos = XMFLOAT3(tc.x + tb.x, tc.y + tb.y, tc.z + tb.z);
		vert3.Color = (const float*)&Colors::Green;

		float mag1 = sqrt( (vert1.Pos.x * vert1.Pos.x) + (vert1.Pos.y * vert1.Pos.y) + (vert1.Pos.z * vert1.Pos.z) );
		float mag2 = sqrt( (vert2.Pos.x * vert2.Pos.x) + (vert2.Pos.y * vert2.Pos.y) + (vert2.Pos.z * vert2.Pos.z) );
		float mag3 = sqrt( (vert3.Pos.x * vert3.Pos.x) + (vert3.Pos.y * vert3.Pos.y) + (vert3.Pos.z * vert3.Pos.z) );
		
		vert1.Pos = XMFLOAT3(vert1.Pos.x / mag1, vert1.Pos.y / mag1, vert1.Pos.z / mag1);
		vert2.Pos = XMFLOAT3(vert2.Pos.x / mag2, vert2.Pos.y / mag1, vert2.Pos.z / mag2);
		vert3.Pos = XMFLOAT3(vert3.Pos.x / mag3, vert3.Pos.y / mag1, vert3.Pos.z / mag3);
		
		TStruct t0; t0.v0 = vert1; t0.v1 = vert3; t0.v2 = vert2;  
		TStruct t1; t0.v0 = va; t0.v1 = vert1; t0.v2 = vert2;  
		TStruct t2; t0.v0 = vc; t0.v1 = vert2; t0.v2 = vert3;  
		TStruct t3; t0.v0 = vb; t0.v1 = vert3; t0.v2 = vert1;

		newTri.push_back(t0);
		newTri.push_back(t1);
		newTri.push_back(t2);
		newTri.push_back(t3);
	}
	return newTri;
}
void Sphere::Init(ID3D11Device* device)
{
	int levels = 0;

	float t = (1 + sqrt(5.0)) / 2.0;
	float s = sqrt(1 + pow(t,2));

	// Create vertex buffer
    Vertex vertices[] =
    {
		{ XMFLOAT3(t + centerx,   1 + centery, 0 + centerz), (const float*)&Colors::Red },
		{ XMFLOAT3(-t + centerx,  1 + centery, 0 + centerz), (const float*)&Colors::White },
		{ XMFLOAT3(t + centerx,  -1 + centery, 0 + centerz), (const float*)&Colors::Black },

		{ XMFLOAT3(-t + centerx, -1 + centery, 0 + centerz), (const float*)&Colors::Yellow   },
		{ XMFLOAT3(1 + centerx,   0 + centery, t + centerz), (const float*)&Colors::Green   },
		{ XMFLOAT3(1 + centerx,   0 + centery, -t + centerz), (const float*)&Colors::Blue   },

		{ XMFLOAT3(-1 + centerx, -0 + centery, t + centerz), (const float*)&Colors::Red   },
		{ XMFLOAT3(-1 + centerx,  0 + centery, -t + centerz), (const float*)&Colors::White   },
		{ XMFLOAT3(0 + centerx,   t + centery, 1 + centerz), (const float*)&Colors::Black   },

		{ XMFLOAT3(0 + centerx,  -t + centery, 1 + centerz), (const float*)&Colors::Yellow   },
		{ XMFLOAT3(0 + centerx,   t + centery, -1 + centerz), (const float*)&Colors::Green   },
		{ XMFLOAT3(0 + centerx,  -t + centery, -1 + centerz), (const float*)&Colors::Blue   },

	};

	TStruct triangles[] =
    {
		{ vertices[0],  vertices[8],  vertices[4] },
		{ vertices[1],  vertices[10], vertices[7] },
		{ vertices[2],  vertices[9],  vertices[11] },
		{ vertices[7],  vertices[3],  vertices[1] },

		{ vertices[0],  vertices[5],  vertices[10] },
		{ vertices[3],  vertices[9],  vertices[6] },
		{ vertices[3],  vertices[11], vertices[9] },
		{ vertices[8],  vertices[6],  vertices[4] },

		{ vertices[2],  vertices[4],  vertices[9] },
		{ vertices[3],  vertices[7],  vertices[11] },
		{ vertices[4],  vertices[2],  vertices[0] },
		{ vertices[9],  vertices[4],  vertices[6] },

		{ vertices[2],  vertices[11], vertices[5] },
		{ vertices[0],  vertices[10], vertices[8] },
		{ vertices[5],  vertices[0],  vertices[2] },
		{ vertices[10], vertices[5],  vertices[7] },

		{ vertices[1],  vertices[6],  vertices[8] },
		{ vertices[1],  vertices[8],  vertices[10] },
		{ vertices[6],  vertices[1],  vertices[3] },
		{ vertices[11], vertices[7],  vertices[5] }
	};

	int indexB[] =
    {
		 0,  8,  4 ,
		 1,  10, 7 ,
		 2,  9,  11 ,
		 7,  3,  1 ,

		 0,  5,  10 ,
		 3,  9,  6 ,
		 3,  11, 9 ,
		 8,  6,  4 ,

		 2,  4,  9 ,
		 3,  7,  11 ,
		 4,  2,  0 ,
		 9,  4,  6 ,

		 2,  11, 5 ,
		 0,  10, 8 ,
		 5,  0,  2 ,
		 10, 5,  7 ,

		 1,  6,  8 ,
		 1,  8,  10 ,
		 6,  1,  3 ,
		 11, 7,  5 
	};

	std::vector<TStruct> tri(triangles, triangles + sizeof(triangles) / sizeof(triangles[0]));

	for(int i = 0; i < levels; i++)
	{
		tri = Divide(tri);
	}

    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(Vertex) * 12;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = vertices;
	HR(device->CreateBuffer(&vbd, &vinitData, &vertexBuffer));

	D3D11_BUFFER_DESC ibd2;
    ibd2.Usage = D3D11_USAGE_IMMUTABLE;
    ibd2.ByteWidth = sizeof(UINT) * 60;
    ibd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd2.CPUAccessFlags = 0;
    ibd2.MiscFlags = 0;
	ibd2.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData2;
    iinitData2.pSysMem = indexB;
    HR(device->CreateBuffer(&ibd2, &iinitData2, &indexBuffer));
}