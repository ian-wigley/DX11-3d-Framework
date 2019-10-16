//-----------------------------------------------------------------------------
// File: FrameWorkTest.cpp
// Description : This Class managers the Application
//-----------------------------------------------------------------------------

#include "FrameWorkTest.h"

//CameraNode* _cameraNode;
//CameraRender* _camRender;
Camera* _camRender;
//Castle* _castle;
//DirectionalLight* _dirLight;
//ExplosionNode* _explosion;
FrameWorkResourceManager* _frameResourcesManager;
SkyDome* _skyDome;
Tank* _tank;
Tree* _tree;
TerrainNode* _tNode;
WoodenCrate* _woodenCrate;
//BulletNode* _bullet;

FrameWorkTest::FrameWorkTest(void)
{
}

FrameWorkTest::~FrameWorkTest(void)
{
	Shutdown();
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
void FrameWorkTest::Shutdown()
{
	//if (_dirLight != NULL)
	//{
	//	delete _dirLight;
	//}

	//if (_tNode != NULL)
	//{
	//	delete _tNode;
	//}

	//if (_woodenCrate != NULL)
	//{
	//	delete _woodenCrate;
	//}
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{

	Framework frameWork = Framework (hInstance);
	Framework*_frame = &frameWork;

	SceneGraph* _sGraph = _frame->GetSceneGraph();

	// Retrieve the necessary DirectX components 
	ID3D11Device* _device = _frame->GetDirectDevice();
	ID3D11DeviceContext* _deviceContext = _frame->GetDirectDeviceContext();

	_frameResourcesManager = new FrameWorkResourceManager(_frame);
	_sGraph->AddNode(_tNode = new TerrainNode(L"Terrain", _frame, _frameResourcesManager),L"Parent");
	// Set the TerrainNode up in the Framework
	_frame->SetTerrain(_tNode);

	//	_sGraph->AddNode(_dirLight = new DirectionalLight(L"DirectionalLight", _frame),L"Parent");


	//	_camRender = new CameraRender(_device, _tNode, _tank);
	//	_sGraph->AddNode(_cameraNode = new CameraNode(L"Camera"),L"Parent");

	_camRender = new Camera(_deviceContext, _tNode, _tank);
	_sGraph->SetCamera(_camRender);
	_frame->SetCamera(_camRender);

	// Set the TerrainNode up in the Framework
	//	_frame->SetTerrain(_tNode);

	_sGraph->AddNode(_tank = new Tank(L"Tank", _frame, -30.0f, -1000.0f, _frameResourcesManager),L"Parent");

//	_sGraph->AddNode(_woodenCrate = new WoodenCrate(L"WoodenCrate", _frame, -140.0f, -870.0f, _frameResourcesManager),L"Parent");
//	//_sGraph->AddNode(_woodenCrate = new WoodenCrate(L"WoodenCrate", _frame, -500.0f, 500.0f, _frameResourcesManager),L"Parent");
	
	_sGraph->AddNode(_skyDome = new SkyDome(L"SkyDome", _frame, _frameResourcesManager), L"Parent");

	//_sGraph->AddNode(_tree = new Tree(L"Tree", _frame, -500.0f, -970.0f, _frameResourcesManager),L"Parent");
	//_sGraph->AddNode(_tree = new Tree(L"Tree", _frame, 800.0f, 570.0f, _frameResourcesManager),L"Parent");
	//_sGraph->AddNode(_tree = new Tree(L"Tree", _frame, 710.0f, 670.0f, _frameResourcesManager),L"Parent");
	//_sGraph->AddNode(_tree = new Tree(L"Tree", _frame, 310.0f, 870.0f, _frameResourcesManager),L"Parent");
	//_sGraph->AddNode(_tree = new Tree(L"Tree", _frame, 10.0f, 970.0f, _frameResourcesManager),L"Parent");
	//_sGraph->AddNode(_castle = new Castle(L"Castle", _frame, 80.0f, 0.0f, _frameResourcesManager),L"Parent");

	_frame->SetObjects(_camRender, _tank, _skyDome,_frameResourcesManager);

	// pass a pointer to the controller class of the tank & skyDome
	//	_frame->GetController();

	// Required go get the view matrix
	_tNode->SetCamera(_camRender);
//	_woodenCrate->SetCamera(_camRender);
	_tank->SetCamera(_camRender);
	_skyDome->SetCamera(_camRender);

	return _frame->Run();
}