#include "DXUT.h"
#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

bool Mesh::Load( std::string path )
{
	filePath = path;
	FILE* file;
	if ((file = fopen(filePath.c_str(), "r")) == NULL)
	{
		MessageBox(0, L"Error opening file", 0, 0);
		return false;
	}

	float xMax, xMin, yMax, yMin, zMax, zMin;
	xMax = -FLT_MAX; yMax = -FLT_MAX; zMax = -FLT_MAX;
	xMin = FLT_MAX; yMin = FLT_MAX; zMin = FLT_MAX;

	std::vector<Vertex> verts = std::vector<Vertex>();
	std::vector<Vertex> faceVerts = std::vector<Vertex>();
	std::vector<int> tris = std::vector<int>();
	std::vector<XMFLOAT3>norms = std::vector<XMFLOAT3>();
	std::vector<XMFLOAT2>vertTex = std::vector<XMFLOAT2>();
	char lineHeader[128];
	while(true)
	{
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; 
		else
		{
			if(strcmp(lineHeader, "v")==0)
			{
				Vertex v;
				float x,y,z;
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				v.Pos = XMFLOAT3(x,y,-1.0f*z);
				//v.Color = (const float*)&Colors::Silver;
				v.Norm = XMFLOAT3(0,0,0);
				//v.Color = XMFLOAT4(1,x,y,z);
				verts.push_back(v);
				// check max and min values
				if(x > xMax) {
					xMax = x;
				} else if(x < xMin) {
					xMin = x;
				}
				if(y > yMax) {
					yMax = y;
				} else if(y < yMin) {
					yMin = y;
				}
				if(z > zMax) {
					zMax = z;
				} else if(z < zMin) {
					zMin = z;
				}
			}
			else if(strcmp(lineHeader, "vn")==0)
			{
				XMFLOAT3 norm;
				float x,y,z;
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				norm = XMFLOAT3(x,y,-1.0f*z);
				norms.push_back(norm);
			}
			else if(strcmp(lineHeader, "vt")==0)
			{
				XMFLOAT2 vertT;
				float x,y;
				fscanf(file, "%f %f\n",&x,&y);
				vertT = XMFLOAT2(x,-1.0f*y);
				vertTex.push_back(vertT);
			}
			else if ( strcmp( lineHeader, "f" ) == 0 )
			{
				int v1,v2,v3;
				int t1,t2,t3;
				int n1,n2,n3;
				fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v1,&t1,&n1,&v2,&t2,&n2,&v3,&t3,&n3);
				//tris.push_back(v3-1);
				//tris.push_back(v2-1);
				//tris.push_back(v1-1);

				verts[v1-1].Norm=norms[n1-1];
				verts[v2-1].Norm=norms[n2-1];
				verts[v3-1].Norm=norms[n3-1];

				verts[v1-1].TexVert=vertTex[t1-1];
				verts[v2-1].TexVert=vertTex[t2-1];
				verts[v3-1].TexVert=vertTex[t3-1];

				faceVerts.push_back(verts[v3-1]);
				faceVerts.push_back(verts[v2-1]);
				faceVerts.push_back(verts[v1-1]);
				tris.push_back(faceVerts.size()-3);
				tris.push_back(faceVerts.size()-2);
				tris.push_back(faceVerts.size()-1);
			}
		}

		// set bounding box
		bounding = new BoundingBox(xMin, xMax, yMin, yMax, zMin, zMax);
	}

	numVerts = faceVerts.size();
	numInd = tris.size();

	vertices = new Vertex[faceVerts.size()]();
	indices = new int[tris.size()]();

	for(int i=0; i<faceVerts.size();i++)
	{
		vertices [i] = faceVerts[i];
	}
	for(int i=0;i<tris.size();i++)
	{
		indices[i] = tris[i];
	}
}
