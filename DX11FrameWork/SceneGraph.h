#include "BoundingShape.h"
#include "SceneNode.h"
//#include <d3d11_1.h>
#include <d3d11.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <string>
#include "Camera.h"

//class Camera;

#pragma once
using namespace std;

__declspec(align(16)) class SceneGraph : public SceneNode
{
public:
	SceneGraph(void);
	~SceneGraph(void);
	//SceneGraph(	LPDIRECT3DDEVICE9 pd3dDevice);
	//SceneGraph(ID3D11Device* device);
	SceneGraph(ID3D11Device* device, ID3D11DeviceContext* deviceContext, IDXGISwapChain* swapChain, ID3D11RenderTargetView* renderTarget);

    HRESULT Initialise(void); 
    void OnLostDevice(void); 
    void OnResetDevice(void); 
    void Update(void); 
    HRESULT Render(void); 
    void Shutdown(void); 
	void SetCamera(Camera* camRender);
    bool AddNode(SceneNode* node, wstring parentNode); 
	bool RemoveNode(unsigned int node);
    SceneNode* FindNode(wstring name); 
    SceneNode* FindNode(SceneNode* nodeToFind); 

protected:
	#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }

private:
	int FindANode(wstring name);
	
    // The scene root node
    SceneNode* _rootNode;
	vector <SceneNode*> _nodes;
	Camera* _camera;
};