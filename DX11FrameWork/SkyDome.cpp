//-----------------------------------------------------------------------------
// File: SkyDome.cpp
// Description : This Class managers the SkyDome

//-----------------------------------------------------------------------------

#include "SkyDome.h"

//-----------------------------------------------------------------------------
// Name: SkyDome()
// Desc: SkyDome Class Constructor
//-----------------------------------------------------------------------------
SkyDome::SkyDome(void)
{
}

//-----------------------------------------------------------------------------
// Name: SkyDome()
// Desc: SkyDome Class Constructor
//-----------------------------------------------------------------------------
SkyDome::SkyDome(wstring name, Framework* frame, FrameWorkResourceManager* _frameResourcesManager)
{
	_delete = false;
	_frame = frame;
	_name = name;
//	_position = XMVECTOR(_x, _y, _z);
	this->m_device = _frame->GetDirectDevice();
	this->m_deviceContext = _frame->GetDirectDeviceContext();

	_frameWorkResourcesManager = _frameResourcesManager;
	_frameWorkResourcesManager->LoadAsset("dome.x");

	// Get the mesh stuff from the model
	meshy = _frameWorkResourcesManager->GetMesh();

	Initialise();

	this->m_projectionTransformation = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1.28f, 0.1f, 1500.0f);
	this->m_worldTransformation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	this->m_scalingMatrix = XMMatrixScaling(1000.0f, 1000.0f, 1000.0f);
}

//-----------------------------------------------------------------------------
// Name: ~SkyDome()
// Desc: SkyDome Class Destructor
//-----------------------------------------------------------------------------
SkyDome::~SkyDome(void)
{
	Shutdown();
}

//-----------------------------------------------------------------------------
// Name: Shutdown()
// Desc: Free memory & resources
//-----------------------------------------------------------------------------
void SkyDome::Shutdown(void)
{
	/*
	if(_texture)
	{
		SAFE_RELEASE(_texture);
	}
	if(_mesh)
	{
		SAFE_RELEASE(_mesh);
	}
	if(_pd3dDevice)
	{
		SAFE_RELEASE(_pd3dDevice);
	}
	*/
}

HRESULT SkyDome::Initialise(void)
{
	this->m_vertices = new VERTEX[meshy[1].vertices.size()];
	for (unsigned int i = 0; i < meshy[1].vertices.size(); i++)
	{
		this->m_vertices[i].Position.x = meshy[1].vertices.at(i).X;
		this->m_vertices[i].Position.y = meshy[1].vertices.at(i).Y;
		this->m_vertices[i].Position.z = meshy[1].vertices.at(i).Z;

		this->m_vertices[i].Normal.x = 0;
		this->m_vertices[i].Normal.y = 0;
		this->m_vertices[i].Normal.z = 0;

		this->m_vertices[i].TexCoord.x = meshy[1].vertices.at(i).texcoord.x;
		this->m_vertices[i].TexCoord.y = meshy[1].vertices.at(i).texcoord.y;
	}

	// Allocate & copy the mesh indices
	this->m_indices = new DWORD[meshy[1].indices.size()];
	for (unsigned int i = 0; i < meshy[1].indices.size(); i++)
	{
		this->m_indices[i] = meshy[1].indices.at(i);
	}

	this->m_numVertices = meshy[1].vertices.size();
	this->m_numIndices = meshy[1].indices.size();

	InitialiseGeometry();
	this->m_texture = meshy[1].textures[0].texture;


#pragma region Load texture from file

	// Load a DDS texture
	if (FAILED(CreateDDSTextureFromFile(this->m_device, L"cloudMap.dds", nullptr, &this->m_texture)))
	{
		return S_OK;
	}
#pragma endregion

	// Set the rasterizer state
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	//rd.AntialiasedLineEnable = false;
	rd.CullMode = D3D11_CULL_FRONT;
	rd.FrontCounterClockwise = true;
	rd.FillMode = D3D11_FILL_SOLID;
	this->m_device->CreateRasterizerState(&rd, &this->m_wireFrame);
	this->m_deviceContext->RSSetState(this->m_wireFrame);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
HRESULT SkyDome::Render(void)
{
	XMMATRIX viewTransformation = _camRender->GetViewMatrix();
	XMMATRIX completeTransformation = this->m_scalingMatrix * this->m_worldTransformation * this->m_projectionTransformation;

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
	this->m_deviceContext->DrawIndexed(this->m_numIndices, 0, 0);

	return S_OK;
}


void SkyDome::SetCamera(Camera* _cameraRender)
{
	_camRender = _cameraRender;
}