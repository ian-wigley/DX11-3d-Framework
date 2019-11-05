//-----------------------------------------------------------------------------
// File: Framework.cpp
// Description : This Class managers the Framework
//-----------------------------------------------------------------------------

#include "Framework.h"
#include "Tank.h"
#include "SkyDome.h"
#include "FrameWorkTest.h"
#include "FrameWorkResourceManager.h"

Framework* _frame = NULL;
FrameWorkTest* _frameWorkTest;
FrameWorkResourceManager* _frameWorkResourceManager = NULL;

//-----------------------------------------------------------------------------
// Name: Framework()
// Desc: FrameWork Class Constructor
//-----------------------------------------------------------------------------
Framework::Framework(void)
{
}

//-----------------------------------------------------------------------------
// Name: ~Framework()
// Desc: FrameWork Class Destructor
//-----------------------------------------------------------------------------
Framework::~Framework(void)
{
	//	_frameWorkResourceManager->Shutdown();
	Shutdown();
}

//-----------------------------------------------------------------------------
// Name: Framework()
// Desc: FrameWork Class Constructor
//-----------------------------------------------------------------------------
Framework::Framework(HINSTANCE hInstance)
{
	// Direct3D interfaces used
	//device = NULL;
	//deviceContext = NULL;
	//swapChain = NULL;
	//renderTarget = NULL;
	//zBuffer = NULL;

	// App finished ?
	_quit = false;

	_screenWidth = 1024;
	_screenHeight = 800;

	_oldMouseX = 0;
	_oldMouseY = 0;
	_mouseX = 0;
	_mouseY = 0;
	msg.message = WM_NULL;
	_hWnd = 0;
	Initialise(hInstance);
	ShowWindow(_hWnd, SW_SHOWDEFAULT);
	InitialiseDirect3D(_hWnd);
	_frame = (this);
	_controller = new GamePadController();
	// Create Scenegraph
	_scene = new SceneGraph(device, deviceContext, swapChain, renderTarget);
}


//-----------------------------------------------------------------------------
// Name: Initialise
// Desc: Initializes Window
//-----------------------------------------------------------------------------
bool Framework::Initialise(HINSTANCE hInstance)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = windPROC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"D3DWndClassName";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		PostQuitMessage(0);
	}

	// Create the application's window
	//_hWnd = CreateWindow(L"D3DWndClassName", L"Framework", WS_OVERLAPPEDWINDOW, 100, 100, 1024 ,800, 0, 0, wc.hInstance, 0);
	_hWnd = CreateWindow(L"D3DWndClassName", L"Framework", WS_OVERLAPPEDWINDOW, 100, 100, _screenWidth, _screenHeight, 0, 0, wc.hInstance, 0);

	if (!_hWnd)
	{
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		PostQuitMessage(0);
	}

	UnregisterClass(L"Framework", wc.hInstance);
	return 0;
}

//-----------------------------------------------------------------------------
// Name: Run()
// Desc: Process Windows Messages
//-----------------------------------------------------------------------------
int Framework::Run(void)
{
	LARGE_INTEGER counterFrequency;
	LARGE_INTEGER nextTime;				// Time to render next frame
	LARGE_INTEGER currentTime;
	LARGE_INTEGER lastTime;
	double timeFactor;
	double _timeSpan;
	DWORD msPerFrame = 40;				// MS per frame - default if no performance counter is available
	bool usePerformanceCounter = false;
	bool updateFlag = true;
	if (QueryPerformanceFrequency(&counterFrequency))
	{
		// We can use a performance counter
		usePerformanceCounter = true;
		msPerFrame = (DWORD)(counterFrequency.QuadPart / 25);
		timeFactor = 1.0 / counterFrequency.QuadPart;
		QueryPerformanceCounter(&nextTime);
		lastTime = nextTime;
	}
	else
	{
		// We do not have a performance counter, so use timeGetTime
		//nextTime.QuadPart = timeGetTime();
		//timeFactor = 0.001;
		//lastTime = nextTime;
	}

	msg.message = WM_NULL;
	while (msg.message != WM_QUIT && GetAsyncKeyState(VK_ESCAPE) == 0)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (updateFlag)
			{
				if (usePerformanceCounter)
				{
					QueryPerformanceCounter(&currentTime);
				}
				else
				{
					//currentTime.QuadPart = timeGetTime();
				}
				_timeSpan = (currentTime.QuadPart - lastTime.QuadPart) * timeFactor;
				lastTime = currentTime;
				// _timeSpan should be made available to all of the scene nodes so that they know
				// how much time has elapsed since the last update.
				Update();
				updateFlag = false;
			}
			// Use appropriate mechanism to get time
			if (usePerformanceCounter)
			{
				QueryPerformanceCounter(&currentTime);
			}
			else
			{
				//currentTime.QuadPart = timeGetTime();
			}
			// Is it time to render the frame?
			if (currentTime.QuadPart > nextTime.QuadPart)
			{
				Render();
				// Set time for next frame
				nextTime.QuadPart += msPerFrame;
				// If we get more than a frame ahead, allow one to be dropped
				// Otherwise, we will never catch up if we let the error accumulate
				// and message handling will suffer
				if (nextTime.QuadPart < currentTime.QuadPart)
				{
					nextTime.QuadPart = currentTime.QuadPart + msPerFrame;
				}
				updateFlag = true;
			}

		}
	}
	return (int)msg.wParam;
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
bool Framework::InitialiseDirect3D(HWND hWnd)
{
	RECT dimensions;

#pragma region Array of driver types that we want to check for in order of preference
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_SOFTWARE
	};

	unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);
#pragma endregion

#pragma region Array of feature levels we require in order of preference
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	unsigned int totalFeatureLevels = ARRAYSIZE(featureLevels);
#pragma endregion

#pragma region Get the width and height of the window client area
	GetClientRect(hWnd, &dimensions);
	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions.bottom - dimensions.top;
#pragma endregion

#pragma region Setup the swap chain descriptor
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	// Start out windowed
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 4;
	swapChainDesc.SampleDesc.Quality = 0;
#pragma endregion

#pragma region Loop through the driver types to determine which one is available to us
	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_UNKNOWN;

	for (unsigned int driver = 0; driver < totalDriverTypes && driverType == D3D_DRIVER_TYPE_UNKNOWN; driver++)
	{
		if (SUCCEEDED(D3D11CreateDeviceAndSwapChain(0,
			driverTypes[driver],
			0,
			0,
			featureLevels,
			totalFeatureLevels,
			D3D11_SDK_VERSION,
			//D3D11_CREATE_DEVICE_DEBUG,
			&swapChainDesc, &swapChain,
			&device,
			0,
			&deviceContext)))

		{
			driverType = driverTypes[driver];
		}
	}
	if (driverType == D3D_DRIVER_TYPE_UNKNOWN)
	{
		// Unable to find a suitable device driver
		return false;
	}
#pragma endregion

#pragma region Create the depth buffer 
	// Create a texture for the depth buffer
	D3D11_TEXTURE2D_DESC zBufferTexture;
	ZeroMemory(&zBufferTexture, sizeof(zBufferTexture));
	zBufferTexture.Width = width;
	zBufferTexture.Height = height;
	zBufferTexture.ArraySize = 1;
	zBufferTexture.MipLevels = 1;
	zBufferTexture.SampleDesc.Count = 4;
	zBufferTexture.Format = DXGI_FORMAT_D32_FLOAT;
	zBufferTexture.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D * depthBuffer;
	if (FAILED(device->CreateTexture2D(&zBufferTexture, NULL, &depthBuffer)))
	{
		return false;
	}

	// Create the depth buffer
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	if (FAILED(device->CreateDepthStencilView(depthBuffer, &dsvd, &zBuffer)))
	{
		return false;
	}
	depthBuffer->Release();
#pragma endregion

#pragma region Get a pointer to the back buffer and set it as our render target
	ID3D11Texture2D * backBuffer;
	if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer)))
	{
		return false;
	}
	// Use the back buffer as the render target
	if (FAILED(device->CreateRenderTargetView(backBuffer, NULL, &renderTarget)))
	{
		return false;
	}
	// Ensure we release the back buffer interface
	backBuffer->Release();

	// Now bind the render target to the output-merger stage
	deviceContext->OMSetRenderTargets(1, &renderTarget, zBuffer);
#pragma endregion

#pragma region Set the viewport
	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	deviceContext->RSSetViewports(1, &viewport);
#pragma endregion
	return true;
}


bool InitialisePipeline(void)
{
	/*
	memcpy(ms.pData, triangleVertices, sizeof(triangleVertices));
	deviceContext->Unmap(vertexBuffer, NULL);

	if (FAILED(device->CreateInputLayout(ied, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &layout)))
	{
		return false;
	}
	deviceContext->IASetInputLayout(layout);
	*/

	return true;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Framework::Shutdown()
{
	/*
		// Make sure we release any Direct3D interfaces we have used
		if (psBlob != NULL)
		{
			psBlob->Release();
			psBlob = NULL;
		}
		if (vsBlob != NULL)
		{
			vsBlob->Release();
			vsBlob = NULL;
		}
		if (layout != NULL)
		{
			layout->Release();
			layout = NULL;
		}
		if (vertexBuffer != NULL)
		{
			vertexBuffer->Release();
			vertexBuffer = NULL;
		}
		if (vertexShader != NULL)
		{
			vertexShader->Release();
			vertexShader = NULL;
		}
		if (pixelShader != NULL)
		{
			pixelShader->Release();
			pixelShader = NULL;
		}
		if (renderTarget != NULL)
		{
			renderTarget->Release();
			renderTarget = NULL;
		}
		if(swapChain != NULL)
		{
			swapChain->Release();
			swapChain = NULL;
		}
		if (deviceContext != NULL)
		{
			deviceContext->Release();
			deviceContext = NULL;
		}
		if (device != NULL)
		{
			device->Release();
			device = NULL;
		}
	*/

	/*
	if(_pd3dDevice)
	{
		SAFE_RELEASE(_pd3dDevice);
	}

	if(_pD3D)
	{
		SAFE_RELEASE(_pD3D);
	}
	*/
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Framework::Render()
{
	///*
	//	// Clear the screen to black
	//	float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	//	deviceContext->ClearRenderTargetView(renderTarget, clearColor);
	//
	//	// Clear the depth buffer
	//	deviceContext->ClearDepthStencilView(zBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//*/
	_scene->Render();
	///*
	//	// Show the back buffer in the window
	//	swapChain->Present(0, 0);
	//*/
}

//-----------------------------------------------------------------------------
// Name: windPROC()
// Desc: The window's procedure
//-----------------------------------------------------------------------------
LRESULT CALLBACK Framework::windPROC(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (_frame != NULL)
	{
		return _frame->MsgProc(hWnd, msg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT Framework::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	float _amountOfMovement = 2.5f;
	float _rotationAmount = 0.015f;
	switch (msg)
	{
	case WM_DESTROY:
		_frame->Shutdown();
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		_frame->Update();
		_frame->Render();
		ValidateRect(hWnd, NULL);
		return 0;

	case WM_MOUSEMOVE:
	{
		//// Store the old mouse positions
		//_oldMouseX = _mouseX;
		//_oldMouseY = _mouseY;

		//// Retrieve mouse screen position
		//_mouseX = (short)LOWORD(lParam);
		//_mouseY = (short)HIWORD(lParam);

		//if (_mouseY < 200)
		//{
		//	_mouseY = 200;
		//}
		//
		//if (_mouseY > 450)
		//{
		//	_mouseY = 450;
		//}

		//if ((_mouseX -_oldMouseX) > 0)
		//{
		//	_renderCamera->Yaw(_rotationAmount * 1);
		//}

		//if ((_mouseX -_oldMouseX) < 0)
		//{
		//	_renderCamera->Yaw(_rotationAmount * -1);
		//}
	}

	case WM_KEYDOWN:
		switch (wParam)
		{
			// Move the camera forward
		case 'q':
		case 'Q':
			//_renderCamera->MoveForward(_amountOfMovement);
			break;

			// Move the camera backward
		case 'w':
		case 'W':
			//_renderCamera->MoveForward(_amountOfMovement * -1);
			break;

			//To move camera up
		case 'a':
		case 'A':
			_renderCamera->MoveUp(_amountOfMovement);
			break;

			//To move camera down
		case 's':
		case 'S':
			_renderCamera->MoveUp(_amountOfMovement * -1);
			break;
		case 'b':
		case 'B':
			_tank->FireBullet();
			break;
			//Change to 1st person camera
		case '1':
			//_tank->SetCameraType(false);
			//_renderCamera->SetCameraType(false);
			//_renderCamera->Pitch(_rotationAmount * 1);
			break;

			//Change to 3rd person camera
		case '2':
			//_tank->SetCameraType(true);
			//_renderCamera->SetCameraType(true);
			//_renderCamera->Pitch(_rotationAmount * -1);
			break;

		case '3':
			//_tank->SetCameraType(false);
			//_renderCamera->SetCameraType(false);
			//_renderCamera->Roll(_rotationAmount * 1);
			break;

			//Change to 3rd person camera
		case '4':
			//_tank->SetCameraType(true);
			//_renderCamera->SetCameraType(true);
			//_renderCamera->Roll(_rotationAmount * -1);
			break;

		case '5':
			//_tank->SetCameraType(false);
			//_renderCamera->SetCameraType(false);
			//_renderCamera->Yaw(_rotationAmount * 1);
			break;

			//Change to 3rd person camera
		case '6':
			//_tank->SetCameraType(true);
			//_renderCamera->SetCameraType(true);
			//_renderCamera->Yaw(_rotationAmount * -1);
			break;

			// Rotate the camera anti clockwise
		case VK_LEFT:
			_renderCamera->Yaw(_amountOfMovement * -1);
			break;

			// Rotate the camera clockwise
		case VK_RIGHT:
			_renderCamera->Yaw(_amountOfMovement);
			break;

		case VK_UP:
			_renderCamera->MoveForward(_amountOfMovement);
			break;

		case VK_DOWN:
			_renderCamera->MoveForward(_amountOfMovement * -1);
			break;

		case VK_ESCAPE:
			_quit = true;
			break;

		default:
			break;
		}
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

//-----------------------------------------------------------------------------
// Name: CheckDeviceCapabilities()
// Desc: Checks Device Capabilities
//-----------------------------------------------------------------------------
bool Framework::CheckDeviceCapabilities(void)
{
	/*
	 D3DCAPS9 _capability;
	_pd3dDevice->GetDeviceCaps(&_capability);

		// Check for hardware vertex processing
	if(_capability.DevCaps && D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		return true;
	}

	// Check for Pure Device
	if(_capability.DevCaps && D3DDEVCAPS_PUREDEVICE)
	{
		return true;
	}
	*/
	return false;
}

//-----------------------------------------------------------------------------
// Name: OnLostDevice()
// Desc: On Lost Device
//-----------------------------------------------------------------------------
void Framework::OnLostDevice(void)
{
	/*
	// Get the state of the graphics device.
	HRESULT hr = _pd3dDevice->TestCooperativeLevel();

	// If the device is lost and cannot be reset yet then
	// sleep for a bit and we'll try again on the next
	// message loop cycle.
	if( hr == D3DERR_DEVICELOST )
	{
		Sleep(20);
	}
	// Driver error, exit.
	else if( hr == D3DERR_DRIVERINTERNALERROR )
	{
		MessageBox(0, L"Internal Driver Error...Exiting", 0, 0);
		PostQuitMessage(0);
	}
	// The device is lost but we can reset and restore it.
	else if( hr == D3DERR_DEVICENOTRESET )
	{
		OnLostDevice();
		OnResetDevice();
	}
	*/
}

//-----------------------------------------------------------------------------
// Name: OnResetDevice()
// Desc: On Reset Device
//-----------------------------------------------------------------------------
void Framework::OnResetDevice(void)
{
}

//-----------------------------------------------------------------------------
// Name: Update()
// Desc: Update the Framework
//-----------------------------------------------------------------------------
void Framework::Update(void)
{
	_controller->ProcessGameController();
	//_scene->Update();
}

//-----------------------------------------------------------------------------
// Name: TextDisplay()
// Desc: Output Text to the screen
//-----------------------------------------------------------------------------
//void Tank::TextDisplay()
//{
//	//std::ostringstream output;
//	//output
//	//	<< "1 : 1st Person Camera" << std::endl
//	//	<< "2 : 3rd Person Camera" << std::endl
//	//	<< "Q : Move Forward" << std::endl
//	//	<< "W : Move Backward" << std::endl
//	//	<< "A : Look Up" << std::endl
//	//	<< "S : Look Down" << std::endl
//	//	<< "Mouse : Rotate Left & Right" << std::endl;
//
//	//string _string = output.str().c_str();
//	//wstring _wideString;
//
//	//_wideString.assign(_string.begin(), _string.end());
//
//	//LPCWSTR _textString = _wideString.c_str();
//
//	//RECT R = {5, 5, 0, 0};
////	mFont->DrawText(0, _textString, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(0,0,0));
//}

//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Set up Matrices
//-----------------------------------------------------------------------------
//void Framework::SetupMatrices(void)
//{
//}
//
//Accessors & Mutators
ID3D11Device* Framework::GetDirectDevice(void)
{
	return device;
}

ID3D11DeviceContext* Framework::GetDirectDeviceContext(void)
{
	return deviceContext;
}

IDXGISwapChain* Framework::GetSwapChain(void)
{
	return swapChain;
}

ID3D11RenderTargetView* Framework::GetRenderTarget(void)
{
	return renderTarget;
}

SceneGraph * Framework::GetSceneGraph(void)
{
	return _scene;
}

HWND Framework::GetHandle(void)
{
	return _hWnd;
}

void Framework::SetCamera(Camera* renderCam)
{
	_renderCamera = renderCam;

	// Make the camera accessible to the controller
	_controller->SetCamera(_renderCamera);
}

//void Framework::SetTank(Tank* tank)
//{
//	_tank = tank;
//}

////CameraRender* Framework::GetCamera(void)const
//Camera* Framework::GetCamera(void)const
//{
//	return _renderCamera;
//}


void Framework::SetTerrain(TerrainNode* terrainNode)
{
	_terrain = terrainNode;
}

TerrainNode* Framework::GetTerrain(void)const
{
	return _terrain;
}

//void Framework::GetController(void)const
//{
//	_controller->SetTank(_tank);
//	_controller->SetCamera(_renderCamera);
//}

void Framework::SetObjects(Camera* camera, Tank* tank, SkyDome* skyDome, FrameWorkResourceManager* frameResourcesManager)
{
	_renderCamera = camera;
	_skyDome = skyDome;
	_tank = tank;
	_frameWorkResourceManager = frameResourcesManager;
}

ID3D11DepthStencilView* Framework::GetStencilBuffer(void)const
{
	return zBuffer;
}