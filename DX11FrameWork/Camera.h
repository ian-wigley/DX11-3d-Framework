#pragma once

#include <string>
#include <Windows.h>
#include <d3d11.h>
#include <directxmath.h>

#include "CameraNode.h"

//#define _XM_NO_INTRINSICS_
using namespace DirectX;

class TerrainNode;
class Tank;

class Camera :
	public CameraNode
{
public:
	~Camera(void);

	Camera(ID3D11DeviceContext* deviceContext, TerrainNode* terrainNode, Tank* tank);

	void Update(void);
		
	void MoveForward(float amountOfMovement);
	void MoveRight(float amountOfMovement);
	void MoveUp(float amountOfMovement);

	void Roll(float amountOfMovement);
	void Yaw(float amountOfMovement);
	void Pitch(float amountOfMovement);

	void SetForward(void);
	void SetPosition(XMVECTOR _gamepadPosition);
	void SetPosition(float x, float y, float z);
	void SetLookAt(const XMVECTOR &position, float angle);
	void SetCameraType(bool cameraType);

	bool GetCameraType(void);

	XMVECTOR GetPosition(void)const;
	XMVECTOR GetLookAt(void)const;
	XMVECTOR GetRight(void)const;
	XMMATRIX GetViewMatrix(void)const;

private:

	XMMATRIX _viewMatrix;
	XMMATRIX _projectionMatrix;

	//XMMATRIX	viewTransformation;
	//XMMATRIX	projectionTransformation;
	//XMMATRIX	worldTransformation;

	XMVECTOR _defaultForward;
	//XMVECTOR _defaultRight;
	XMVECTOR _defaultUp;

	XMVECTOR _cameraForward;
	XMVECTOR _cameraUp;
	XMVECTOR _cameraRight;
	XMVECTOR _cameraPosition;
	XMVECTOR  cameraTarget;

	float _moveLeftRight;
	float _moveForwardBack;
	float _cameraYaw;
	float _cameraPitch;
	float _cameraRoll;
	float _offsetHeight;
	float _cameraSpeed;
	float _fogStart;
	float _fogEnd;
	float _angle;
	//float	amountOfMovement;

	bool _thirdPerson;

	//	TerrainNode* _terrain;
	//	Tank* _tank;

	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	float yaw, pitch, roll;

	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector; 
	XMVECTOR positionVector; 
	XMVECTOR lookAtVector;
	XMMATRIX rotationMatrix;
};