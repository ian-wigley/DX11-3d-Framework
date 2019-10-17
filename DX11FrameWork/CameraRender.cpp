//-----------------------------------------------------------------------------
// File: CameraRender.cpp
// Description : This Class managers the Rendering of the Camera
//-----------------------------------------------------------------------------

#include "CameraRender.h"
//#include "TerrainNode.h"
//#include "Tank.h"
//#include "Renderer.h"

//XMVECTOR _up;
//XMVECTOR _lookAt;
//XMVECTOR _right;
//XMVECTOR _position;

////-----------------------------------------------------------------------------
//// Name: CameraRender()
//// Desc: CameraRender Class Constructor
////-----------------------------------------------------------------------------
////CameraRender::CameraRender(LPDIRECT3DDEVICE9 pd3dDevice , TerrainNode* terrainNode, Tank* tank)
//CameraRender::CameraRender(ID3D11Device* device, TerrainNode* terrainNode, Tank* tank)
//{
////	XMStoreFloat4x4(&_viewMatrix), XMMatrixIdentity());
//	Renderer();
//
//
//XMVECTOR defaultForward = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//_defaultForward = defaultForward;
//
//    _defaultForward = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//    _defaultRight = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//    _defaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//    _cameraForward = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//    _cameraUp  = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//    _cameraRight  = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//    _cameraPosition  = XMVectorSet(0.0f, 1.0f, -100000.0f, 0.0f);
//	
//
//	XMMATRIX Identity (_viewMatrix);
//
//	_thirdPerson = false;
//
////	_angle = 0;
//	_terrain = terrainNode;
//	_tank = tank;
////	_pd3dDevice = pd3dDevice;
//
////	_device = device;
//	
//	_offsetHeight = 10.0f;
//	_cameraSpeed = 5.0f;
//
////	yaw = 0.0f;						// Degrees of yaw (in radians)
////	pitch = 0.0f;					// Degrees of pitch (in radians)
////	roll = 0.0f;
//
//	_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//	_lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
//	_right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
//
//	_position = XMVectorSet(0.0f, 0.0f, -5500.0f, 0.0f);
//	//_position.y = _terrain->GetHeight(_position.x,_position.z) + _offsetHeight;
//	float _y = _terrain->GetHeight(0.0f, 0.0f) + _offsetHeight;
//	XMVectorSetY(_position, _y);
//	_fogStart = 400.0f;
//	_fogEnd = 2000.0f;
//
// //   XMMATRIX    _viewMatrix;
//
//    _moveLeftRight = 0.0f;
//    _moveForwardBack = 0.0f;
//
//    _cameraYaw = 0.0f;
//    _cameraPitch = 0.0f;
//    _cameraRoll = 0.0f;;
//
//}

//-----------------------------------------------------------------------------
// Name: ~CameraRender()
// Desc: CameraRender Class Destructor
//-----------------------------------------------------------------------------
CameraRender::~CameraRender(void)
{
}

////-----------------------------------------------------------------------------
//// Name: Render()
//// Desc: Render the scene
////-----------------------------------------------------------------------------
//HRESULT CameraRender::Render(void)
//{
//	/*
//	_viewMatrix._11 = _right.x;
//	_viewMatrix._21 = _right.y;
//	_viewMatrix._31 = _right.z;
//
//	_viewMatrix._12 = _up.x;
//	_viewMatrix._22 = _up.y;
//	_viewMatrix._32 = _up.z;
//
//	_viewMatrix._13 = _lookAt.x;
//	_viewMatrix._23 = _lookAt.y;
//	_viewMatrix._33 = _lookAt.z;
//
//	_viewMatrix._41 = -D3DXVec3Dot(&_position, &_right);
//	_viewMatrix._42 = -D3DXVec3Dot(&_position, &_up);
//	_viewMatrix._43 = -D3DXVec3Dot(&_position, &_lookAt);
//
//	_pd3dDevice->SetTransform( D3DTS_VIEW, &_viewMatrix);
//
//	// Enable Fog
//	_pd3dDevice->SetRenderState(D3DRS_FOGENABLE,true);
//	_pd3dDevice->SetRenderState(D3DRS_RANGEFOGENABLE,true);
//	_pd3dDevice->SetRenderState(D3DRS_FOGCOLOR,D3DCOLOR_XRGB(128,128,128));
//	_pd3dDevice->SetRenderState(D3DRS_FOGVERTEXMODE,D3DFOG_LINEAR);
//	_pd3dDevice->SetRenderState(D3DRS_FOGSTART,*(DWORD*)(&_fogStart));
//	_pd3dDevice->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&_fogEnd));
//	*/
//	return S_OK;
//}
//
////-----------------------------------------------------------------------------
//// Name: Update()
//// Desc: Updates the scene
////-----------------------------------------------------------------------------
//void CameraRender::Update(void)
//{
//
//
//    XMMATRIX cameraRotationYaw = XMMatrixRotationAxis(_defaultUp, _cameraYaw);
//    _cameraRight = XMVector3TransformCoord(_defaultRight, cameraRotationYaw);
//    _cameraForward = XMVector3TransformCoord(_defaultForward, cameraRotationYaw);
//
//    XMMATRIX cameraRotationPitch = XMMatrixRotationAxis(_cameraRight, _cameraPitch);
//    _cameraUp = XMVector3TransformCoord(_defaultUp, cameraRotationPitch);
//    _cameraForward = XMVector3TransformCoord(_cameraForward, cameraRotationPitch);
//
//    XMMATRIX cameraRotationRoll = XMMatrixRotationAxis(_cameraForward, _cameraRoll);
//    _cameraUp = XMVector3TransformCoord(_cameraUp, cameraRotationRoll);
//    _cameraRight = XMVector3TransformCoord(_cameraRight, cameraRotationRoll);
//
//    _cameraPosition += _moveLeftRight * _cameraRight;
//    _cameraPosition += _moveForwardBack * _cameraForward;
//
//    _moveLeftRight = 0.0f;
//    _moveForwardBack = 0.0f;
//
//    XMVECTOR cameraTarget = _cameraPosition + XMVector3Normalize(_cameraForward);
//
//   _viewMatrix = XMMatrixLookAtLH(_cameraPosition, cameraTarget, _cameraUp);
//
//
//
//
//
//
//
//	/*
//	if(!_thirdPerson)
//	{
//		_position.y = _terrain->GetHeight(_position.x,_position.z) + _offsetHeight;
//	}
//
//	_up = XMVECTOR(0.0f, 1.0f, 0.0f);
//	_lookAt = XMVECTOR(0.0f, 0.0f, 1.0f);
//	_right = XMVECTOR(1.0f, 0.0f, 0.0f);
//
//	// Rotate lookat and right vectors around the up vector
//	XMMATRIXRotationAxis(&yawMatrix, &_up, yaw);
//	D3DXVec3TransformCoord(&_lookAt, &_lookAt, &yawMatrix);
//	D3DXVec3TransformCoord(&_right, &_right, &yawMatrix);
//
//	// Rotate lookat and up vectors around the right vector
//	XMMATRIXRotationAxis(&pitchMatrix, &_right, pitch);
//	D3DXVec3TransformCoord(&_lookAt, &_lookAt, &pitchMatrix);
//	D3DXVec3TransformCoord(&_up, &_up, &pitchMatrix);
//
//	// Rotate right and up vectors around the lookat vector
//	XMMATRIXRotationAxis(&rollMatrix, &_lookAt, roll);
//	D3DXVec3TransformCoord(&_right, &_right, &rollMatrix);
//	D3DXVec3TransformCoord(&_up, &_up, &rollMatrix);
//
//	XMMATRIXA16 matProj;
//	XMMATRIXPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 10000.0f );
//	_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
//	*/
//}
//
////-----------------------------------------------------------------------------
//// Name: SetLookAt()
//// Desc: Get the position of tank away from the camera
////-----------------------------------------------------------------------------
//void CameraRender::SetLookAt(const XMVECTOR &position, float angle)
//{
////	_angle = angle;
///*
//	targetPosition.x = position.x;
//	targetPosition.y = position.y + 20.0f;
//	targetPosition.z = position.z;
//
//	_position.x = position.x;
//	_position.y = position.y + 20.0f;
//	_position.z = position.z -100;
//	*/
//}
//
////-----------------------------------------------------------------------------
//// Name: MoveForward()
//// Desc: Move Camera Forward
////-----------------------------------------------------------------------------
//void CameraRender::MoveForward(float amountOfMovement)
//{
//	_position += _lookAt * amountOfMovement * _cameraSpeed;
//}
//
////-----------------------------------------------------------------------------
//// Name: MoveRight()
//// Desc: Move Camera Right
////-----------------------------------------------------------------------------
//void CameraRender::MoveRight(float amountOfMovement)
//{
//	_position += _right * amountOfMovement * _cameraSpeed;
//}
//
////-----------------------------------------------------------------------------
//// Name: MoveUp()
//// Desc: Move Camera Up
////-----------------------------------------------------------------------------
//void CameraRender::MoveUp(float amountOfMovement)
//{
//	_position += _up * amountOfMovement;
//}
//
////-----------------------------------------------------------------------------
//// Name: Roll()
//// Desc: Roll The Camera
////-----------------------------------------------------------------------------
//void CameraRender::Roll(float amountOfMovement)
//{
////	roll += amountOfMovement;
//}
//
////-----------------------------------------------------------------------------
//// Name: Yaw()
//// Desc: Yaw The Camera
////-----------------------------------------------------------------------------
//void CameraRender::Yaw(float amountOfMovement)
//{
////	yaw += amountOfMovement;
////	Render();
//}
//
////-----------------------------------------------------------------------------
//// Name: Pitch()
//// Desc: Pitch The Camera
////-----------------------------------------------------------------------------
//void CameraRender::Pitch(float amountOfMovement)
//{
////	pitch += amountOfMovement;
//}
//
////Accessors
//XMVECTOR CameraRender::GetPosition(void)const
//{
//	return _position;
//}
//
//XMVECTOR CameraRender::GetLookAt(void)const
//{
//	return _lookAt;
//}
//	
//XMVECTOR CameraRender::GetRight(void)const
//{
//	return _right;
//}	
//
//void CameraRender::SetPosition(XMVECTOR _gamepadPosition)
//{
//	_position = _gamepadPosition;
//}
//
//XMMATRIX CameraRender::GetViewMatrix(void)const
//{
//	return _viewMatrix;
//}
//
////-----------------------------------------------------------------------------
//// Name: SetCameraType()
//// Desc: Changes between 1st and 3rd person camera
////-----------------------------------------------------------------------------
//void CameraRender::SetCameraType(bool cameraType)
//{
//	_thirdPerson = cameraType;
//}
//
////-----------------------------------------------------------------------------
//// Name: GetCameraType()
//// Desc: Returns the camera type
////-----------------------------------------------------------------------------
//bool CameraRender::GetCameraType(void)
//{
//	return _thirdPerson;
//}