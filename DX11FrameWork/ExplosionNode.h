#pragma once
#include "scenenode.h"
#include "Framework.h"
#include "FrameWorkResourceManager.h"
#include "TerrainNode.h"

class ExplosionNode :
	public SceneNode
{
public:
	ExplosionNode(void);
	ExplosionNode::ExplosionNode(wstring name, Framework* frame, XMVECTOR position, FrameWorkResourceManager* frameResourcesManager);
	~ExplosionNode(void);
	HRESULT Render(void);
	void Update(void);
	bool DeleteMe(void);


	// The format of our vertices
	struct VERTEX
	{
		   XMFLOAT3 Position;  // position
		   XMFLOAT3 Normal;    // normal
		   XMFLOAT2 TexCoord;   // Texture UV Coordinates
	};

	//struct CUSTOMVERTEX
	//{
	//	FLOAT x, y, z;      // The untransformed, 3D position for the vertex
	//	XMVECTOR normal; // The normal for the vertex
	//	FLOAT u, v;			// Texture coordinates
	//};

	//// Custom FVF, which describes our custom vertex structure
	//#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

	void Shutdown(void);

private:

	float _u1;
	float _u2;

	HRESULT InitialiseExplosion(void);

	Framework* _frame;
	FrameWorkResourceManager* _frameWorkResourcesManager;
};

