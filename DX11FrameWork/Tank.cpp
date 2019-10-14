//-----------------------------------------------------------------------------
// File: Tank.cpp
// Description : This Class managers the Tank

//-----------------------------------------------------------------------------

#include "Tank.h"


VERTEX cubeVertices1[] =
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

DWORD cubeIndices1[] =
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
// Name: Constructor
// Desc: Creates the Tank
//-----------------------------------------------------------------------------
Tank::Tank(void)
{
}

//-----------------------------------------------------------------------------
// Name: Constructor
// Desc: Creates the Tank
//-----------------------------------------------------------------------------
Tank::Tank(wstring name, Framework* frame, float x, float z, FrameWorkResourceManager* frameResourcesManager)
{
	_thirdPerson = false;
	_fire = false;
	_scale = 0.5f;
	_angle = 0;
	this->m_x = x;
	this->m_y = 0;
	this->m_z = z;
	_terrainExtent = 1260.0f;
	_name = name;
	_frame = frame;
	//	_texture = NULL;
	_collsion = false;
	_delete = false;

	this->m_device = _frame->GetDirectDevice();
	this->m_deviceContext = _frame->GetDirectDeviceContext();

	//	_sGraph =_frame->GetSceneGraph();
	//	_renderCam = _frame->GetCamera();
	//
	//	_bulletCount = 0;
	//
	// 	_cameraSpeed = 10.0f;
	//	_yaw = 0.0f;					// Degrees of yaw (in radians)
	//	_pitch = 0.0f;					// Degrees of pitch (in radians)
	//	_roll = 0.0f;
	//
	//	_terrainNode = _frame->GetTerrain();
	//
	//	// Get the height of the terrain at x, z
	////	_y = _terrainNode->GetHeight(_x, _z);
	//
	////	_position = XMVECTOR(_x, _y, _z);
	//
	_frameWorkResourcesManager = frameResourcesManager;

	_frameWorkResourcesManager->LoadAsset("Tiger.x");

	// Get the mesh stuff from the model
	meshy = _frameWorkResourcesManager->GetMesh();

	InitialiseTank();

	this->m_projectionTransformation = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1.28f, 0.1f, 1500.0f);
	this->m_worldTransformation = XMMatrixTranslation(0.0f, 20.0f, 0.0f);
	this->m_scalingMatrix = XMMatrixScaling(0.5f, 0.5f, 0.5f);

	////	_mesh = _frameWorkResourcesManager->GetMesh(L"Tiger.x", false);
	////	_texture = _frameWorkResourcesManager->GetTexture(L"Tiger.x");
	////	_material = _frameWorkResourcesManager->GetMaterial(L"Tiger.x");
	//
	////	_sGraph->AddNode(_boundingBox = new BoundingBox(_mesh, _pd3dDevice, _x,_y,_z, L"boundingBox", _scale),L"Parent");
	//
	//	// Get the 4 vectors
	//	_tankFrontLeftPos = _boundingBox->GetFrontLeftVector();
	//	_tankFrontMidPos = _boundingBox->GetFrontMidVector();
	//	_tankFrontRightPos = _boundingBox->GetFrontRightVector();
	//	_tankRearMidPos = _boundingBox->GetRearMidVector();
	//
	//	// Calculate the Hypotenuse values
	////	_xHypotenuse =  _tankFrontLeftPos.x - _tankFrontRightPos.x ;
	////	_zHypotenuse =  _tankRearMidPos.z - _tankFrontMidPos.z;
	//
	//	//D3DXFONT_DESC fontDesc;
	//	//fontDesc.Height          = 22;
	// //   fontDesc.Width           = 0;
	// //   fontDesc.Weight          = FW_BOLD;
	// //   fontDesc.MipLevels       = 1;
	// //   fontDesc.Italic          = false;
	// //   fontDesc.CharSet         = DEFAULT_CHARSET;
	// //   fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	// //   fontDesc.Quality         = DEFAULT_QUALITY;
	// //   fontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
	////	D3DXCreateFontIndirect(_pd3dDevice, &fontDesc, &mFont);
}

//-----------------------------------------------------------------------------
// Name: ~Tank()
// Desc: Tank Class Destructor
//-----------------------------------------------------------------------------
Tank::~Tank(void)
{
	Shutdown();
}

//-----------------------------------------------------------------------------
// Name: Shutdown()
// Desc: Deletes the objects used in the Class
//-----------------------------------------------------------------------------
void Tank::Shutdown(void)
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

HRESULT Tank::InitialiseTank(void)
{
	m_vertices = new VERTEX[meshy[0].vertices.size()];
	for (unsigned int i = 0; i < meshy[0].vertices.size(); i++)
	{
		m_vertices[i].Position.x = meshy[0].vertices.at(i).X;
		m_vertices[i].Position.y = meshy[0].vertices.at(i).Y;
		m_vertices[i].Position.z = meshy[0].vertices.at(i).Z;

		m_vertices[i].Normal.x = 0;
		m_vertices[i].Normal.y = 0;
		m_vertices[i].Normal.z = 0;

		m_vertices[i].TexCoord.x = meshy[0].vertices.at(i).texcoord.x;
		m_vertices[i].TexCoord.y = meshy[0].vertices.at(i).texcoord.y;
	}

	// Allocate & copy the mesh indices
	m_indices = new DWORD[meshy[0].indices.size()];
	for (unsigned int i = 0; i < meshy[0].indices.size(); i++)
	{
		m_indices[i] = meshy[0].indices.at(i);
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

	m_numVertices = meshy[0].vertices.size();
	m_numIndices = meshy[0].indices.size();

	//m_numVertices = unsigned(size(cubeVertices1)*3);
	//m_numIndices = unsigned(size(cubeIndices1));
	//m_vertices = cubeVertices1;
	//m_indices = cubeIndices1;


	InitialiseGeometry();

#pragma region Load texture from file

	// Load a DDS texture
	if (FAILED(CreateDDSTextureFromFile(this->m_device, L"triax_tracks.dds", nullptr, &_texture)))
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
		//rd.FrontCounterClockwise = false;
	rd.FrontCounterClockwise = true;
	//rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.FillMode = D3D11_FILL_SOLID;
	this->m_device->CreateRasterizerState(&rd, &pRSWireFrame1);
	this->m_deviceContext->RSSetState(pRSWireFrame1);

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
HRESULT Tank::Render(void)
{
	/*
	_worldMatrix._11 = _right.x;
	_worldMatrix._21 = _right.y;
	_worldMatrix._31 = _right.z;

	_worldMatrix._12 = _up.x;
	_worldMatrix._22 = _up.y;
	_worldMatrix._32 = _up.z;

	_worldMatrix._13 = _lookAt.x;
	_worldMatrix._23 = _lookAt.y;
	_worldMatrix._33 = _lookAt.z;

	_worldMatrix._41 = -D3DXVec3Dot(&_position, &_right);
	_worldMatrix._42 = -D3DXVec3Dot(&_position, &_up);
	_worldMatrix._43 = -D3DXVec3Dot(&_position, &_lookAt);

	XMMATRIXRotationX(&_rotationMatrixX, _roll);
	XMMATRIXRotationY(&_rotationMatrixY, _angle);
	XMMATRIXRotationZ(&_rotationMatrixZ, _pitch);

	XMMATRIXTranslation(&_translationMatrix, _position.x, _position.y, _position.z);

	XMMATRIXScaling(&_scalingingMatrix,_scale,_scale,_scale);

	_worldMatrix = _rotationMatrixY * _rotationMatrixY * _rotationMatrixZ * _scalingingMatrix *_translationMatrix;
//	_pd3dDevice->SetTransform(D3DTS_WORLD, &_worldMatrix);

//	_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

//    _pd3dDevice->SetTexture( 0, _texture );

	// Draw the mesh subset
//	_mesh->DrawSubset( 0 );


	_boundingBox->UpdateBoundingShape(_worldMatrix);


	// If Camera is set to 3rd person then update the posiotn and angle
	if (_thirdPerson)
	{
		_renderCam->SetLookAt(_position, _angle);
	}

	TextDisplay();

	_position.y = _terrainNode->GetHeight(_tankFrontLeftPos.x + _position.x, _tankFrontLeftPos.z  + _position.z);
*/


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
	this->m_deviceContext->PSSetShaderResources(0, 1, &_texture);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	this->m_deviceContext->IASetVertexBuffers(0, 1, &this->m_vertexBuffer, &stride, &offset);
	this->m_deviceContext->IASetIndexBuffer(this->m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	this->m_deviceContext->RSSetState(NULL);
	this->m_deviceContext->RSSetState(pRSWireFrame1);
	this->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_deviceContext->DrawIndexed(m_numIndices, 0, 0);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Update()
// Desc: Updates the Tank
//-----------------------------------------------------------------------------
void Tank::Update(void)
{
	/*
	_up = XMVECTOR(0.0f, 1.0f, 0.0f);
	_lookAt = XMVECTOR(0.0f, 0.0f, 1.0f);
	_right = XMVECTOR(1.0f, 0.0f, 0.0f);

	// Rotate lookat and right vectors around the up vector
	XMMATRIXRotationAxis(&yawMatrix, &_up, _yaw);
	D3DXVec3TransformCoord(&_lookAt, &_lookAt, &yawMatrix);
	D3DXVec3TransformCoord(&_right, &_right, &yawMatrix);

	// Rotate lookat and up vectors around the right vector
	XMMATRIXRotationAxis(&pitchMatrix, &_right, _pitch);
	D3DXVec3TransformCoord(&_lookAt, &_lookAt, &pitchMatrix);
	D3DXVec3TransformCoord(&_up, &_up, &pitchMatrix);

	// Rotate right and up vectors around the lookat vector
	XMMATRIXRotationAxis(&rollMatrix, &_lookAt, _roll);
	D3DXVec3TransformCoord(&_right, &_right, &rollMatrix);
	D3DXVec3TransformCoord(&_up, &_up, &rollMatrix);

	// Calculate the opposite length for s=o/h required for the roll calculation
	_xOpposite = _terrainNode->GetHeight(_tankFrontLeftPos.x + _position.x, _tankFrontLeftPos.z + _position.z) -
				_terrainNode->GetHeight(_tankFrontRightPos.x + _position.x, _tankFrontRightPos.z + _position.z);

	CalculatePitch(_zOpposite, _zHypotenuse);


	// Calculate the opposite length for s=o/h required for the pitch calculation
	_zOpposite = _terrainNode->GetHeight(_tankFrontLeftPos.x + _position.x, _tankFrontLeftPos.z + _position.z) -
				_terrainNode->GetHeight(_tankFrontRightPos.x + _position.x, _tankFrontRightPos.z + _position.z);

	CalculateRoll(_xOpposite, _xHypotenuse);
	*/
}

//-----------------------------------------------------------------------------
// Name: FireBullet()
// Desc: Creates a new Bullet
//-----------------------------------------------------------------------------
void Tank::FireBullet(void)
{
	_bulletCount++;
	wstringstream streamVal;
	streamVal << _bulletCount;
	wstring _bulletName = L"BulletNode" + streamVal.str();
	//	_sGraph->AddNode(_bullet = new BulletNode(_bulletName, _frame, _position, _angle, _frameWorkResourcesManager),L"Parent");
}

//-----------------------------------------------------------------------------
// Name: MoveForward()
// Desc: Moves the tank forward
//-----------------------------------------------------------------------------
void Tank::MoveForward(float amountOfMovement)
{
	/*
	if (_position.z < _terrainExtent && _position.z > _terrainExtent * -1)
	{
		_position += _lookAt * amountOfMovement * _cameraSpeed;
	}

	// Stop the tank from falling off the terrain
	if (_position.z > _terrainExtent)
	{
		_position.z = 1259.0f;
	}
	else if (_position.z < _terrainExtent * -1)
	{
		_position.z = -1259.0f;
	}

	if (_position.x > _terrainExtent)
	{
		_position.x = 1259.0f;
	}
	else if (_position.x < _terrainExtent * -1)
	{
		_position.x = -1259.0f;
	}
	*/
}

//-----------------------------------------------------------------------------
// Name: Yaw()
// Desc: Calculates the Yaw
//-----------------------------------------------------------------------------
void Tank::Yaw(float amountOfMovement)
{
	_yaw += amountOfMovement;
	_angle += amountOfMovement;
	if (_angle > 3.141 || _angle < -3.141)
	{
		_angle = 0;
		_yaw = 0;
	}
}

//-----------------------------------------------------------------------------
// Name: CalculateRoll()
// Desc: Calculates the Roll
//-----------------------------------------------------------------------------
void Tank::CalculateRoll(float xOpposite, float xHypotenuse)
{
	_roll = sin(xOpposite / xHypotenuse);
}

//-----------------------------------------------------------------------------
// Name: CalculatePitch()
// Desc: Calculates the Pitch
//-----------------------------------------------------------------------------
void Tank::CalculatePitch(float zOpposite, float zHypotenuse)
{
	_pitch = sin(zOpposite / zHypotenuse);
}

//-----------------------------------------------------------------------------
// Name: SetPosition()
// Desc: Sets the Position
//-----------------------------------------------------------------------------
void Tank::SetPosition(XMVECTOR distance)
{
	//	_position += distance;
}

//-----------------------------------------------------------------------------
// Name: SetCameraType()
// Desc: Changes between 1st and 3rd person camera
//-----------------------------------------------------------------------------
void Tank::SetCameraType(bool cameraType)
{
	_thirdPerson = cameraType;
}


void Tank::SetCamera(Camera* _cameraRender)
{
	_camRender = _cameraRender;
}