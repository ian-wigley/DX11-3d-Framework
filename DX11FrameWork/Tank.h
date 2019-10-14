#pragma once
#include "scenenode.h"
#include "SceneGraph.h"
#include "Framework.h"
#include "FrameWorkResourceManager.h"
#include "TerrainNode.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "BoundingBlox.h"
#include "BulletNode.h"
//#include "CameraRender.h"
#include "Camera.h"

__declspec(align(16)) class Tank :
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
	void SetCamera(Camera* _cameraRender);

private:
	void TextDisplay();
	void CalculateRoll(float opposite, float hypotenuse);
	void CalculatePitch(float opposite, float hypotenuse);
	HRESULT InitialiseTank(void);

	bool m_collsion;
	bool m_thirdPerson;
	bool m_fire;
	float m_xOpposite;
	float m_xHypotenuse;
	float m_zOpposite;;
	float m_zHypotenuse;
	float m_terrainExtent;
	int m_bulletCount;

	BoundingShape* _boundingShape;
	//BoundingSphere* _boundingSphere;
	//BoundingBlox* _boundingBox;
	BulletNode* _bullet;
	//CameraRender* _renderCam;
	SceneGraph* m_sGraph;
	//TerrainNode* m_terrainNode;
	Camera* m_camRender;
	Framework* m_frame;
	FrameWorkResourceManager* m_frameWorkResourcesManager;

	//ID3DXFont* mFont;
	XMFLOAT3 m_tankFrontLeftPos;
	XMFLOAT3 m_tankFrontMidPos;
	XMFLOAT3 m_tankFrontRightPos;
	XMFLOAT3 m_tankRearMidPos;

	vector<Mesh> meshy;
};