#pragma once
#include "scenenode.h"
class BoundingSphere;

class BoundingShape :
	public SceneNode
{
public:
	BoundingShape(void);
	~BoundingShape(void);
	void AddBoundingSpheres(BoundingSphere* sphere);
	
	// Intersection testing
	virtual bool IsIntersecting(SceneNode* otherShape);

	wstring GetType(void)const;
	float GetRadius(void);
	XMVECTOR* GetCenter(void);

	virtual void SetDelete(bool deleteValue);
	virtual bool DeleteMe(void);

	wstring GetName(void);

protected:

	XMVECTOR* vertices;
	XMVECTOR* _center;
	XMMATRIX _worldMatrix;

	float _radius;
	float _x;
	float _y;
	float _z;

	bool _collision;

	virtual void UpdateBoundingShape(XMMATRIX* matWorld);
};

