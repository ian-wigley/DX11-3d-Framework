#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include "Framework.h"

#pragma comment(lib, "D3dcompiler.lib")
using namespace DirectX;
using namespace std;

class Shader
{
public:
	Shader();
	Shader(Framework* frame);
	~Shader();
	HRESULT InitialiseShader();

	UINT	_numVertices;		// The number of vertices in the grid
	DWORD	_numTriangles;		// Total number of triangles in the grid
	UINT	_numIndices;

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

	// Describe the Vertex Buffers format that is being passed to the shader GPU
	D3D11_INPUT_ELEMENT_DESC ied[3];

	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_matrixBuffer;

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
};

