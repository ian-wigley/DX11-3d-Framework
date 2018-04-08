#pragma once
#include "boundingsphere.h"

class BoundingBlox :
	public BoundingShape
{
public:
	BoundingBlox(ID3D11Device* device, float x, float y, float z, wstring name, float scale);
	~BoundingBlox(void);

	HRESULT Render(void);
	bool IsIntersecting(SceneNode* otherShape);
	void UpdateBoundingShape(XMMATRIX& worldMatrix);

	XMFLOAT3 GetBoxMax(void);
	XMFLOAT3 GetBoxMin(void);
	XMFLOAT3 GetFrontLeftVector(void)const;
	XMFLOAT3 GetFrontMidVector(void)const;
	XMFLOAT3 GetFrontRightVector(void)const;
	XMFLOAT3 GetRearMidVector(void)const;

private:

	ID3D11Device* _device;

	void CreateBoundingBlox(void);

	XMFLOAT3 _boxMin;
	XMFLOAT3 _boxMax;
	XMFLOAT3 _center;

	XMMATRIX _rotationMatrix;
	XMMATRIX _translationMatrix;

	vector<XMVECTOR> _verts;

	XMVECTOR	_oobCornerVertices[8];
	XMVECTOR	_worldCornerVertices[8];

	float _angle;

	float _width;
	float _length;
	float _height;

	BoundingBlox* _box1;
	BoundingBlox* _box2;
	bool CheckDirectionX(void);
	bool CheckDirectionZ(void);
};

