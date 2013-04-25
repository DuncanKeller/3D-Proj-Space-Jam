//***************************************************************************************
// BoxDemo.cpp by Frank Luna (C) 2011 All Rights Reserved.
//
// Demonstrates rendering a colored box.
//
// Controls:
//		Hold the left mouse button down and move the mouse to rotate.
//      Hold the right mouse button down to zoom in and out.
//
//***************************************************************************************

#include "DXUT.h"
#include "EmptyProject.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	BoxApp theApp(hInstance);
	
	if( !theApp.Init() )
		return 0;
	
	return theApp.Run();
}
 

BoxApp::BoxApp(HINSTANCE hInstance)
: D3DApp(hInstance), mFX(0), mTech(0),
  mfxWorldViewProj(0), mInputLayout(0), 
  mTheta(.5f*MathHelper::Pi), mPhi(0.25f*MathHelper::Pi), mRadius(40.0f)
{
	mMainWndCaption = L"Box Demo";
	
	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	wDown = false;
	aDown = false;
	sDown = false;
	dDown = false;
	eDown = false;
	qDown = false;
	spaceDown =  false;
	XMMATRIX I = XMMatrixIdentity();
	//XMStoreFloat4x4(&mWorld, I);
	XMStoreFloat4x4(&mView, I);
	XMStoreFloat4x4(&mProj, I);

	// Directional light.
	mDirLight.Ambient  = XMFLOAT4(0.1f, 0.1f, 0.2f, 1.0f);
	mDirLight.Diffuse  = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLight.Specular = XMFLOAT4(0.5f, 0.5f, 0.8f, 1.0f);
	mDirLight.Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);

	mPointLight.Ambient  = XMFLOAT4(0.1f, 0.0f, 0.0f, 1.0f);
	mPointLight.Diffuse  = XMFLOAT4(0.6f, 0.0f, 0.0f, 1.0f);
	mPointLight.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	mPointLight.Att      = XMFLOAT3(0.1f, 0.05f, 0.0f);
	mPointLight.Range    =50.0f;
	mPointLight.Position = XMFLOAT3(0.0f,20.0f,20.0f);

	//mPointLight2.Ambient  = XMFLOAT4(0.0f, 0.1f, 0.0f, 1.0f);
	//mPointLight2.Diffuse  = XMFLOAT4(0.0f, 0.6f, 0.0f, 1.0f);
	//mPointLight2.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 8.0f);
	mPointLight2.Ambient  = XMFLOAT4(0.0f, 0.1f, 0.0f, 1.0f);
	mPointLight2.Diffuse  = XMFLOAT4(0.0f, 0.6f, 0.0f, 1.0f);
	mPointLight2.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	mPointLight2.Att      = XMFLOAT3(0.1f, 0.05f, 0.0f);
	mPointLight2.Range    =50.0f;
	mPointLight2.Position = XMFLOAT3(0.0f,20.0f,20.0f);

	//mShipMat.Ambient  = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
	//mShipMat.Diffuse  = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
	//mShipMat.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);
}

BoxApp::~BoxApp()
{
	
	ReleaseCOM(mFX);
	ReleaseCOM(mInputLayout);
}

bool BoxApp::Init()
{
	if(!D3DApp::Init())
		return false;
	GetWindowRect(mhMainWnd,&rc);
	int midX= (rc.right+rc.left)/2;
	int midY= (rc.top+rc.bottom)/2;
	mLastMousePos.x = midX;
	mLastMousePos.y = midY;
	SetCursorPos(midX,midY);
	ClipCursor(&rc);
	w = new World();
	w->Init(md3dDevice,this);

	cam = new Camera();
	cam->Init(&mView, w->playerShip);

	//SetCapture(mhMainWnd);
	ShowCursor(false);

	BuildGeometryBuffers();
	BuildFX();
	BuildVertexLayout();

	return true;
}

void BoxApp::OnResize()
{
	D3DApp::OnResize();

	// The window resized, so update the aspect ratio and recompute the projection matrix.
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);

	GetWindowRect(mhMainWnd,&rc);
	//ClipCursor(&rc);
}

void BoxApp::UpdateScene(float dt)
{
	POINT mousepos;
	GetCursorPos(&mousepos);
	int mousex=mousepos.x;
	int mousey=mousepos.y;

	// Make each pixel correspond to a quarter of a degree.
	float dx = 0.25f*static_cast<float>(mousex - mLastMousePos.x);
	float dy = 0.25f*static_cast<float>(mousey - mLastMousePos.y);

	cam->Pitch(dy);
	cam->Yaw(dx);
	
	// Update angles based on input to orbit camera around box.
	//mTheta -= dx;
	//mPhi   -= dy;

	// Restrict the angle mPhi.
	//mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi-0.1f);

	int midX= (rc.right+rc.left)/2;
	int midY= (rc.top+rc.bottom)/2;

 	//
	mLastMousePos.x = midX;
	mLastMousePos.y = midY;
	SetCursorPos(midX,midY);

	w->projManager.Update(dt);
	if(wDown==true)
	{
		w->playerShip->pos.x=w->playerShip->fwd.x*.015+w->playerShip->pos.x;
		w->playerShip->pos.y=w->playerShip->fwd.y*.015+w->playerShip->pos.y;
		w->playerShip->pos.z=w->playerShip->fwd.z*.015+w->playerShip->pos.z;
	}
	if(aDown==true)
	{
		w->playerShip->pos.x=w->playerShip->right.x*-.015+w->playerShip->pos.x;
		w->playerShip->pos.y=w->playerShip->right.y*-.015+w->playerShip->pos.y;
		w->playerShip->pos.z=w->playerShip->right.z*-.015+w->playerShip->pos.z;
	}
	if(sDown==true)
	{
		w->playerShip->pos.x=w->playerShip->fwd.x*-.015+w->playerShip->pos.x;
		w->playerShip->pos.y=w->playerShip->fwd.y*-.015+w->playerShip->pos.y;
		w->playerShip->pos.z=w->playerShip->fwd.z*-.015+w->playerShip->pos.z;
	}
	if(dDown==true)
	{
		w->playerShip->pos.x=w->playerShip->right.x*.015+w->playerShip->pos.x;
		w->playerShip->pos.y=w->playerShip->right.y*.015+w->playerShip->pos.y;
		w->playerShip->pos.z=w->playerShip->right.z*.015+w->playerShip->pos.z;
	}
	if(eDown==true)
	{
		cam->Roll(-.05);
	}
	if(qDown==true)
	{
		cam->Roll(.05);
	}
	if(spaceDown==true)
	{
		w->projManager.Fire(w->playerShip->mWorldNoTransl,w->playerShip->pos,w->playerShip->fwd,0,0);
	}
	// Convert Spherical to Cartesian coordinates.
	float x = mRadius*sinf(mPhi)*cosf(mTheta);
	float z = mRadius*sinf(mPhi)*sinf(mTheta);
	float y = mRadius*cosf(mPhi);

	mPointLight.Position=XMFLOAT3(10.0f,10.0f,20.0f*sinf(2.0f*mTimer.TotalTime() ));
	mPointLight2.Position=XMFLOAT3(-10.0f,10.0f,20.0f*-1.0f*sinf(2.0f*mTimer.TotalTime() ));
	// Build the view matrix.
	XMVECTOR pos    = XMVectorSet(x, y, z, 1.0f);
	//XMVECTOR target = XMVectorZero();
	//XMVECTOR up     = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	cam->Update();
// 	XMVECTOR fwd = XMLoadFloat3(&w->playerShip->fwd);
// 	XMVECTOR up = XMLoadFloat3(&w->playerShip->up);
// 	XMVECTOR shippos = XMLoadFloat3(&w->playerShip->pos);
// 	XMVECTOR camerapos = XMVectorAdd(XMVectorAdd(XMVectorScale(up,40.0f),XMVectorScale(fwd,-50.0f)),shippos);
// 	XMVECTOR target = XMVectorAdd(XMVectorScale(fwd,20.0f),shippos);
// 	XMStoreFloat3(&cam->pos,camerapos);
// 	XMMATRIX V = XMMatrixLookAtLH(camerapos, target, up);
// 	XMStoreFloat4x4(&mView, V);

}

void BoxApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&XMFLOAT4(29.0f/255.0f,0.0f/255.0f,48.0f/255.0f,1)));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	md3dImmediateContext->IASetInputLayout(mInputLayout);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set constants
// 	XMMATRIX world = XMLoadFloat4x4(&mWorld);
// 	XMMATRIX view  = XMLoadFloat4x4(&mView);
// 	XMMATRIX proj  = XMLoadFloat4x4(&mProj);
// 	XMMATRIX worldViewProj = world*view*proj;

	//mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));
	mfxDirLight->SetRawValue(&mDirLight, 0, sizeof(mDirLight));
	mfxPointLight->SetRawValue(&mPointLight, 0, sizeof(mPointLight));
	mfxPointLight2->SetRawValue(&mPointLight2, 0, sizeof(mPointLight2));


	float x = mRadius*sinf(mPhi)*cosf(mTheta);
	float z = mRadius*sinf(mPhi)*sinf(mTheta);
	float y = mRadius*cosf(mPhi);

	XMFLOAT3 mEyePosW = XMFLOAT3(x,y,z);
	mfxEyePosW->SetRawValue(&cam->pos, 0, sizeof(cam->pos));
	
	w->Draw(md3dImmediateContext, mTech);

	HR(mSwapChain->Present(0, 0));
}

void BoxApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	//mLastMousePos.x = x;
	//mLastMousePos.y = y;

	//SetCapture(mhMainWnd);
}

void BoxApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	//ReleaseCapture();
}

void BoxApp::OnMouseMove(WPARAM btnState, int x, int y)
{/*
	POINT pos;
	GetCursorPos(&pos);
	x=pos.x;
	y=pos.y;
	if( (btnState & MK_LBUTTON) != 0 )
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		// Update angles based on input to orbit camera around box.
		mTheta -= dx;
		mPhi   -= dy;

		// Restrict the angle mPhi.
		mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi-0.1f);
	}
	else if( (btnState & MK_RBUTTON) != 0 )
	{
		// Make each pixel correspond to 0.005 unit in the scene.
		float dx = 0.005f*static_cast<float>(x - mLastMousePos.x);
		float dy = 0.005f*static_cast<float>(y - mLastMousePos.y);

		// Update the camera radius based on input.
		mRadius += dx - dy;

		// Restrict the radius.
		mRadius = MathHelper::Clamp(mRadius, 30.0f, 50.0f);
	}
	else if(mLastMousePos.x!=0&&mLastMousePos.y!=0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(10.0f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(10.0f*static_cast<float>(y - mLastMousePos.y));

		// Update angles based on input to orbit camera around box.
		mTheta -= dx;
		mPhi   -= dy;

		// Restrict the angle mPhi.
		mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi-0.1f);
	}
	
	int midX= (rc.right+rc.left)/2;
	int midY= (rc.top+rc.bottom)/2;

 	if(x<midX-100||x>midX+100)
 		x=midX;
 	if(y<midY-100||y>midY+100)
 		y=midY;
	mLastMousePos.x = x;
	mLastMousePos.y = y;
	SetCursorPos(x,y);
	*/

}

void BoxApp::OnKeyDown(WPARAM keyState)
{
	switch(keyState)
	{
	case 'W':
		wDown = true;
		break;
	case 'S':
		sDown = true;
		break;
	case 'A':
		aDown = true;
		break;
	case 'D':
		dDown = true;
		break;
	case 'E':
		eDown = true;
		break;
	case 'Q':
		qDown = true;
		break;
	case ' ':
		spaceDown = true;
		break;
	case 0x1B:
		exit(0);
		break;
	};
}

void BoxApp::OnKeyUp(WPARAM keyState)
{
	switch(keyState)
	{
	case 'W':
		wDown = false;
		break;
	case 'S':
		sDown = false;
		break;
	case 'A':
		aDown = false;
		break;
	case 'D':
		dDown = false;
		break;
	case 'E':
		eDown = false;
		break;
	case 'Q':
		qDown = false;
		break;
	case ' ':
		spaceDown = false;
		break;
	};
};

void BoxApp::BuildGeometryBuffers()
{

	
}
 
void BoxApp::BuildFX()
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
 
	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DX11CompileFromFile(L"FX/Lighting.fx", 0, 0, 0, "fx_5_0", shaderFlags, 
		0, 0, &compiledShader, &compilationMsgs, 0);

	// compilationMsgs can store errors or warnings.
	if( compilationMsgs != 0 )
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		ReleaseCOM(compilationMsgs);
	}

	// Even if there are no compilationMsgs, check to make sure there were no other errors.
	if(FAILED(hr))
	{
		DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
	}

	HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 
		0, md3dDevice, &mFX));

	// Done with compiled shader.
	ReleaseCOM(compiledShader);

	mTech                = mFX->GetTechniqueByName("LightTech");
	mfxWorldViewProj     = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	mfxWorld             = mFX->GetVariableByName("gWorld")->AsMatrix();
	mfxWorldInvTranspose = mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	mfxEyePosW           = mFX->GetVariableByName("gEyePosW")->AsVector();
	mfxDirLight          = mFX->GetVariableByName("gDirLight");
	mfxPointLight        = mFX->GetVariableByName("gPointLight");
	mfxPointLight2       = mFX->GetVariableByName("gPointLight2");
	mfxSpotLight         = mFX->GetVariableByName("gSpotLight");
	mfxMaterial          = mFX->GetVariableByName("gMaterial");

	diffuseMap = mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
}

void BoxApp::BuildVertexLayout()
{
	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
    D3DX11_PASS_DESC passDesc;
    mTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(md3dDevice->CreateInputLayout(vertexDesc, 3, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &mInputLayout));
}

void BoxApp::SetDiffuseMap( ID3D11ShaderResourceView* tex )
{
	diffuseMap->SetResource(tex);
}

