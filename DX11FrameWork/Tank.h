#pragma once
#include "scenenode.h"
#include "SceneGraph.h"
#include "Framework.h"
#include "FrameWorkResourceManager.h"
#include "TerrainNode.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "BoundingBlox.h"
//#include "CameraRender.h"
#include "Camera.h"
#include "BulletNode.h"
#include <d3d11_1.h>
#include <directxmath.h>


class Tank :
	public SceneNode
{
public:
	Tank(void);
	Tank(wstring name, Framework* frame, float x, float z, FrameWorkResourceManager* frameResourcesManager);
	~Tank(void);
	HRESULT Render(void);
	void Update(void);
	void MoveForward(float amountOfMovement);
	void Yaw(float amountOfMovement);
	void FireBullet(void);

	void SetPosition(XMVECTOR distance);
	void SetCameraType(bool cameraType);
	void Shutdown();

private:

	void TextDisplay();
	void CalculateRoll(float opposite, float hypotenuse);
	void CalculatePitch(float opposite, float hypotenuse);

	bool _collsion;
	bool _thirdPerson;
	bool _fire;

	float _xOpposite;
	float _xHypotenuse;

	float _zOpposite;;
	float _zHypotenuse;

	float h1;
	float _terrainExtent;

	int _bulletCount;

	BoundingShape* _boundingShape;
	BoundingSphere* _boundingSphere;
	BoundingBlox* _boundingBox;

	BulletNode* _bullet;

//	CameraRender* _renderCam;
	Camera* _renderCam;

	Framework* _frame;
	FrameWorkResourceManager* _frameWorkResourcesManager;
	SceneGraph* _sGraph;
	TerrainNode* _terrainNode;
	
//	ID3DXFont* mFont;
	XMFLOAT3 _tankFrontLeftPos;
	XMFLOAT3 _tankFrontMidPos;
	XMFLOAT3 _tankFrontRightPos;
	XMFLOAT3 _tankRearMidPos;
};

