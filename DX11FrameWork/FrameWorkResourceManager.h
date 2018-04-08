#include "Framework.h"
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

#include <d3d11_1.h>
#include <directxmath.h>

#include <iostream>
#include <fstream>

#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#pragma once

using namespace std;


class FrameWorkResourceManager
{
public:
	FrameWorkResourceManager(void);
	FrameWorkResourceManager(Framework* _frame);
	~FrameWorkResourceManager(void);
	void Shutdown(void);

	void SetTexture(wstring name);

	HRESULT LoadTextures(wstring filename);
	vector<float> LoadHeightMap(wstring filename, DWORD gridSize);

	ID3D11ShaderResourceView* GetTexture(wstring name);

	//	D3DMATERIAL9* GetMaterial(wstring name);

	DWORD GetNumberOfMatrials(void);
	//	D3DMATERIAL9 GetDefaultMaterial(void);
	//	D3DMATERIAL9 GetDefaultBlackMaterial(void);
private:

	LPCWSTR StringFormat(wstring name);

	//	map<wstring, LPD3DXMESH> _meshes;
	//	map<wstring, D3DMATERIAL9*> _materials;
	//	map<wstring, ID3D11ShaderResourceView> _textures;

		// Specify an iterator
	//	map<wstring, LPD3DXMESH>::iterator _meshIterator;
	//	map<wstring, D3DMATERIAL9*>::iterator _materialsIterator;
	//	map<wstring, ID3D11ShaderResourceView>::iterator _textureIterator;

	ID3D11ShaderResourceView* _texture;

	ID3D11Device* _device;


	void SetMultipleMaterials(void);

	// The array of height values read from the height map
	vector<float> _heights;

	//Todo
	// UnzipResources();
	//
};

