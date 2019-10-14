#include <Windows.h>
#include <vector>

// DirectX include files - Make sure that $(DSSDK_DIR)Include is on the VC++ Directories Include path
#include <d3d11.h>
#include <directxmath.h>

// DirectX libraries that are needed - make sure that $(DSSDK_DIR)lib\x86 is on the VC++ Directories Lib path
//#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "D3dcompiler.lib")

using namespace DirectX;

#pragma once
using namespace std;

class BoundingShape;

// The format of our vertices
struct VERTEX
{
	XMFLOAT3 Position;  // position
	XMFLOAT3 Normal;    // normal
	XMFLOAT2 TexCoord;   // Texture UV Coordinates
};

struct CBUFFER
{
	XMMATRIX    CompleteTransformation;
	XMMATRIX	WorldTransformation;
	XMVECTOR    LightVector;
	XMFLOAT4    LightColor;
	XMFLOAT4    AmbientColor;
};

__declspec(align(16)) class SceneNode
{
public:
	SceneNode(void);
	SceneNode(wstring name);
	SceneNode(wstring name, HWND hWnd);
	~SceneNode(void);

	// Core methods 
	virtual HRESULT Initialise(void);
	virtual void OnLostDevice(void); 
	virtual void OnResetDevice(void); 
	virtual void Update(void);          
	virtual HRESULT Render(void);          
	virtual void Shutdown(void); 

	// Intersection testing
	virtual bool IsIntersecting(SceneNode* otherShape);
	wstring GetType(void)const;

	// Events 
	virtual void OnAdded(void) {} ;
	virtual void OnRemoved(void){} ;

	// Child changes 
	bool AddChild(SceneNode* child); 
	bool RemoveChild(unsigned int child);
	void RemoveAllChildren(void); 

	void SetParent(SceneNode* parent);         
	inline SceneNode* GetParent(void) const;  
	inline SceneNode* GetName(void) const;

	//Graph searching 
	SceneNode* FindNode(wstring name);
	SceneNode* FindNode(SceneNode* nodeToFind); 

	vector<SceneNode*> GetNodeList(void) const;

	virtual void ExternalDeleteMe(bool deleteMe);
	virtual bool CheckDirectionX(void);
	virtual bool CheckDirectionZ(void);
//	virtual void SetPosition(XMVECTOR distance);

	bool DeleteMe(void);
	wstring ReturnName(void);

protected:

	HWND _hWnd;
	wstring _name;               

	#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }

	 // converts from degrees to radians
	#define DEGTORAD(degree) ((D3DX_PI / 180.0f) * (degree))
	// converts from radians to degrees
	#define RADTODEG(radian) ((180.0f / D3DX_PI) * (radian)) 

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	IDXGISwapChain*	m_swapChain;
	ID3D11RenderTargetView* m_renderTarget;

	D3D11_BUFFER_DESC m_bufferDesc;
	UINT m_numIndices;
	UINT m_numVertices;
	VERTEX* m_vertices;
	DWORD* m_indices;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	ID3D11Buffer* m_constantBuffer;
	D3D11_MAPPED_SUBRESOURCE ms1;
	ID3D11RasterizerState* m_wireFrame;
	ID3D11DepthStencilView*	m_zBuffer;
	ID3D11ShaderResourceView* m_texture;

	float _cameraSpeed;
    float _angle;
	float _yaw;						// Degrees of yaw (in radians)
	float _pitch;					// Degrees of pitch (in radians)
	float _roll;					// Degrees of roll (in radians)
	float m_x;
	float m_y;
	float m_z;
	float _scale;

	bool _collsion;
	bool _delete;

	wstring _type;

	DWORD _numberOfMaterials;
	VERTEX* modelVertices;
	vector<UINT> indices;

	XMMATRIX m_projectionTransformation;
	XMMATRIX m_scalingMatrix;
	XMMATRIX m_worldTransformation;

	HRESULT InitialiseGeometry(void);

private:
	SceneNode* _parentNode;			// The parent of the scene node 
	vector<SceneNode*>  _children;  // The scene nodes child nodes
};