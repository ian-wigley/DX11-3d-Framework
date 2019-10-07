#pragma once

#include <string>
#include <Windows.h>
#include <d3d11.h>
//#include <d3d11_1.h>
#include <directxmath.h>

//#define _XM_NO_INTRINSICS_
using namespace DirectX;

class TerrainNode;
class Tank;

class Camera
{
public:
	~Camera(void);

	Camera(ID3D11DeviceContext* deviceContext, TerrainNode* terrainNode, Tank* tank);

	void Update(void);

	void SetPosition(float x, float y, float z);

	void MoveForward(float amountOfMovement);
	void MoveRight(float amountOfMovement);
	void MoveUp(float amountOfMovement);
//
//	void Roll(float amountOfMovement);
//	void Yaw(float amountOfMovement);
//	void Pitch(float amountOfMovement);
//
//	void SetForward(void);
//	void SetPosition(XMVECTOR _gamepadPosition);
//	void SetLookAt(const XMVECTOR &position, float angle);
//	void SetCameraType(bool cameraType);
//	
//	bool GetCameraType(void);
//
//	XMVECTOR GetPosition(void)const;
//	XMVECTOR GetLookAt(void)const;
//	XMVECTOR GetRight(void)const;
	XMMATRIX GetViewMatrix(void)const;
//	
//
//	struct CBUFFER
//	{
//		 XMMATRIX    CompleteTransformation;
////		 XMMATRIX    World;
////		 XMMATRIX    Transformation;
////		 XMMATRIX	 Rotation;
////		 XMVECTOR    LightVector;
////		 XMFLOAT4    LightColor;
////		 XMFLOAT4    AmbientColor;
//	 };
//
//
//
private:
////	ID3D11Device* _device;
////	ID3D11DeviceContext* _deviceContext;
////	ID3D11Buffer* _constantBuffer;
////	CBUFFER* _cBuffer;

	XMMATRIX	_viewMatrix;
	XMMATRIX	_projectionMatrix;

//	XMMATRIX	viewTransformation;
//	XMMATRIX	projectionTransformation;
//	XMMATRIX	worldTransformation;
//
//	XMVECTOR    _defaultForward;
//    XMVECTOR    _defaultRight;
//    XMVECTOR    _defaultUp;
//
    XMVECTOR    _cameraForward;
    XMVECTOR    _cameraUp;
    XMVECTOR    _cameraRight;
    XMVECTOR    _cameraPosition;
	XMVECTOR     cameraTarget;

	float       _moveLeftRight;
    float       _moveForwardBack;
    float       _cameraYaw;
    float       _cameraPitch;
    float       _cameraRoll;
	float		_offsetHeight;
	float		_cameraSpeed;
	float		_fogStart;
	float		_fogEnd;

	float		_angle;
//
//
//	float		amountOfMovement;
//	
//	bool _thirdPerson;
//
//	TerrainNode* _terrain;
//	Tank* _tank;


	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;





};


