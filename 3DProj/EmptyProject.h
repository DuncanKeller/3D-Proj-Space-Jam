#ifndef EMPTY_PROJ_H
#define EMPTY_PROJ_H

#include "DXUT.h"
#include "d3dApp.h"
#include "d3dx11Effect.h"
#include "MathHelper.h"
#include "World.h"
#include "Camera.h"


class BoxApp : public D3DApp
{
public:
	BoxApp(HINSTANCE hInstance);
	~BoxApp();

	RECT rc;
	RECT rw;
	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene(); 

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

	void OnKeyDown(WPARAM keyState);
	void OnKeyUp(WPARAM keyState);

	void SetDiffuseMap(ID3D11ShaderResourceView* tex);
	
	ID3DX11Effect* mFX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mfxWorld;
	ID3DX11EffectMatrixVariable* mfxWorldInvTranspose;
	ID3DX11EffectVectorVariable* mfxEyePosW;
	ID3DX11EffectVariable* mfxDirLight;
	ID3DX11EffectVariable* mfxPointLight;
	ID3DX11EffectVariable* mfxPointLight2;
	ID3DX11EffectVariable* mfxSpotLight;
	ID3DX11EffectVariable* mfxMaterial;

	ID3DX11EffectShaderResourceVariable* diffuseMap;
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;

	ID3DX11EffectMatrixVariable* mfxWorldViewProj;

	bool wDown;
	bool aDown;
	bool sDown;
	bool dDown;

	Camera* cam;
private:
	void BuildGeometryBuffers();
	void BuildFX();
	void BuildVertexLayout();

private:




	ID3D11InputLayout* mInputLayout;

	//XMFLOAT4X4 mWorld;
	

	float mTheta;
	float mPhi;
	float mRadius;

	POINT mLastMousePos;

	DirectionalLight mDirLight;
	PointLight mPointLight;
	PointLight mPointLight2;
	SpotLight mSpotLight;
	Material mShipMat;

	World* w;
};
#endif