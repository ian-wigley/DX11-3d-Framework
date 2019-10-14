//-----------------------------------------------------------------------------
// File: TerrainNode.cpp
// Description : This Class managers the Terrain
//-----------------------------------------------------------------------------

#include "TerrainNode.h"

//-----------------------------------------------------------------------------
// Name: TerrainNode()
// Desc: TerrainNode Class Constructor
//-----------------------------------------------------------------------------
TerrainNode::TerrainNode(void)
{
	_gridSize = 256;
	_numCellCols = 256;
	_numCellRows = 256;
	_spacing = 10;
	//	InitialiseGrid();
	GenerateVertices();
	GenerateIndices();
	CalculateVertexNormals();
}

//-----------------------------------------------------------------------------
// Name: SetTexture()
// Desc: TerrainNode Class Constructor
//-----------------------------------------------------------------------------
TerrainNode::TerrainNode(wstring name, Framework *_frame, FrameWorkResourceManager* frameResourcesManager)
{
	this->m_x = 0.0f;
	this->m_y = 0.0f;
	this->m_z = 0.0f;

	_v0 = 0.0f;
	_delete = false;
	_height = 100.0f;

	_gridSize = 256;
	_numCellCols = 255;
	_numCellRows = 255;
	_numVertices = _gridSize * _gridSize;

	_spacing = 10;
	_numTriangles = _numCellCols * _numCellRows * 2;
	//	_name = name;

	_terrainStartX = 0;
	_terrainStartZ = 0;

	_hWnd = _frame->GetHandle();

	this->m_device = _frame->GetDirectDevice();
	this->m_deviceContext = _frame->GetDirectDeviceContext();
	this->m_swapChain = _frame->GetSwapChain();
	this->m_renderTarget = _frame->GetRenderTarget();
	this->m_zBuffer = _frame->GetStencilBuffer();

	vsBlob = NULL;
	psBlob = NULL;
	vertexShader = NULL;
	pixelShader = NULL;
	vertexBuffer = NULL;
	indexBuffer = NULL;
	constantBuffer = NULL;
	layout = NULL;

	modelVertices = new VERTEX[_numVertices];
	currentVertex = modelVertices;
	_numIndices = _numTriangles * 3;
	modelIndices = new unsigned int[_numIndices];
	currentIndex = modelIndices;

	_viewTransformation = XMMatrixIdentity();

	this->m_worldTransformation = XMMatrixRotationZ(XMConvertToRadians(180));
	_completeTransformation = XMMatrixIdentity();
	_ambientLightColour = XMFLOAT4(1.5f, 0.5f, 0.5f, 1.0f);
	_directionalLightColour = XMFLOAT4(1.0f, 1.0, 1.0f, 1.0f);
	_directionalLightVector = XMVector4Normalize(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));

	//http://www.rastertek.com/dx11s2tut03.html
	this->m_projectionTransformation = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1.28f, 0.1f, 1500.0f);

	// Create the vertex input layout description.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	_frameWorkResourcesManager = frameResourcesManager;
	_heights = _frameWorkResourcesManager->LoadHeightMap(L"volcano.raw", _gridSize);
	GenerateVertices();
	GenerateIndices();
	CalculateVertexNormals();

	InitialiseShaders();
	//	Initialise();
}

//-----------------------------------------------------------------------------
// Name: ~TerrainNode()
// Desc: TerrainNode Class Destructor
//-----------------------------------------------------------------------------
TerrainNode::~TerrainNode(void)
{
	Shutdown();
}

//-----------------------------------------------------------------------------
// Name: Shutdown()
// Desc: Deletes the objects used in the Terrain
//-----------------------------------------------------------------------------
void TerrainNode::Shutdown(void)
{
	//	if (_heights.size() != 0)
	//	{
	//		_heights.clear();
	//	}
	//
	//	//	if (_vertices.size() != 0)
	//	//	{
	//	//		_vertices.clear();
	//	//	}
	//
	//	//	if (_indices.size() != 0)
	//	//	{
	//	//		_indices.clear();
	//	//	}
	//
	//	//	if(_pd3dDevice)
	//	//	{
	//	//		SAFE_RELEASE(_pd3dDevice);
	//	//	}
}

//-----------------------------------------------------------------------------
// Name: InitialiseShaders()
// Desc: Initialises the Shaders
//-----------------------------------------------------------------------------
HRESULT TerrainNode::InitialiseShaders(void)
{

#pragma region Set up vertex buffer
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(VERTEX) * _numVertices;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	if (FAILED(this->m_device->CreateBuffer(&bufferDesc, NULL, &vertexBuffer)))
	{
		return false;
	}
	// Copy vertices to the vertex buffer
	if (FAILED(this->m_deviceContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms)))
	{
		return false;
	}
	memcpy(ms.pData, modelVertices, sizeof(VERTEX) * _numVertices);

	this->m_deviceContext->Unmap(vertexBuffer, NULL);
#pragma endregion

#pragma region Create the index buffer
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(DWORD) * _numIndices;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	if (FAILED(this->m_device->CreateBuffer(&bufferDesc, NULL, &indexBuffer)))
	{
		return false;
	}
	this->m_deviceContext->Map(indexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, modelIndices, sizeof(DWORD) * _numIndices);
	this->m_deviceContext->Unmap(indexBuffer, NULL);
#pragma endregion

#pragma region Create constant buffer
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(CBUFFER);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	if (FAILED(this->m_device->CreateBuffer(&bufferDesc, NULL, &constantBuffer)))
	{
		return false;
	}
#pragma endregion


#pragma region Create Light Constant Buffer
	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;
	if (FAILED(this->m_device->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer)))
	{
		return false;
	}
#pragma endregion

#pragma region Create Matrix Constant Buffer
	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	if (FAILED(this->m_device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer)))
	{
		return false;
	}
#pragma endregion

#pragma region Load texture from file

	// Load a DDS texture
	if (FAILED(CreateDDSTextureFromFile(this->m_device, L"volcano.dds", nullptr, &this->m_texture)))
	{
		return S_OK;
	}
#pragma endregion

	// Get a count of the elements in the layout.
	unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//https://code.msdn.microsoft.com/Basic-DXUT-Win32-Samples-e59c0682/sourcecode?fileId=121851&pathId=729485639
	// Create a sampler state 
	D3D11_SAMPLER_DESC SamDesc;
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.MipLODBias = 0.0f;
	SamDesc.MaxAnisotropy = 1;
	SamDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	SamDesc.BorderColor[0] = SamDesc.BorderColor[1] = SamDesc.BorderColor[2] = SamDesc.BorderColor[3] = 0;
	SamDesc.MinLOD = 0;
	SamDesc.MaxLOD = D3D11_FLOAT32_MAX;
	this->m_device->CreateSamplerState(&SamDesc, &g_pSamLinear);

	// Set the rasterizer state
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	//rd.AntialiasedLineEnable = false;
	rd.CullMode = D3D11_CULL_FRONT;
	rd.FrontCounterClockwise = false;
	rd.FillMode = D3D11_FILL_WIREFRAME;
	this->m_device->CreateRasterizerState(&rd, &this->m_wireFrame);
	this->m_deviceContext->RSSetState(this->m_wireFrame);
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: GenerateVertices() 
// Desc: Generate the Vertices
//-----------------------------------------------------------------------------
void TerrainNode::GenerateVertices()
{
	float width = (float)_numCellCols * _spacing;
	float depth = (float)_numCellRows * _spacing;

	float xOffset = -width * 0.5f;
	float zOffset = depth * 0.5f;

	_terrainStartX = xOffset;
	_terrainStartZ = zOffset;

	float uIncrement = 1.0f / _numCellRows;
	float vIncrement = 1.0f / _numCellCols;

	// Set up the vertex array.  For now, we set the y co-ordinate to 0 (we will adjust this when we
	// apply the height map
	int vertex = 0;

	for (float i = 0; i < _gridSize; ++i)
	{
		for (float j = 0; j < _gridSize; ++j)
		{
			currentVertex[vertex].Position.x = j * _spacing + xOffset;
			currentVertex[vertex].Position.y = (_heights[vertex] * _height)*-1;
			currentVertex[vertex].Position.z = -i * _spacing + zOffset;

			//currentVertex[vertex].Position.z = 0.0f;

			currentVertex[vertex].TexCoord.x = j * uIncrement;
			currentVertex[vertex].TexCoord.y = i * vIncrement;
			++vertex;
		}
	}
}

//-----------------------------------------------------------------------------
// Name: GenerateIndices()
// Desc: Generates the Indices
//-----------------------------------------------------------------------------
void TerrainNode::GenerateIndices()
{
	int index = 0;
	for (DWORD i = 0; i < (DWORD)_numCellRows; ++i)
	{
		for (DWORD j = 0; j < (DWORD)_numCellCols; ++j)
		{
			// First triangle
			currentIndex[index] = (i * _gridSize) + j;
			currentIndex[index + 1] = (i * _gridSize) + (j + 1);
			currentIndex[index + 2] = ((i + 1) * _gridSize) + j;

			// Second triangle
			currentIndex[index + 3] = ((i + 1) * _gridSize) + j;
			currentIndex[index + 4] = (i * _gridSize) + (j + 1);
			currentIndex[index + 5] = ((i + 1) * _gridSize) + (j + 1);

			index += 6;
		}
	}
}

//-----------------------------------------------------------------------------
// Name: CalculateVertexNormals()
// Desc: Calculates the Vertex Normals
//-----------------------------------------------------------------------------
void TerrainNode::CalculateVertexNormals(void)
{
	int vertexContributingCount[65536];
	for (unsigned int i = 0; i < _numVertices; i++)
	{
		vertexContributingCount[i] = 0;
	}
	for (unsigned int i = 0; i < _numIndices / 3; i++)
	{
		int index0 = currentIndex[i * 3];
		int index1 = currentIndex[i * 3 + 1];
		int index2 = currentIndex[i * 3 + 2];

		XMVECTOR u = XMVectorSet(currentVertex[index1].Position.x - currentVertex[index0].Position.x,
			currentVertex[index1].Position.y - currentVertex[index0].Position.y,
			currentVertex[index1].Position.z - currentVertex[index0].Position.z,
			0.0f);

		XMVECTOR v = XMVectorSet(currentVertex[index2].Position.x - currentVertex[index0].Position.x,
			currentVertex[index2].Position.y - currentVertex[index0].Position.y,
			currentVertex[index2].Position.z - currentVertex[index0].Position.z,
			0.0f);

		XMVECTOR normal = XMVector3Normalize(XMVector3Cross(u, v));
		XMStoreFloat3(&currentVertex[index0].Normal, XMVectorAdd(XMLoadFloat3(&currentVertex[index0].Normal), normal));
		vertexContributingCount[index0]++;
		XMStoreFloat3(&currentVertex[index1].Normal, XMVectorAdd(XMLoadFloat3(&currentVertex[index1].Normal), normal));
		vertexContributingCount[index1]++;
		XMStoreFloat3(&currentVertex[index2].Normal, XMVectorAdd(XMLoadFloat3(&currentVertex[index2].Normal), normal));
		vertexContributingCount[index2]++;
	}

	// Now divide the vertex normals by the contributing counts and normalise
	for (unsigned int i = 0; i < _numVertices; i++)
	{
		XMVECTOR vertexNormal = XMLoadFloat3(&currentVertex[i].Normal);
		XMStoreFloat3(&currentVertex[i].Normal, XMVector3Normalize(vertexNormal / (float)vertexContributingCount[i]));
	}
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
HRESULT TerrainNode::Render(void)
{
	// Clear the depth buffer
	this->m_deviceContext->ClearDepthStencilView(this->m_zBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);

	_viewTransformation = _camRender->GetViewMatrix();

	//XMMATRIX _translationMatrix = XMMatrixIdentity();

	_completeTransformation = this->m_worldTransformation * _viewTransformation * this->m_projectionTransformation;

	// Update the cBuffer in the shader
	cBuffer.LightVector = _directionalLightVector;
	cBuffer.LightColor = _directionalLightColour;
	cBuffer.AmbientColor = _ambientLightColour;
	cBuffer.CompleteTransformation = _completeTransformation;
	cBuffer.Rotation = this->m_worldTransformation;

	// Update the constant buffer with the complete transformation
	this->m_deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	this->m_deviceContext->UpdateSubresource(constantBuffer, 0, 0, &cBuffer, 0, 0);

	// Set the texture to be used by the pixel shader
	this->m_deviceContext->PSSetShaderResources(0, 1, &this->m_texture);
	this->m_deviceContext->PSSetSamplers(0, 1, &g_pSamLinear);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	this->m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	this->m_deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	this->m_deviceContext->RSSetState(NULL);
	this->m_deviceContext->RSSetState(this->m_wireFrame);
	this->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_deviceContext->DrawIndexed(_numIndices, 0, 0);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Update()
// Desc: Updates the Terrain
//-----------------------------------------------------------------------------
void TerrainNode::UpdateViewMatrix(XMMATRIX& viewMatrix)
{
	//	_viewTransformation = viewMatrix;
	//	degrees += 0.1f;
	//	_worldTransformation = XMMatrixRotationY(XMConvertToRadians(degrees));
	//		_viewTransformation = _camRender->GetViewMatrix();
}

//-----------------------------------------------------------------------------
// Name: Update()
// Desc: Updates the Terrain
//-----------------------------------------------------------------------------
void TerrainNode::Update(void)
{
	//	degrees += 0.5f;
	//	//_worldTransformation = XMMatrixRotationY(XMConvertToRadians(degrees));
	//
	//	// Update the camera
	//	_viewTransformation = XMMatrixRotationY(XMConvertToRadians(degrees));
	//
	//	//_viewTransformation = _camRender->GetViewMatrix();
}

//-----------------------------------------------------------------------------
// Name: Initialise()
// Desc: Initialises the Terrain
//-----------------------------------------------------------------------------
HRESULT TerrainNode::Initialise(void)
{
	//	_material = _frameWorkResourcesManager->GetDefaultMaterial();
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: SetCamera()
// Desc: Sets a pointer to the Camera
//-----------------------------------------------------------------------------
void TerrainNode::SetCamera(Camera* _cameraRender)
{
	_camRender = _cameraRender;
}

//-----------------------------------------------------------------------------
// Name: GetHeight()
// Desc: Returns the Height of the Terrain at a particular location
//-----------------------------------------------------------------------------
float TerrainNode::GetHeight(float x, float z)
{

	//Calculate which cell we are in
	int indexBase = 0;
	int _cellX = (int)((x - _terrainStartX) / _spacing);
	int _cellZ = (int)((_terrainStartZ - z) / _spacing);

	int verticesIndex = _cellZ * _gridSize + _cellX;
	float _dx = x - currentVertex[verticesIndex].Position.x;
	float _dz = z - currentVertex[verticesIndex].Position.z;
	// Get the first index of the triangle we are positioned in

	// We are in triangle V0,V1,V2
	if (_dz > _dx)
	{
		indexBase = (_cellZ * _numCellCols + _cellX) * 6;
	}
	// We are in triangle V0,V2,V3
	else
	{
		indexBase = (_cellZ * _numCellCols + _cellX) * 6 + 3;
	}

	// v0---v1
	// |\   | <-dx->
	// | \  |   /\ 
	// |  \ |   dz
	// |   \|   \/
	// v3---v2

	int index0 = currentIndex[indexBase];
	int index1 = currentIndex[indexBase + 1];
	int index2 = currentIndex[indexBase + 2];

	XMFLOAT3 _point(_dx, 0.0f, _dz);

	// Calculate the Triangle Normal
	XMVECTOR _u = XMVectorSet(currentVertex[index1].Position.x - currentVertex[index0].Position.x,
		currentVertex[index1].Position.y - currentVertex[index0].Position.y,
		currentVertex[index1].Position.z - currentVertex[index0].Position.z, 0.0f);

	XMVECTOR _v = XMVectorSet(currentVertex[index2].Position.x - currentVertex[index0].Position.x,
		currentVertex[index2].Position.y - currentVertex[index0].Position.y,
		currentVertex[index2].Position.z - currentVertex[index0].Position.z, 0.0f);

	XMVECTOR _normal = XMVector3Cross(_u, _v);
	XMVector3Normalize(_normal);

	float Nx = XMVectorGetX(_normal);
	float Ny = XMVectorGetY(_normal);
	float Nz = XMVectorGetZ(_normal);

	_v0 = currentVertex[index0].Position.y;

	return _point.y = _v0 + ((Nx * _dx) + (Nz * _dz) / -Ny);
}
