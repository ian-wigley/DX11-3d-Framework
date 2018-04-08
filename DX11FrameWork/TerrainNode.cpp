//-----------------------------------------------------------------------------
// File: TerrainNode.cpp
// Description : This Class managers the Terrain

//-----------------------------------------------------------------------------

#include "TerrainNode.h"

float degrees = 0;

// Describe the Vertex Buffers format that is being passed to the shader GPU
D3D11_INPUT_ELEMENT_DESC ied[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
};



// The format of our vertices
struct VERTEX
{
	XMFLOAT3 Position;  // position
	XMFLOAT3 Normal;    // normal
	XMFLOAT2 TexCoord;   // Texture UV Coordinates
};

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

VERTEX * modelVertices;
VERTEX * currentVertex;
unsigned int * modelIndices;
unsigned int * currentIndex;

ID3D11RasterizerState* pRSWireFrame;
D3D11_RASTERIZER_DESC RSWireFrameDesc;

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
	InitialiseGrid();
}

//-----------------------------------------------------------------------------
// Name: SetTexture()
// Desc: TerrainNode Class Constructor
//-----------------------------------------------------------------------------
TerrainNode::TerrainNode(wstring name, Framework *_frame, FrameWorkResourceManager* frameResourcesManager)
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;

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

	_device = _frame->GetDirectDevice();
	_deviceContext = _frame->GetDirectDeviceContext();
	_swapChain = _frame->GetSwapChain();
	_renderTarget = _frame->GetRenderTarget();
	_zBuffer = _frame->GetStencilBuffer();

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
	_projectionTransformation = XMMatrixIdentity();
	////_worldTransformation = XMMatrixTransformation( XMMatrixIdentity();

	_worldTransformation = XMMatrixIdentity();
	//_worldTransformation = XMMatrixRotationZ(XMConvertToRadians(180));



	_completeTransformation = XMMatrixIdentity();

	_ambientLightColour = XMFLOAT4(1.5f, 0.5f, 0.5f, 1.0f);
	_directionalLightColour = XMFLOAT4(1.0f, 1.0, 1.0f, 1.0f);
	_directionalLightVector = XMVector4Normalize(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
	_projectionTransformation = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1.0f, 1.0f, 1500.0f);

	// Wooden box example
//	_viewTransformation = XMMatrixLookAtLH(XMVectorSet(0.0f, 3.0f, -10.0f, 0.0),
//										XMVectorSet(0.0f, 0.0f, 0.0f, 0.0),
//										XMVectorSet(0.0f, 1.0f, 0.0f, 0.0));

	_viewMatrix = XMMatrixLookAtLH(XMVectorSet(0.0f, 2.0f, 0.0f, 0.0),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0),
		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0));

	_frameWorkResourcesManager = frameResourcesManager;
	_frameWorkResourcesManager->SetTexture(L"volcano.bmp");
	_texture = _frameWorkResourcesManager->GetTexture(L"volcano.bmp");
	_heights = _frameWorkResourcesManager->LoadHeightMap(L"volcano.raw", _gridSize);
	InitialiseGrid();
	Initialise();
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
	if (_heights.size() != 0)
	{
		_heights.clear();
	}

	//	if (_vertices.size() != 0)
	//	{
	//		_vertices.clear();
	//	}

	//	if (_indices.size() != 0)
	//	{
	//		_indices.clear();
	//	}

	//	if(_pd3dDevice)
	//	{
	//		SAFE_RELEASE(_pd3dDevice);
	//	}
}

//-----------------------------------------------------------------------------
// Name: InitialiseGrid()
// Desc: Initialises the Grid
//-----------------------------------------------------------------------------
HRESULT TerrainNode::InitialiseGrid(void)
{
	GenerateVertices();
	GenerateIndices();
	CalculateVertexNormals();

	D3D11_BUFFER_DESC bufferDesc;
	D3D11_MAPPED_SUBRESOURCE ms;

#pragma region Compile and set vertex shader
	if (FAILED(D3DCompileFromFile(L"TerrainShader.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0, &vsBlob, 0)))
	{
		return false;
	}
	if (FAILED(_device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vertexShader)))
	{
		return false;
	}
	_deviceContext->VSSetShader(vertexShader, 0, 0);
#pragma endregion

#pragma region Compile and set pixel shader
	if (FAILED(D3DCompileFromFile(L"TerrainShader.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, &psBlob, 0)))
	{
		return false;
	}
	if (FAILED(_device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &pixelShader)))
	{
		return false;
	}
	_deviceContext->PSSetShader(pixelShader, 0, 0);
#pragma endregion

#pragma region Set up vertex buffer
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(VERTEX) * _numVertices;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	if (FAILED(_device->CreateBuffer(&bufferDesc, NULL, &vertexBuffer)))
	{
		return false;
	}
	// Copy vertices to the vertex buffer
	if (FAILED(_deviceContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms)))
	{
		return false;
	}
	memcpy(ms.pData, modelVertices, sizeof(VERTEX) * _numVertices);

	_deviceContext->Unmap(vertexBuffer, NULL);
#pragma endregion

#pragma region Specify input element format of data passed to vertex shader
	if (FAILED(_device->CreateInputLayout(ied, ARRAYSIZE(ied), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &layout)))
	{
		return false;
	}
	_deviceContext->IASetInputLayout(layout);
#pragma endregion

#pragma region Create the index buffer
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(DWORD) * _numIndices;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	if (FAILED(_device->CreateBuffer(&bufferDesc, NULL, &indexBuffer)))
	{
		return false;
	}
	_deviceContext->Map(indexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, modelIndices, sizeof(DWORD) * _numIndices);
	_deviceContext->Unmap(indexBuffer, NULL);
#pragma endregion

#pragma region Create constant buffer
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(CBUFFER);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	if (FAILED(_device->CreateBuffer(&bufferDesc, NULL, &constantBuffer)))
	{
		return false;
	}
#pragma endregion

#pragma region Load texture from file

	// Load a DDS texture
	if (FAILED(CreateDDSTextureFromFile(_device, L"Concrete.dds", nullptr, &_texture)))
	{
		return S_OK;
	}

#pragma endregion

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = false;// true;
	rd.FillMode = D3D11_FILL_WIREFRAME; //D3D11_FILL_SOLID;// D3D11_FILL_WIREFRAME;
	//rd.FillMode = D3D11_FILL_SOLID;// D3D11_FILL_WIREFRAME;
	_device->CreateRasterizerState(&rd, &pRSWireFrame);
	_deviceContext->RSSetState(pRSWireFrame);
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
			currentVertex[vertex].Position.x = j *  _spacing + xOffset;
			currentVertex[vertex].Position.y = -i * _spacing + zOffset;
			//			currentVertex[vertex].Position.z = _heights[vertex] * _height;
			currentVertex[vertex].Position.z = 0.0f;

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
	// Clear the screen to black
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	_deviceContext->ClearRenderTargetView(_renderTarget, clearColor);

	// Clear the depth buffer
	_deviceContext->ClearDepthStencilView(_zBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);

	_viewTransformation = _camRender->GetViewMatrix();

	_completeTransformation = _worldTransformation * _viewTransformation * _projectionTransformation;

	// Update the cBuffer in the shader
	cBuffer.LightVector = _directionalLightVector;
	cBuffer.LightColor = _directionalLightColour;
	cBuffer.AmbientColor = _ambientLightColour;
	cBuffer.CompleteTransformation = _completeTransformation;
	cBuffer.Rotation = _worldTransformation;

	// Update the constant buffer with the complete transformation
	_deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	_deviceContext->UpdateSubresource(constantBuffer, 0, 0, &cBuffer, 0, 0);

	// Set the texture to be used by the pixel shader
	_deviceContext->PSSetShaderResources(0, 1, &_texture);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	_deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_deviceContext->DrawIndexed(_numIndices, 0, 0);
	// Show the back buffer in the window
	_swapChain->Present(0, 0);

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
	degrees += 0.5f;
	//_worldTransformation = XMMatrixRotationY(XMConvertToRadians(degrees));

	// Update the camera
	_viewTransformation = XMMatrixRotationY(XMConvertToRadians(degrees));

	//_viewTransformation = _camRender->GetViewMatrix();
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

TerrainNode::CBUFFER* TerrainNode::GetCbuffer(void)
{
	return &this->cBuffer;
}

ID3D11Buffer* TerrainNode::GetConstBuffer(void)const
{
	return constantBuffer;
}