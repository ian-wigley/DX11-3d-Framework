//-----------------------------------------------------------------------------
// File: WoodenCrate.cpp
// Description : This Class managers the WoodenCrate
//-----------------------------------------------------------------------------

#include "WoodenCrate.h"

VERTEX cubeVertices[] =
{
	{XMFLOAT3(-1.0f, -1.0f, 1.0f),  XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(0.0f, 0.0f)},    // side 1
	{XMFLOAT3(1.0f, -1.0f, 1.0f),   XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(0.0f, 1.0f)},
	{XMFLOAT3(-1.0f, 1.0f, 1.0f),   XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(1.0f, 0.0f)},
	{XMFLOAT3(1.0f, 1.0f, 1.0f),    XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(1.0f, 1.0f)},

	{XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),  XMFLOAT2(0.0f, 0.0f)},    // side 2
	{XMFLOAT3(-1.0f, 1.0f, -1.0f),  XMFLOAT3(0.0f, 0.0f, -1.0f),  XMFLOAT2(0.0f, 1.0f)},
	{XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT3(0.0f, 0.0f, -1.0f),  XMFLOAT2(1.0f, 0.0f)},
	{XMFLOAT3(1.0f, 1.0f, -1.0f),   XMFLOAT3(0.0f, 0.0f, -1.0f),  XMFLOAT2(1.0f, 1.0f)},

	{XMFLOAT3(-1.0f, 1.0f, -1.0f),  XMFLOAT3(0.0f, 1.0f, 0.0f),  XMFLOAT2(0.0f, 0.0f)},    // side 3
	{XMFLOAT3(-1.0f, 1.0f, 1.0f),   XMFLOAT3(0.0f, 1.0f, 0.0f),  XMFLOAT2(0.0f, 1.0f)},
	{XMFLOAT3(1.0f, 1.0f, -1.0f),   XMFLOAT3(0.0f, 1.0f, 0.0f),  XMFLOAT2(1.0f, 0.0f)},
	{XMFLOAT3(1.0f, 1.0f, 1.0f),    XMFLOAT3(0.0f, 1.0f, 0.0f),  XMFLOAT2(1.0f, 1.0f)},

	{XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f),  XMFLOAT2(0.0f, 0.0f)},    // side 4
	{XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT3(0.0f, -1.0f, 0.0f),  XMFLOAT2(0.0f, 1.0f)},
	{XMFLOAT3(-1.0f, -1.0f, 1.0f),  XMFLOAT3(0.0f, -1.0f, 0.0f),  XMFLOAT2(1.0f, 0.0f)},
	{XMFLOAT3(1.0f, -1.0f, 1.0f),   XMFLOAT3(0.0f, -1.0f, 0.0f),  XMFLOAT2(1.0f, 1.0f)},

	{XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT3(1.0f, 0.0f, 0.0f),  XMFLOAT2(0.0f, 0.0f)},    // side 5
	{XMFLOAT3(1.0f, 1.0f, -1.0f),   XMFLOAT3(1.0f, 0.0f, 0.0f),  XMFLOAT2(0.0f, 1.0f)},
	{XMFLOAT3(1.0f, -1.0f, 1.0f),   XMFLOAT3(1.0f, 0.0f, 0.0f),  XMFLOAT2(1.0f, 0.0f)},
	{XMFLOAT3(1.0f, 1.0f, 1.0f),    XMFLOAT3(1.0f, 0.0f, 0.0f),  XMFLOAT2(1.0f, 1.0f)},

	{XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f),  XMFLOAT2(0.0f, 0.0f)},    // side 6
	{XMFLOAT3(-1.0f, -1.0f, 1.0f),  XMFLOAT3(-1.0f, 0.0f, 0.0f),  XMFLOAT2(0.0f, 1.0f)},
	{XMFLOAT3(-1.0f, 1.0f, -1.0f),  XMFLOAT3(-1.0f, 0.0f, 0.0f),  XMFLOAT2(1.0f, 0.0f)},
	{XMFLOAT3(-1.0f, 1.0f, 1.0f),   XMFLOAT3(-1.0f, 0.0f, 0.0f),  XMFLOAT2(1.0f, 1.0f)},
};

DWORD cubeIndices[] =
{
	0, 1, 2,       // side 1
	2, 1, 3,
	4, 5, 6,       // side 2
	6, 5, 7,
	8, 9, 10,      // side 3
	10, 9, 11,
	12, 13, 14,    // side 4
	14, 13, 15,
	16, 17, 18,    // side 5
	18, 17, 19,
	20, 21, 22,    // side 6
	22, 21, 23,
};

//-----------------------------------------------------------------------------
// Name: Constructor()
// Desc: Creates the Wooden Crate
//-----------------------------------------------------------------------------
WoodenCrate::WoodenCrate(void)
{
}

//-----------------------------------------------------------------------------
// Name: Constructor
// Desc: Creates the Wooden Crate
//-----------------------------------------------------------------------------
WoodenCrate::WoodenCrate(wstring name, Framework *_frame, float x, float z, FrameWorkResourceManager* _frameResourcesManager)
{
	this->m_x = x;
	this->m_y = 0;
	this->m_z = z;
	_name = name;
	this->m_scale = 1.0f;
	this->m_device = _frame->GetDirectDevice();
	this->m_deviceContext = _frame->GetDirectDeviceContext();
	this->m_zBuffer = _frame->GetStencilBuffer();
	_sGraph = _frame->GetSceneGraph();
	_delete = false;
	_frameWorkResourcesManager = _frameResourcesManager;
	_terrainNode = _frame->GetTerrain();
	this->m_y = 5;// _terrainNode->GetHeight(_x, _z) + 5.0f;
	InitialiseCrate();
	this->m_projectionTransformation = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1.28f, 0.1f, 1500.0f);
	this->m_worldTransformation = XMMatrixTranslation(100.0f, 50.0f, 0.0f);
	this->m_scalingMatrix = XMMatrixScaling(25.0f, 25.0f, 25.0f);
}

//-----------------------------------------------------------------------------
// Name: ~WoodenCrate()
// Desc: WoodenCrate Class Destructor
//-----------------------------------------------------------------------------
WoodenCrate::~WoodenCrate(void)
{
	Shutdown();
}

//-----------------------------------------------------------------------------
// Name: Shutdown()
// Desc: Deletes the objects used in the Class
//-----------------------------------------------------------------------------
void WoodenCrate::Shutdown(void)
{
	SAFE_RELEASE(this->m_texture);
	//SAFE_RELEASE(_mesh);
}

//-----------------------------------------------------------------------------
// Name: InitialiseCrate()
// Desc: Initialises the Crate
//-----------------------------------------------------------------------------
HRESULT WoodenCrate::InitialiseCrate(void)
{
	m_numVertices = unsigned(size(cubeVertices) * 3);
	m_numIndices = unsigned(size(cubeIndices));
	m_vertices = cubeVertices;
	m_indices = cubeIndices;

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
// Name: Render() ALL Render methods should call the world transform matrix.....
// Desc: Draws the Crate
//-----------------------------------------------------------------------------
HRESULT WoodenCrate::Render(void)
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

	// Update the bounding Box
	//_boundingBox->UpdateBoundingShape(_worldMatrix);

	return S_OK;
}


void WoodenCrate::SetCamera(Camera* _cameraRender)
{
	_camRender = _cameraRender;
}