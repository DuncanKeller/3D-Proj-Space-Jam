#include "DXUT.h"
#include "Camera.h"


Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}

void Camera::Update()
{
	XMVECTOR targfwd = XMLoadFloat3(&targetEntity->fwd);
	XMVECTOR targup = XMLoadFloat3(&targetEntity->up);
	XMVECTOR targpos = XMLoadFloat3(&targetEntity->pos);
	XMVECTOR targright = XMLoadFloat3(&targetEntity->right);

// 	D3DXVec3Normalize(&tarView, &tarView);
// 
// 	D3DXVec3Cross(&tarUp, &tarView, &tarRight);
// 	D3DXVec3Normalize(&tarUp, &tarUp);
// 
// 	D3DXVec3Cross(&tarRight, &tarUp, &tarView);
// 	D3DXVec3Normalize(&tarRight, &tarRight);
// 
// 	// Do the same for the camerafs vectors
// 	D3DXVec3Normalize(&camView, &camView);
// 
// 	D3DXVec3Cross(&camUp, &camView, &camRight);
// 	D3DXVec3Normalize(&camUp, &camUp);
// 
// 	D3DXVec3Cross(&camRight, &camUp, &camView);
// 	D3DXVec3Normalize(&camRight, &camRight);
	targfwd = XMVector3Normalize(targfwd);
	
	targup = XMVector3Cross(targfwd,targright);
	targup = XMVector3Normalize(targup);

	targright = XMVector3Cross(targup,targfwd);
	targright = XMVector3Normalize(targright);

	XMStoreFloat3(&targetEntity->fwd,targfwd);
	XMStoreFloat3(&targetEntity->up,targup);
	XMStoreFloat3(&targetEntity->right,targright);
	
	// calculate target: look at their projected forward
	XMVECTOR target = XMVectorAdd(XMVectorScale(targfwd,20.0f),targpos);
	// += some in the up direction
	target = XMVectorAdd(target,XMVectorScale(targup,10.0f));

	// need the look vector for calculations
	XMVECTOR mypos = XMLoadFloat3(&pos);
	XMVECTOR lookVec = XMVectorSubtract(mypos, target);

	// cross the look and ship vec
	XMVECTOR lookxship = XMVector3Cross(lookVec, targfwd);

	XMVECTOR targvel = XMLoadFloat3(&targetEntity->vel);

	XMVECTOR udDot = XMVector3Dot(targvel,targright);
	XMFLOAT3 udDotf;
	XMStoreFloat3(&udDotf, udDot);

	// http://www.gamedev.net/topic/345149-projecting-a-vector-on-a-plane/
	targvel = XMVectorSubtract(targvel, XMVectorScale(targright,udDotf.x));

	// calculate offsets
	XMVECTOR updown = XMVector3Dot(targfwd, targvel);
	XMFLOAT3 updownf;
	XMStoreFloat3(&updownf,updown);

	XMVECTOR sideside = XMVector3Dot(lookxship, targup);
	XMFLOAT3 sidesidef;
	XMStoreFloat3(&sidesidef,sideside);

	/*if (abs(rightOffset) < maxRO)  
	{
		rightOffset += sidesidef.x;

		if (rightOffset > maxRO) rightOffset = maxRO;
	}*/

	if(enableExperimentalStuff)
	{
		if (updownf.x < 0.0f)upOffset -= .1f;
		else if (updownf.x >= 0.0f) upOffset += .1f;
	}

	if (upOffset > maxUO) upOffset = maxUO;
	else if (upOffset < -maxUO) upOffset = -maxUO;

	fwdOffset = -50 - (targetEntity->vel.x*targetEntity->vel.x + targetEntity->vel.y*targetEntity->vel.y + targetEntity->vel.z*targetEntity->vel.z) * 1000.0f;
	if (fwdOffset > maxFO) fwdOffset = maxFO;
	else if (fwdOffset < -maxFO) fwdOffset = -maxFO;

	XMVECTOR ROVec = XMVectorScale(targright, rightOffset/maxRO);

	//XMVECTOR camerapos = XMVectorAdd(XMVectorAdd(XMVectorAdd(XMVectorScale(targup,upOffset),XMVectorScale(targfwd,fwdOffset)), XMVectorAdd(targright,ROVec)), targpos);
	XMVECTOR camerapos = XMVectorAdd(XMVectorAdd(XMVectorScale(targup,upOffset),XMVectorScale(targfwd,fwdOffset)), targpos);
	XMStoreFloat3(&pos,camerapos);
	

	XMMATRIX V = XMMatrixLookAtLH(camerapos, target, targup);
	XMStoreFloat4x4(viewMat, V);
}

void Camera::Init(XMFLOAT4X4* view, Entity* targ )
{
	maxFO = 150.0f;
	maxUO = 20.0f;
	maxRO = 1.0f;

	viewMat = view;
	targetEntity = targ;
	fwdOffset = -75.0f;
	upOffset = 20.0f;
	rightOffset = 0.0f;

	enableExperimentalStuff = 0;

	Update();
}

void Camera::Yaw(float angle)
{
	XMVECTOR targfwd = XMLoadFloat3(&targetEntity->fwd);
	XMVECTOR targup = XMLoadFloat3(&targetEntity->up);
	XMVECTOR targright = XMLoadFloat3(&targetEntity->right);

	XMVECTOR targpos = XMLoadFloat3(&targetEntity->pos);

	XMMATRIX yaw; 
	yaw = XMMatrixRotationAxis(targup,D3DXToRadian(angle));

	targfwd = XMVector3Transform(targfwd,yaw);
	targright = XMVector3Transform(targright,yaw);

	XMMATRIX targWorld = XMLoadFloat4x4(&targetEntity->mWorldNoTransl);
	targWorld = targWorld*yaw;
	XMStoreFloat4x4(&targetEntity->mWorldNoTransl,targWorld);

	XMStoreFloat3(&targetEntity->fwd,targfwd);
	XMStoreFloat3(&targetEntity->right,targright);

}

void Camera::Pitch(float angle)
{
	XMVECTOR targfwd = XMLoadFloat3(&targetEntity->fwd);
	XMVECTOR targup = XMLoadFloat3(&targetEntity->up);
	XMVECTOR targright = XMLoadFloat3(&targetEntity->right);

	XMVECTOR targpos = XMLoadFloat3(&targetEntity->pos);

	XMMATRIX pitch; 
	pitch = XMMatrixRotationAxis(targright,D3DXToRadian(angle));



	targfwd = XMVector3Transform(targfwd,pitch);
	targup = XMVector3Transform(targup,pitch);

	XMMATRIX targWorld = XMLoadFloat4x4(&targetEntity->mWorldNoTransl);
	targWorld = targWorld*pitch;
	XMStoreFloat4x4(&targetEntity->mWorldNoTransl,targWorld);

	XMStoreFloat3(&targetEntity->fwd,targfwd);
	XMStoreFloat3(&targetEntity->up,targup);

}

void Camera::Roll( float angle )
{
	XMVECTOR targfwd = XMLoadFloat3(&targetEntity->fwd);
	XMVECTOR targup = XMLoadFloat3(&targetEntity->up);
	XMVECTOR targright = XMLoadFloat3(&targetEntity->right);

	XMVECTOR targpos = XMLoadFloat3(&targetEntity->pos);

	XMMATRIX roll; 
	roll = XMMatrixRotationAxis(targfwd,D3DXToRadian(angle));

	targright = XMVector3Transform(targright,roll);
	targup = XMVector3Transform(targup,roll);

	XMMATRIX targWorld = XMLoadFloat4x4(&targetEntity->mWorldNoTransl);
	targWorld = targWorld*roll;
	XMStoreFloat4x4(&targetEntity->mWorldNoTransl,targWorld);

	XMStoreFloat3(&targetEntity->right,targright);
	XMStoreFloat3(&targetEntity->up,targup);

}
