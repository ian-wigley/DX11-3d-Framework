#pragma once
#include "SceneNode.h"
#include "Framework.h"
#include "FrameWorkResourceManager.h"
#include "CameraRender.h"
#include "DDSTextureLoader.h"

class SkyDome :
	public SceneNode
{
public:
	SkyDome(void);
	~SkyDome(void);
	SkyDome(wstring name, Framework* frame, FrameWorkResourceManager* _frameResourcesManager);
	HRESULT Render(void);
	void SetCamera(Camera* _cameraRender);

private:
	void Shutdown(void);
	HRESULT InitialiseDome(void);
	void LoadDome(void);
	HRESULT Initialise(void);

	XMMATRIX _saveView;

	//CameraRender* _renderCamera;
	Framework* _frame;
	FrameWorkResourceManager* _frameWorkResourcesManager;
	Camera* _camRender;

	vector<Mesh> meshy;

};

