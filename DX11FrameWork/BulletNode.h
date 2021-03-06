#pragma once
#include "scenenode.h"
#include "SceneGraph.h"
#include "Framework.h"
#include "FrameWorkResourceManager.h"
#include "TerrainNode.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "BoundingBlox.h"
#include "ExplosionNode.h"


class BulletNode :
	public SceneNode
{
public:
	BulletNode(void);
	BulletNode::BulletNode(wstring name, Framework* frame, XMFLOAT3& position, float angle, FrameWorkResourceManager* frameResourcesManager);
	~BulletNode(void);
	HRESULT Render(void);
	void Update(void);
	bool DeleteMe(void);
	void ExternalDeleteMe(bool deleteMe);
	void SetCamera(Camera* _cameraRender);

private:
	void Shutdown(void);
	HRESULT InitialiseBullet(void);

	float m_maxDistance;
	float m_startDistance;

	BoundingShape* _boundingShape;
	BoundingSphere* _boundingSphere;
	Camera* m_camRender;
	Framework* _frame;
	FrameWorkResourceManager* _frameWorkResourcesManager;
	SceneGraph* _sGraph;
	TerrainNode* m_terrainNode;
	ExplosionNode* _explosion;
};

