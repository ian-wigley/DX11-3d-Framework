////#include "CameraRender.h"
//#include "Camera.h"
#include "Framework.h"
#include "FrameWorkResourceManager.h"
#include <iostream>
#include <fstream>

#include "DDSTextureLoader.h"
#include <d3d11.h>
///#include <d3d11_1.h>

#include <directxmath.h>
#include <d3dcompiler.h>
#include <directxcolors.h>

#pragma comment(lib, "D3dcompiler.lib")


#pragma once
using namespace DirectX;
using namespace std;

//
////_DECLSPEC_ALIGN_16_ 
class TerrainNode :	public SceneNode
{
public:
	TerrainNode(void);
	~TerrainNode(void);
//	TerrainNode(wstring name, Framework *_frame);
	TerrainNode(wstring name, Framework *_frame , FrameWorkResourceManager* frameResourcesManager);
	HRESULT Render(void);
	HRESULT InitialiseShaders(void);
	void GenerateVertices();
	void GenerateIndices();
	void Update(void);

	void SetCamera(Camera* _cameraRender);
	float GetHeight(float x, float z);

	void UpdateViewMatrix(XMMATRIX& viewMatrix);


	//struct VERTEX
	//{
	//	XMFLOAT3 position;	// The position
	//	XMFLOAT3 normal;	// The normal
	//	XMFLOAT2 texel;		// The texture co-ords
	//};


//
//
//	CBUFFER* GetCbuffer(void);
//	ID3D11Buffer* GetConstBuffer(void)const;
////	CBUFFER* _cBuffer;
//
//
//	//VERTEX * modelVertices;
//	//VERTEX * currentVertex;
//	//unsigned int * modelIndices;
//	//unsigned int * currentIndex;
//
////	std::vector<VERTEX>					_vertices;			// List of vertices
////	std::vector<DWORD>					_indices;			// List of indexes


	UINT								_numVertices;		// The number of vertices in the grid
	DWORD								_numTriangles;		// Total number of triangles in the grid
	UINT								_numIndices;

	DWORD								_gridSize;			// Size of gird (number of rows or cells on each side)
	int									_numCellRows;		// Maximum cell number in a row (_gridSize - 1)
	int									_numCellCols;		// Maximum cell number in a column (_gridSize - 1)
	float								_spacing;			// Width of a grid square
	DWORD								_colour;			// Colour to use for wireframe drawing
	std::vector<float>					_heights;			// The array of height values read from the height map

private:
	
	struct CBUFFER
	{
		XMMATRIX CompleteTransformation;
		XMMATRIX WorldTransformation;
		XMMATRIX Rotation;
		XMVECTOR LightVector;
		XMFLOAT4 LightColor;
		XMFLOAT4 AmbientColor;
	};

	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX CompleteTransformation;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMVECTOR lightDirection;
		float padding;
	};



	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_matrixBuffer;




	void Shutdown(void);
	void CalculateVertexNormals(void);
	HRESULT Initialise(void);

	float _height;
	float _eye;
	float _terrainStartX;
	float _terrainStartZ;
	float _v0;



	ID3D11SamplerState*         g_pSamLinear = nullptr;


	ID3D11ShaderResourceView *	_texture;
	ID3D11Device *				_device;
	ID3D11DeviceContext *		_deviceContext;
	IDXGISwapChain *			_swapChain;
	ID3D11RenderTargetView *	_renderTarget;
	ID3D11DepthStencilView *	_zBuffer;

	ID3DBlob *				 vsBlob;
	ID3DBlob *				 psBlob;
	ID3D11VertexShader *	 vertexShader;
	ID3D11PixelShader *		 pixelShader;
	ID3D11Buffer *			 vertexBuffer;
	ID3D11Buffer *			 indexBuffer;
	ID3D11Buffer *			 constantBuffer;

	ID3D11InputLayout *		 layout;

	XMMATRIX _completeTransformation;
	XMMATRIX _viewTransformation;
	XMMATRIX _projectionTransformation;
	XMMATRIX _worldTransformation;

    XMFLOAT4 _ambientLightColour;
    XMFLOAT4 _directionalLightColour;
    XMVECTOR _directionalLightVector;

	CBUFFER cBuffer;

	Camera* _camRender;
	//Framework* _frame;
	FrameWorkResourceManager* _frameWorkResourcesManager;
};

