//-----------------------------------------------------------------------------
// File: Tank.cpp
// Description : This Class managers the Tank
//-----------------------------------------------------------------------------

#include "Tank.h"

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
	this->m_thirdPerson = false;
	this->m_fire = false;
	this->m_scale = 0.5f;
	this->m_angle = 0;
	this->m_x = x;
	this->m_y = 0;
	this->m_z = z;
	this->m_terrainExtent = 1260.0f;
	_name = name;
	this->m_frame = frame;
	_collsion = false;
	_delete = false;

	this->m_device = this->m_frame->GetDirectDevice();
	this->m_deviceContext = this->m_frame->GetDirectDeviceContext();

	//	_sGraph =_frame->GetSceneGraph();
	//	_renderCam = _frame->GetCamera();
	this->m_bulletCount = 0;
	// 	_cameraSpeed = 10.0f;
	//	_yaw = 0.0f;					// Degrees of yaw (in radians)
	//	_pitch = 0.0f;					// Degrees of pitch (in radians)
	//	_roll = 0.0f;
	//	_terrainNode = _frame->GetTerrain();

	//	// Get the height of the terrain at x, z
	////	_y = _terrainNode->GetHeight(_x, _z);
	this->m_position = XMFLOAT3(m_x, m_y, m_z);

	this->m_frameWorkResourcesManager = frameResourcesManager;
	this->m_frameWorkResourcesManager->LoadAsset("Tiger.x");
	this->m_sGraph = this->m_frame->GetSceneGraph();

	// Get the mesh stuff from the model
	meshy = this->m_frameWorkResourcesManager->GetMesh();

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

	InitialiseGeometry();

#pragma region Load texture from file

	// Load a DDS texture
	if (FAILED(CreateDDSTextureFromFile(this->m_device, L"triax_tracks.dds", nullptr, &this->m_texture)))
	{
		return S_OK;
	}
#pragma endregion

	// Set the rasterizer state
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	//rd.AntialiasedLineEnable = false;
	rd.CullMode = D3D11_CULL_BACK;
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
HRESULT Tank::Render(void)
{
	XMMATRIX viewTransformation = this->m_camRender->GetViewMatrix();
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

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	this->m_deviceContext->IASetVertexBuffers(0, 1, &this->m_vertexBuffer, &stride, &offset);
	this->m_deviceContext->IASetIndexBuffer(this->m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	this->m_deviceContext->RSSetState(NULL);
	this->m_deviceContext->RSSetState(this->m_wireFrame);
	this->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_deviceContext->DrawIndexed(m_numIndices, 0, 0);

	return S_OK;

	/*
	_boundingBox->UpdateBoundingShape(_worldMatrix);

	// If Camera is set to 3rd person then update the posiotn and angle
	if (_thirdPerson)
	{
		_renderCam->SetLookAt(_position, _angle);
	}
	TextDisplay();
	_position.y = _terrainNode->GetHeight(_tankFrontLeftPos.x + _position.x, _tankFrontLeftPos.z  + _position.z);
	*/
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
	this->m_bulletCount++;
	wstringstream streamVal;
	streamVal << this->m_bulletCount;
	wstring _bulletName = L"BulletNode" + streamVal.str();
	m_sGraph->AddNode(_bullet = new BulletNode(_bulletName, this->m_frame, this->m_position, this->m_angle, this->m_frameWorkResourcesManager),L"Parent");
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
	this->m_angle += amountOfMovement;
	if (this->m_angle > 3.141 || this->m_angle < -3.141)
	{
		this->m_angle = 0;
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
	this->m_thirdPerson = cameraType;
}


void Tank::SetCamera(Camera* _cameraRender)
{
	this->m_camRender = _cameraRender;
}