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

//UINT _numIndices;
//UINT m_numVertices = 24*3;
ID3D11Buffer* vertexBuffer;
ID3D11Buffer* indexBuffer;
ID3D11Buffer* constantBuffer;
D3D11_MAPPED_SUBRESOURCE ms1;
//VERTEX1* modelVertices1;
ID3D11Device* _pd3dDevice;
ID3D11RasterizerState* pRSWireFrame1;
ID3D11DepthStencilView*	_zBuffer;
ID3D11ShaderResourceView* _texture;

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
	_x = x;
	_y = 0;
	_z = z;
	_name = name;
//	_texture = NULL;
	_scale = 1.0f;
	_pd3dDevice = _frame->GetDirectDevice();
	_deviceContext = _frame->GetDirectDeviceContext();
	_zBuffer = _frame->GetStencilBuffer();


	_sGraph =_frame->GetSceneGraph();
	_delete = false;
	_frameWorkResourcesManager = _frameResourcesManager;
//	_frameWorkResourcesManager->SetTexture(L"woodbox.bmp");
	_terrainNode = _frame->GetTerrain();
	_y = 5;// _terrainNode->GetHeight(_x, _z) + 5.0f;




	InitialiseCrate();


	//XMMATRIX projectionTransformation = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1.28f, 0.1f, 1500.0f);
	//XMMATRIX _worldTransformation = XMMatrixIdentity(); //XMMatrixTranslation(_x = 0, 20.0f, _z = 0);
	//XMMATRIX _scalingMatrix = XMMatrixScaling(100.0f, 100.0f, 100.0f);

	projectionTransformation = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1.28f, 0.1f, 1500.0f);
	_worldTransformation = XMMatrixTranslation(100.0f, 50.0f, 0.0f);// XMMatrixIdentity();
	_scalingMatrix = XMMatrixScaling(25.0f, 25.0f, 25.0f);

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
//	SAFE_RELEASE(_texture);
//	SAFE_RELEASE(_mesh);
}

//-----------------------------------------------------------------------------
// Name: InitialiseCrate()
// Desc: Initialises the Crate
//-----------------------------------------------------------------------------
HRESULT WoodenCrate::InitialiseCrate(void)
{
	m_numVertices = unsigned(size(cubeVertices) * 3);
	m_numIndices = unsigned(size(cubeIndices));
	//modelVertices1 = new VERTEX1[m_numVertices];
	m_vertices = cubeVertices;
	m_indices = cubeIndices;

	InitialiseGeometry();

#pragma region Load texture from file

	// Load a DDS texture
	if (FAILED(CreateDDSTextureFromFile(_pd3dDevice, L"woodbox.dds", nullptr, &_texture)))
	{
		return S_OK;
	}
#pragma endregion


	// Set the rasterizer state
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	//rd.AntialiasedLineEnable = false;
//	rd.CullMode = D3D11_CULL_NONE;// BACK;
	rd.CullMode = D3D11_CULL_BACK;
//	rd.CullMode = D3D11_CULL_FRONT;
	rd.FrontCounterClockwise = false;
	//rd.FrontCounterClockwise = true;
	//rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.FillMode = D3D11_FILL_SOLID;
	_pd3dDevice->CreateRasterizerState(&rd, &pRSWireFrame1);
//	_deviceContext->RSSetState(pRSWireFrame1);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Render() ALL Render methods should call the world transform matrix.....
// Desc: Draws the Crate
//-----------------------------------------------------------------------------
HRESULT WoodenCrate::Render(void)
{
	// Clear the depth buffer
	//_deviceContext->ClearDepthStencilView(_zBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);

	XMMATRIX viewTransformation = _camRender->GetViewMatrix();

	XMMATRIX completeTransformation = _scalingMatrix * /* _rotation **/  _worldTransformation * viewTransformation * projectionTransformation;

	CBUFFER cBuffer;
	cBuffer.LightVector = XMVector4Normalize(XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	cBuffer.LightColor = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	cBuffer.AmbientColor = XMFLOAT4(0.44f, 0.57f, 0.74f, 1.0f);
	cBuffer.CompleteTransformation = completeTransformation;
	cBuffer.WorldTransformation = _worldTransformation;


	//XMMATRIXTranslation( &_worldMatrix, _x, _y, _z);
	//_pd3dDevice->SetTransform(D3DTS_WORLD, &_worldMatrix);

	//_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//
	//// Set texture to use
   // _pd3dDevice->SetTexture( 0, _texture );
	//_pd3dDevice->SetMaterial(&_material);

 //   _pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
 //   _pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
 //   _pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );


	// Update the constant buffer with the complete transformation
	_deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	_deviceContext->UpdateSubresource(constantBuffer, 0, 0, &cBuffer, 0, 0);

	// Set the texture to be used by the pixel shader
	_deviceContext->PSSetShaderResources(0, 1, &_texture);
	//_deviceContext->PSSetSamplers(0, 1, &g_pSamLinear);


	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	_deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	_deviceContext->RSSetState(NULL);
	_deviceContext->RSSetState(pRSWireFrame1);

	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_deviceContext->DrawIndexed(m_numIndices, 0, 0);


	// Draw the box
	//_mesh->DrawSubset(0);

	// Update the bounding Box
	//_boundingBox->UpdateBoundingShape(_worldMatrix);
	
	return S_OK;
}


void WoodenCrate::SetCamera(Camera* _cameraRender)
{
	_camRender = _cameraRender;
}