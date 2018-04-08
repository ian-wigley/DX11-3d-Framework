#include "Camera.h"
#include "TerrainNode.h"

Camera::Camera(ID3D11DeviceContext* deviceContext, TerrainNode* terrainNode, Tank* tank)
{
	_defaultForward = XMVectorSet(0.0f, 1.0f, 1.0f, 0.0f);
	_defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	_defaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);// -1.0f

	_cameraForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	_cameraRight = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	_cameraUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//------------------------------------------------------------------------------------------


	_cameraPosition = XMVectorSet(0.0f, -130.0f, -400.0f, 0.0f);

	//_cameraPosition = XMVectorSet(0.0f, -130.0f, -550.0f, 0.0);
	////_cameraPosition = XMVectorSet(-18.7096844, 365.0f, 74.7193985, 0.0);// 625.000000);// 0.0f, -130.0f, -550.0f, 0.0);
	//--------------------------------------------------------------------------------------------

	//	XMMATRIX Identity (_viewMatrix);
	_viewMatrix = XMMatrixIdentity();


	_thirdPerson = false;

	_angle = 0;
	_terrain = terrainNode;
	_tank = tank;

	_offsetHeight = 10.0f;
	_cameraSpeed = 5.0f;

	//_position.y = _terrain->GetHeight(_position.x,_position.z) + _offsetHeight;
	//	float _y = _terrain->GetHeight(0.0f, 0.0f) + _offsetHeight;
	//	XMVectorSetY(_position, _y);

	//	_fogStart = 400.0f;
	//	_fogEnd = 2000.0f;

	_moveLeftRight = 0.0f;
	_moveForwardBack = 0.0f;

	_cameraYaw = 0.0f;
	_cameraPitch = 1.0f;
	_cameraRoll = 0.0f;
}


Camera::~Camera(void)
{
}

//-----------------------------------------------------------------------------
// Name: Update()
// Desc: Update the camera
//-----------------------------------------------------------------------------
void Camera::Update(void)
{
	XMMATRIX cameraRotationYaw = XMMatrixRotationAxis(_defaultUp, _cameraYaw);
	_cameraRight = XMVector3TransformCoord(_defaultRight, cameraRotationYaw);
	_cameraForward = XMVector3TransformCoord(_defaultForward, cameraRotationYaw);

	XMMATRIX cameraRotationPitch = XMMatrixRotationAxis(_cameraRight, _cameraPitch);
	_cameraUp = XMVector3TransformCoord(_defaultUp, cameraRotationPitch);
	_cameraForward = XMVector3TransformCoord(_cameraForward, cameraRotationPitch);


	XMMATRIX cameraRotationRoll = XMMatrixRotationAxis(_cameraForward, _cameraRoll);
	_cameraUp = XMVector3TransformCoord(_cameraUp, cameraRotationRoll);
	_cameraRight = XMVector3TransformCoord(_cameraRight, cameraRotationRoll);

	_cameraPosition += _moveLeftRight * _cameraRight;
	_cameraPosition += _moveForwardBack * _cameraForward;

	_moveLeftRight = 0.0f;
	_moveForwardBack = 0.0f;

	XMVECTOR cameraTarget = _cameraPosition + XMVector3Normalize(_cameraForward);

	_viewMatrix = XMMatrixLookAtLH(_cameraPosition, cameraTarget, _cameraUp);
}


//-----------------------------------------------------------------------------
// Name: SetLookAt()
// Desc: Get the position of tank away from the camera
//-----------------------------------------------------------------------------
void Camera::SetLookAt(const XMVECTOR &position, float angle)
{
	_angle = angle;

	//targetPosition.x = position.x;
	//targetPosition.y = position.y + 20.0f;
	//targetPosition.z = position.z;

	//_position.x = position.x;
	//_position.y = position.y + 20.0f;
	//_position.z = position.z -100;

}

//-----------------------------------------------------------------------------
// Name: MoveForward()
// Desc: Move Camera Forward
//-----------------------------------------------------------------------------
void Camera::MoveForward(float amountOfMovement)
{
	_cameraPosition += _cameraForward * amountOfMovement * _cameraSpeed;
	//	_cameraPosition = _cameraPosition;
	_terrain->UpdateViewMatrix(_viewMatrix);
}

//-----------------------------------------------------------------------------
// Name: MoveRight()
// Desc: Move Camera Right
//-----------------------------------------------------------------------------
void Camera::MoveRight(float amountOfMovement)
{
	_cameraPosition += _cameraRight * amountOfMovement * _cameraSpeed;
}

//-----------------------------------------------------------------------------
// Name: MoveUp()
// Desc: Move Camera Up
//-----------------------------------------------------------------------------
void Camera::MoveUp(float amountOfMovement)
{
	_cameraPosition += _cameraUp * amountOfMovement;
}

//-----------------------------------------------------------------------------
// Name: Roll()
// Desc: Roll The Camera
//-----------------------------------------------------------------------------
void Camera::Roll(float amountOfMovement)
{
	_cameraRoll += amountOfMovement;

	XMMATRIX cameraRotationRoll = XMMatrixRotationAxis(_cameraForward, _cameraRoll);
	_cameraUp = XMVector3TransformCoord(_cameraUp, cameraRotationRoll);
	_cameraRight = XMVector3TransformCoord(_cameraRight, cameraRotationRoll);
}

//-----------------------------------------------------------------------------
// Name: Yaw()
// Desc: Yaw The Camera
//-----------------------------------------------------------------------------
void Camera::Yaw(float amountOfMovement)
{
	_cameraYaw += amountOfMovement;

	XMMATRIX cameraRotationYaw = XMMatrixRotationAxis(_defaultUp, _cameraYaw);
	//    _cameraRight = XMVector3TransformCoord(_defaultRight, cameraRotationYaw);
	_cameraForward = XMVector3TransformCoord(_defaultForward, cameraRotationYaw);

}

//-----------------------------------------------------------------------------
// Name: Pitch()
// Desc: Pitch The Camera
//-----------------------------------------------------------------------------
void Camera::Pitch(float amountOfMovement)
{
	_cameraPitch += amountOfMovement;

	XMMATRIX cameraRotationPitch = XMMatrixRotationAxis(_cameraRight, _cameraPitch);
	_cameraUp = XMVector3TransformCoord(_defaultUp, cameraRotationPitch);
	_cameraForward = XMVector3TransformCoord(_cameraForward, cameraRotationPitch);
}

//Accessors
XMVECTOR Camera::GetPosition(void)const
{
	return _cameraPosition;
}

XMVECTOR Camera::GetLookAt(void)const
{
	return _cameraForward;
}

XMVECTOR Camera::GetRight(void)const
{
	return _cameraRight;
}

void Camera::SetPosition(XMVECTOR _gamepadPosition)
{
	_cameraPosition = _gamepadPosition;
}

XMMATRIX Camera::GetViewMatrix(void)const
{
	return _viewMatrix;
}

//-----------------------------------------------------------------------------
// Name: SetCameraType()
// Desc: Changes between 1st and 3rd person camera
//-----------------------------------------------------------------------------
void Camera::SetCameraType(bool cameraType)
{
	_thirdPerson = cameraType;
}

//-----------------------------------------------------------------------------
// Name: GetCameraType()
// Desc: Returns the camera type
//-----------------------------------------------------------------------------
bool Camera::GetCameraType(void)
{
	return _thirdPerson;
}

