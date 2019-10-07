#include <Windows.h>
#include <vector>

// DirectX include files - Make sure that $(DSSDK_DIR)Include is on the VC++ Directories Include path
#include <d3d11.h>
//#include <d3d11_1.h>
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

class SceneNode
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


	ID3D11Device* _device;
	ID3D11DeviceContext* _deviceContext;
	IDXGISwapChain*	_swapChain;
	ID3D11RenderTargetView* _renderTarget;

	HRESULT InitialiseGeometry(void);
	D3D11_BUFFER_DESC bufferDesc;
	UINT m_numIndices;
	UINT m_numVertices;// = 24 * 3;
	VERTEX* m_vertices;
	DWORD* m_indices;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* constantBuffer;
	D3D11_MAPPED_SUBRESOURCE ms1;
//	VERTEX1* modelVertices1;
	ID3D11Device* _pd3dDevice;
	ID3D11RasterizerState* pRSWireFrame1;
	ID3D11DepthStencilView*	_zBuffer;
	ID3D11ShaderResourceView* _texture;



//
//	XMMATRIX _rotationMatrixX;
//	XMMATRIX _rotationMatrixY;
//	XMMATRIX _rotationMatrixZ;
//	
//	XMMATRIX _scalingingMatrix;
//	XMMATRIX _translationMatrix;
//	XMMATRIX _worldMatrix;
//	
//	XMMATRIX _viewMatrix;
//
////	XMVECTOR _up;
////	XMVECTOR _lookAt;
////	XMVECTOR _right;
////	XMVECTOR _position;
//
//	XMMATRIX yawMatrix;
//	XMMATRIX pitchMatrix;
//	XMMATRIX rollMatrix;

	float _cameraSpeed;
    float _angle;

	float _yaw;						// Degrees of yaw (in radians)
	float _pitch;					// Degrees of pitch (in radians)
	float _roll;					// Degrees of roll (in radians)

	float _x;
	float _y;
	float _z;

	float _scale;

	bool _collsion;
	bool _delete;

	wstring _type;

	DWORD _numberOfMaterials;
	VERTEX* modelVertices;
	//unsigned int* modelIndices;
	vector<UINT> indices;

	XMMATRIX projectionTransformation;
	XMMATRIX _scalingMatrix;
	XMMATRIX _worldTransformation;
	


private:
	SceneNode* _parentNode;			// The parent of the scene node 
	vector<SceneNode*>  _children;  // The scene nodes child nodes
};