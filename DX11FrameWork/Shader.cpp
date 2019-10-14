#include "Shader.h"

Shader::Shader()
{
}

Shader::Shader(Framework* frame)
{
	_device = frame->GetDirectDevice();
	_deviceContext = frame->GetDirectDeviceContext();
	_swapChain = frame->GetSwapChain();
	_renderTarget = frame->GetRenderTarget();
	_zBuffer = frame->GetStencilBuffer();
}

Shader::~Shader()
{
}

HRESULT Shader::InitialiseShader()
{
	ied[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	ied[1] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	ied[2] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 };

	//D3D11_BUFFER_DESC bufferDesc;
	//D3D11_MAPPED_SUBRESOURCE ms;
	//D3D11_SAMPLER_DESC samplerDesc;
	//D3D11_BUFFER_DESC matrixBufferDesc;
	//D3D11_BUFFER_DESC lightBufferDesc;

#pragma region Compile and set vertex shader
	if (FAILED(D3DCompileFromFile(L"TerrainShader.hlsl", 0, 0, "main", "vs_4_0", 0, 0, &vsBlob, 0)))
	{
		return false;
	}
	if (FAILED(_device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vertexShader)))
	{
		return false;
	}
	_deviceContext->VSSetShader(vertexShader, 0, 0);
#pragma endregion

#pragma region Compile and set pixel shader
	if (FAILED(D3DCompileFromFile(L"TerrainShader.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, &psBlob, 0)))
	{
		return false;
	}
	if (FAILED(_device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &pixelShader)))
	{
		return false;
	}
	_deviceContext->PSSetShader(pixelShader, 0, 0);
#pragma endregion

#pragma region Specify input element format of data passed to vertex shader
	if (FAILED(_device->CreateInputLayout(ied, ARRAYSIZE(ied), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &layout)))
	{
		return false;
	}
	_deviceContext->IASetInputLayout(layout);
#pragma endregion

	return S_OK;
}