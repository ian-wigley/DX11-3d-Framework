#include "SceneGraph.h"
#include <Windows.h>
#include <string>
#include "GamePadController.h"
#include <XInput.h>
#include "Camera.h"

// DirectX include files - Make sure that $(DSSDK_DIR)Include is on the VC++ Directories Include path
#include <d3d11.h>
#include <directxmath.h>

// DirectX libraries that are needed - make sure that $(DSSDK_DIR)lib\x86 is on the VC++ Directories Lib path
//#pragma comment(lib, "d3d11.lib")

class Tank;
class SkyDome;
class FrameWorkResourceManager;

using namespace std;

#pragma once
class Framework
{
public:

	Framework(void);
	Framework(HINSTANCE hInstance);
	~Framework(void);

	ID3D11Device* GetDirectDevice(void);
	ID3D11DeviceContext* GetDirectDeviceContext(void);
	IDXGISwapChain* GetSwapChain(void);
	ID3D11RenderTargetView* GetRenderTarget(void);

	HWND GetHandle(void);

	// Framework methods.  Derived client class overrides these methods to  
	// implement specific application requirements. 

	virtual bool Initialise(HINSTANCE hInstance);
	virtual void Shutdown(void);
	virtual int Run(void);
	virtual bool CheckDeviceCapabilities(void);
	virtual void OnLostDevice(void);
	virtual void OnResetDevice(void);
	virtual void Update(void);
	virtual void Render(void);

	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//HRESULT InitD3D( HWND hWnd );
	bool InitialiseDirect3D(HWND hWnd);
	bool InitialisePipeline(void);

	static LRESULT CALLBACK windPROC(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	SceneGraph* GetSceneGraph(void);

	void SetCamera(Camera* _renderCam);
	//Camera* GetCamera(void)const;
	//void SetTank(Tank* tank);
	void SetTerrain(TerrainNode* terrainNode);
	TerrainNode* GetTerrain(void)const;
	//void GetController(void)const;

	ID3D11DepthStencilView* GetStencilBuffer(void)const;
	void SetObjects(Camera* camera, Tank* tank, SkyDome* skyDome, FrameWorkResourceManager* frameResourcesManager);

protected:
#define SAFE_DELETE(x) { delete x; x = NULL; }
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }

private:
	int _screenWidth;
	int _screenHeight;
	int _oldMouseX;
	int _oldMouseY;
	int _mouseX;
	int _mouseY;

	bool _quit;

	MSG msg;
	HWND _hWnd;
	SceneGraph* _scene;

	//void SetupMatrices(void);

	GamePadController* _controller;
	Camera* _renderCamera;
	SkyDome* _skyDome;
	Tank* _tank;
	TerrainNode* _terrain;

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain*	swapChain;
	ID3D11RenderTargetView* renderTarget;
	ID3D11DepthStencilView* zBuffer;
};