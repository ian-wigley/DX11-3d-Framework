//-----------------------------------------------------------------------------
// File: Tree.cpp
// Description : This Class managers the Tree
//-----------------------------------------------------------------------------

#include "Tree.h"

Tree::Tree(void)
{
}

Tree::Tree(wstring name, Framework* frame, float x, float z, FrameWorkResourceManager* _frameResourcesManager)
{
	this->m_scale = 10.0f;
	_name = name;
	_frame = frame;
//	_pd3dDevice = _frame->GetDirect3dDevice();
	_terrainNode = _frame->GetTerrain();

	_frameWorkResourcesManager = _frameResourcesManager;
//	_mesh = _frameWorkResourcesManager->GetMesh(L"tree.x", true);
//	_material = _frameWorkResourcesManager->GetMaterial(L"Tree.x");
	_numberOfMaterials = _frameWorkResourcesManager->GetNumberOfMaterials();
	_delete = false;
	this->m_x = x;
	this->m_z = z;
	this->m_y = _terrainNode->GetHeight(this->m_x, this->m_z) + 20.0f;
}

Tree::~Tree(void)
{
	Shutdown();
}

void Tree::Shutdown(void)
{
	/*
	if(_texture)
	{
		SAFE_RELEASE(_texture);
	}
	if(_mesh)
	{
		SAFE_DELETE(_mesh);
	}
	if(_pd3dDevice)
	{
		SAFE_RELEASE(_pd3dDevice);
	}
	*/
}

HRESULT Tree::Render(void)
{
	/*
	XMMATRIXTranslation(&_translationMatrix, _x, _y, _z);	

	XMMATRIXScaling(&_scalingingMatrix,_scale,_scale,_scale);

	_worldMatrix = _scalingingMatrix *_translationMatrix;

	_pd3dDevice->SetTransform(D3DTS_WORLD, &_worldMatrix);

	// ALL Render methods should call the world transform matrix.....
	_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	for (DWORD i=0; i < _numberOfMaterials; i++)
	{
		// Draw the mesh subsets
		_mesh->DrawSubset(i);
	}
	*/
	return S_OK;
}