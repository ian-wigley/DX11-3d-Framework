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
//	_pd3dDevice = _frame->GetDirect3dDevice();
//	_position = XMVECTOR(_x, _y, _z);
	_pd3dDevice = _frame->GetDirectDevice();
	_deviceContext = _frame->GetDirectDeviceContext();

	_frameWorkResourcesManager = _frameResourcesManager;
//	_mesh = _frameWorkResourcesManager->GetMesh(L"dome.x", false);
//	_texture = _frameWorkResourcesManager->GetTexture(L"dome.x");
	_frameWorkResourcesManager->LoadAsset("dome.x");

	// Get the mesh stuff from the model
	meshy = _frameWorkResourcesManager->GetMesh();

	Initialise();

	projectionTransformation = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1.28f, 0.1f, 1500.0f);
	_worldTransformation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);// XMMatrixIdentity();_worldTransformation = XMMatrixIdentity();
	_scalingMatrix = XMMatrixScaling(1000.0f, 1000.0f, 1000.0f);
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
	m_vertices = new VERTEX[meshy[1].vertices.size()];
	for (unsigned int i = 0; i < meshy[1].vertices.size(); i++)
	{
		m_vertices[i].Position.x = meshy[1].vertices.at(i).X;
		m_vertices[i].Position.y = meshy[1].vertices.at(i).Y;
		m_vertices[i].Position.z = meshy[1].vertices.at(i).Z;

		m_vertices[i].Normal.x = 0;
		m_vertices[i].Normal.y = 0;
		m_vertices[i].Normal.z = 0;

		m_vertices[i].TexCoord.x = meshy[1].vertices.at(i).texcoord.x;
		m_vertices[i].TexCoord.y = meshy[1].vertices.at(i).texcoord.y;
	}

	// Allocate & copy the mesh indices
	m_indices = new DWORD[meshy[1].indices.size()];
	for (unsigned int i = 0; i < meshy[1].indices.size(); i++)
	{
		m_indices[i] = meshy[1].indices.at(i);
	}

	//std::ofstream ofs("tank verts.txt");
	//for (unsigned int i = 0; i < meshy[0].vertices.size(); i++) {
	//	ofs << "vert x ->" << m_vertices[i].Position.x;
	//	ofs << "vert y ->" << m_vertices[i].Position.y;
	//	ofs << "vert z ->" << m_vertices[i].Position.z << std::endl;
	//}

	//std::ofstream ofs1("tank indices.txt");
	//for (unsigned int i = 0; i < meshy[0].indices.size(); i++) {
	//	ofs1 << "index -> " << m_indices[i] << std::endl;
	//}

	m_numVertices = meshy[1].vertices.size();
	m_numIndices = meshy[1].indices.size();

	//m_numVertices = unsigned(size(cubeVertices1)*3);
	//m_numIndices = unsigned(size(cubeIndices1));
	//m_vertices = cubeVertices1;
	//m_indices = cubeIndices1;


	InitialiseGeometry();


	_texture = meshy[1].textures[0].texture;


#pragma region Load texture from file

	// Load a DDS texture
	if (FAILED(CreateDDSTextureFromFile(_pd3dDevice, L"cloudMap.dds", nullptr, &_texture)))
	{
		return S_OK;
	}
#pragma endregion


	// Set the rasterizer state
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	//rd.AntialiasedLineEnable = false;
//	rd.CullMode = D3D11_CULL_NONE;// BACK;
//	rd.CullMode = D3D11_CULL_BACK;
	rd.CullMode = D3D11_CULL_FRONT;
	//rd.FrontCounterClockwise = false;
	rd.FrontCounterClockwise = true;
	//rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.FillMode = D3D11_FILL_SOLID;
	_pd3dDevice->CreateRasterizerState(&rd, &pRSWireFrame1);
	_deviceContext->RSSetState(pRSWireFrame1);

	return S_OK;
}






//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
HRESULT SkyDome::Render(void)
{
	/*
	_renderCamera = _frame->GetCamera();

	//Get the view Matrix from the camera
	_viewMatrix = _renderCamera->GetViewMatrix();

	//Store the view matrix in SaveView
	_pd3dDevice->GetTransform(D3DTS_VIEW, &_saveView);

	_viewMatrix._41 = 0.0f;
	_viewMatrix._42 = 0.0f;
	_viewMatrix._43 = 0.0f;

	_pd3dDevice->SetTransform(D3DTS_VIEW, &_viewMatrix);

	XMMATRIXIdentity(&_worldMatrix);

	XMMATRIXTranslation(&_translationMatrix, 0.0f, -200.0f, 100.0f);
	XMMATRIXScaling(&_scalingingMatrix, 2000.0f, 2000.0f, 2000.0f);
	XMMATRIXRotationY(&_rotationMatrixY, DEGTORAD(90));
	_worldMatrix = _rotationMatrixY * _scalingingMatrix *_translationMatrix;

	_pd3dDevice->SetTransform(D3DTS_WORLD, &_worldMatrix);
	_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

  	// Set texture to render
    _pd3dDevice->SetTexture( 0, _texture );

	// Draw the mesh subset
	_mesh->DrawSubset( 0 );
	
	// Restore the view Matrix back to it's original state
	_pd3dDevice->SetTransform(D3DTS_VIEW,	&_saveView);
	*/


	XMMATRIX viewTransformation = _camRender->GetViewMatrix();

	XMMATRIX completeTransformation = _scalingMatrix * /* _rotation **/  _worldTransformation * /*viewTransformation * */ projectionTransformation;

	CBUFFER cBuffer;
	cBuffer.LightVector = XMVector4Normalize(XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	cBuffer.LightColor = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	cBuffer.AmbientColor = XMFLOAT4(0.44f, 0.57f, 0.74f, 1.0f);
	cBuffer.CompleteTransformation = completeTransformation;
	cBuffer.WorldTransformation = _worldTransformation;


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

	return S_OK;
}


void SkyDome::SetCamera(Camera* _cameraRender)
{
	_camRender = _cameraRender;
}