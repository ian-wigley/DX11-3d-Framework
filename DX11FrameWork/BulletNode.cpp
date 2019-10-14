//-----------------------------------------------------------------------------
// File: BulletNode.cpp
// Description : This Class managers the Bullets fired from the Tank
//-----------------------------------------------------------------------------

#include "BulletNode.h"

VERTEX bulletVertices[] =
{
	{XMFLOAT3(-1.0f, -1.0f, 1.0f),  XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(0.0f, 0.0f)},    // side 1
	{XMFLOAT3(1.0f, -1.0f, 1.0f),   XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(0.0f, 1.0f)},
	{XMFLOAT3(-1.0f, 1.0f, 1.0f),   XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(1.0f, 0.0f)},
	{XMFLOAT3(1.0f, 1.0f, 1.0f),    XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(1.0f, 1.0f)},
};

DWORD bulletIndices[] =
{
	0, 1, 2,       // side 1
	2, 1, 3,
};

BulletNode::BulletNode(void)
{
}

//-----------------------------------------------------------------------------
// Name: Constructor
// Desc: Creates the Bullet
//-----------------------------------------------------------------------------
BulletNode::BulletNode(wstring name, Framework* frame, XMFLOAT3& position, float angle, FrameWorkResourceManager* frameResourcesManager)
{
	this->m_position = position;
	this->m_maxDistance = 200.0f + this->m_position.z;
	this->m_scale = 0.0f;
	this->m_angle = angle;
	this->m_x = this->m_position.x;
	this->m_y = this->m_position.y + 9.0f;
	this->m_z = this->m_position.z;
	_name = name;
	_frame = frame;
	//	_texture = NULL;
	_collsion = false;
	_delete = false;
	this->m_device = _frame->GetDirectDevice();
	this->m_deviceContext = _frame->GetDirectDeviceContext();
	_sGraph =_frame->GetSceneGraph();

	this->m_terrainNode = _frame->GetTerrain();
	_frameWorkResourcesManager = frameResourcesManager;
	//_materials = _frameWorkResourcesManager->GetDefaultBlackMaterial();
	InitialiseBullet();
	//	_sGraph->AddNode(_boundingSphere = new BoundingSphere(_mesh, _pd3dDevice, _x,_y,_z, L"boundingSphere", _scale),L"Parent");
}

//-----------------------------------------------------------------------------
// Name: InitialiseBullet()
// Desc: Initialises the Bullet object
//-----------------------------------------------------------------------------
HRESULT BulletNode::InitialiseBullet(void)
{
	m_numVertices = unsigned(size(bulletVertices) * 3);
	m_numIndices = unsigned(size(bulletIndices));
	m_vertices = bulletVertices;
	m_indices = bulletIndices;

	InitialiseGeometry();

#pragma region Load texture from file

	// Load a DDS texture
	if (FAILED(CreateDDSTextureFromFile(this->m_device, L"woodbox.dds", nullptr, &this->m_texture)))
	{
		return S_OK;
	}
#pragma endregion

	// Set the rasterizer state
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	//rd.AntialiasedLineEnable = false;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = false;
	rd.FillMode = D3D11_FILL_SOLID;
	this->m_device->CreateRasterizerState(&rd, &this->m_wireFrame);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: ~BulletNode()
// Desc: BulletNode Class Destructor
//-----------------------------------------------------------------------------
BulletNode::~BulletNode(void)
{
	Shutdown();
}

//-----------------------------------------------------------------------------
// Name: Shutdown()
// Desc: Deletes the textures, meshes etc
//-----------------------------------------------------------------------------
void BulletNode::Shutdown(void)
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

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
HRESULT BulletNode::Render(void)
{
	XMMATRIX viewTransformation = _camRender->GetViewMatrix();
	XMMATRIX completeTransformation = this->m_scalingMatrix * this->m_worldTransformation * viewTransformation * this->m_projectionTransformation;

	CBUFFER cBuffer;
	cBuffer.LightVector = XMVector4Normalize(XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	cBuffer.LightColor = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	cBuffer.AmbientColor = XMFLOAT4(0.44f, 0.57f, 0.74f, 1.0f);
	cBuffer.CompleteTransformation = completeTransformation;
	cBuffer.WorldTransformation = this->m_worldTransformation;

	// Update the constant buffer with the complete transformation
	this->m_deviceContext->VSSetConstantBuffers(0, 1, &this->m_constantBuffer);
	this->m_deviceContext->UpdateSubresource(this->m_constantBuffer, 0, 0, &cBuffer, 0, 0);

	// Set the texture to be used by the pixel shader
	this->m_deviceContext->PSSetShaderResources(0, 1, &this->m_texture);
	//_deviceContext->PSSetSamplers(0, 1, &g_pSamLinear);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	this->m_deviceContext->IASetVertexBuffers(0, 1, &this->m_vertexBuffer, &stride, &offset);
	this->m_deviceContext->IASetIndexBuffer(this->m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	this->m_deviceContext->RSSetState(NULL);
	this->m_deviceContext->RSSetState(this->m_wireFrame);
	this->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_deviceContext->DrawIndexed(m_numIndices, 0, 0);

	/*
	XMMATRIXTranslation(&_translationMatrix, _x, _y, _z);
	XMMATRIXRotationY(&_rotationMatrixY, _angle);
	_worldMatrix = _rotationMatrixY * _translationMatrix;
	_pd3dDevice->SetTransform(D3DTS_WORLD, &_worldMatrix);
	_pd3dDevice->SetMaterial(&_materials);
	_mesh->DrawSubset(0);
	_boundingSphere->UpdateBoundingShape(&_worldMatrix);
	*/
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Update()
// Desc: Updates the Bullet
//-----------------------------------------------------------------------------
void BulletNode::Update(void)
{
	float _bulletHeight = this->m_terrainNode->GetHeight(this->m_x, this->m_z);
	
	if (this->m_z < this->m_maxDistance)
	{
		// 240 degrees to 180 degrees
		if(this->m_angle < -0.80f && this->m_angle > -1.60f || this->m_angle > 0.80f && this->m_angle < 1.60f)
		{
			this->m_z -= 2.0f;
			this->m_x += this->m_angle;
		}

		// 180 degrees to 90 degrees
		else if(this->m_angle < -1.60f && this->m_angle > -2.40f || this->m_angle > 1.60f && this->m_angle < 2.40f)
		{
			this->m_z -= 2.0f;
			this->m_x += (this->m_angle*-1);
		}

		else if (this->m_angle > 2.4f && this->m_angle < 4.0f)
		{
			this->m_z += 2.0f;
			this->m_x -= (this->m_angle - 2.4f);
		}

		else if (this->m_angle < -2.4f && this->m_angle > -4.0f)
		{
			this->m_z += 2.0f;
			this->m_x += (this->m_angle + 2.4f) * -1;
		}

		else
		{
			this->m_z += 2.0f;
			this->m_x += this->m_angle;
		}
	}

	// Bullet has reached the end of it's travel or collided the terrain
	if(this->m_z >= this->m_maxDistance || this->m_y < _bulletHeight)
	{
		_delete = true;
		_boundingSphere->SetDelete(true);
		
		//update the position vector
		//		_position.x = _x;
		//		_position.y = _y;
		//		_position.z = _z;

		//		_sGraph->AddNode(_explosion = new ExplosionNode(L"ExplosionNode", _frame, _position, _frameWorkResourcesManager),L"Parent");
	}
}

bool BulletNode::DeleteMe(void)
{
	return _delete;
}

void BulletNode::ExternalDeleteMe(bool deleteMe)
{
	_delete = deleteMe;
	_boundingSphere->SetDelete(true);
		
	//update the position vector
	//	_position.x = _x;
	//	_position.y = _y;
	//	_position.z = _z;
	
	//	_sGraph->AddNode(_explosion = new ExplosionNode(L"ExplosionNode", _frame, _position, _frameWorkResourcesManager),L"Parent");
}