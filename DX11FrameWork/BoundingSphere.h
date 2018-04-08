#pragma once
#include "boundingshape.h"
#include "BoundingBlox.h"
#include "Framework.h"

class BoundingSphere :
	public BoundingShape
{
public:
	BoundingSphere(void);
	BoundingSphere(ID3D11Device* device, float x, float y, float z, wstring name, float scale);

	~BoundingSphere(void);
	
	HRESULT Render(void);
	void Update(void);

	// Intersection testing
	bool IsIntersecting(SceneNode* otherShape);

	void UpdateBoundingShape(XMMATRIX* matWorld);
	bool GetCollision(void);

	void SetDelete(bool deleteValue);
	bool DeleteMe(void);
	float GetRadius(void);
	XMVECTOR GetCenter(void);

private:
	void CreateBoundingSphere(void);
	XMVECTOR _center;
	bool _collision;
	float _radius;

	Framework* _frame;
};

