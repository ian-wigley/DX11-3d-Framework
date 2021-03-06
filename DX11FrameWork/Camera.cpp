//-----------------------------------------------------------------------------
// File: Camera.cpp
// Description : This Class managers the Camera
//-----------------------------------------------------------------------------

#include "Camera.h"

Camera::Camera(ID3D11DeviceContext* deviceContext, TerrainNode* terrainNode, Tank* tank)
{
	//_cameraPosition = XMVectorSet(0.0f, -130.0f, -400.0f, 0.0f);
	// Set the initial camera position
	m_positionX = 0.0f;
	m_positionY = 40.0f;
	m_positionZ = 0.0f;// -1000.0f;

	// Set the initial camera rotation
	m_rotationX = 0.0f;
	m_rotationY = 1.0f;
	m_rotationZ = 0.0f;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3(&up);

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&lookAt);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	_thirdPerson = false;

	//_angle = 0;
	//_terrain = terrainNode;
	//_tank = tank;

	//_offsetHeight = 10.0f;
	_cameraSpeed = 5.0f;

	//_position.y = _terrain->GetHeight(_position.x,_position.z) + _offsetHeight;
	//float _y = _terrain->GetHeight(0.0f, 0.0f) + _offsetHeight;
	//XMVectorSetY(_position, _y);

	//_fogStart = 400.0f;
	//_fogEnd = 2000.0f;

	//_moveLeftRight = 0.0f;
	//_moveForwardBack = 0.0f;

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
	//XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3(&up);

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&lookAt);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = this->m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);

	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	// Rotate the position vector to move the camera in the correct orientation
	positionVector = XMVector3TransformCoord(positionVector, rotationMatrix);
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
	m_positionZ += amountOfMovement;
}

//-----------------------------------------------------------------------------
// Name: MoveRight()
// Desc: Move Camera Right
//-----------------------------------------------------------------------------
void Camera::MoveRight(float amountOfMovement)
{
	m_positionY += amountOfMovement;
}

//-----------------------------------------------------------------------------
// Name: MoveUp()
// Desc: Move Camera Up
//-----------------------------------------------------------------------------
void Camera::MoveUp(float amountOfMovement)
{
	m_positionY += amountOfMovement;
}

//-----------------------------------------------------------------------------
// Name: Roll()
// Desc: Roll The Camera
//-----------------------------------------------------------------------------
void Camera::Roll(float amountOfMovement)
{
	//_cameraRoll += amountOfMovement;
	//XMMATRIX cameraRotationRoll = XMMatrixRotationAxis(_cameraForward, _cameraRoll);
	//_cameraUp = XMVector3TransformCoord(_cameraUp, cameraRotationRoll);
	//_cameraRight = XMVector3TransformCoord(_cameraRight, cameraRotationRoll);
}

//-----------------------------------------------------------------------------
// Name: Yaw()
// Desc: Yaw The Camera
//-----------------------------------------------------------------------------
void Camera::Yaw(float amountOfMovement)
{
	m_rotationY += amountOfMovement;
}

//-----------------------------------------------------------------------------
// Name: Pitch()
// Desc: Pitch The Camera
//-----------------------------------------------------------------------------
void Camera::Pitch(float amountOfMovement)
{
	_cameraPitch += amountOfMovement;
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

//void Camera::SetPosition(XMVECTOR _gamepadPosition)
//{
//	_cameraPosition = _gamepadPosition;
//}

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
