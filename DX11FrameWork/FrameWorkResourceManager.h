#include "Framework.h"

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

/* assimp include files. These three are usually needed. */
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <d3d11.h>
#include "Shader.h"
////#include <d3d11_1.h>
////#include <directxmath.h>

#include <iostream>
#include <fstream>


#include <windows.graphics.imaging.h>
#include <windows.h>
#include <wincodec.h>
#include <commdlg.h>
#include <d2d1.h>

#include "TextureLoader.h"
#include "Mesh.h"

//#pragma warning( disable : 4996 ) // disable deprecated warning 
//#include <strsafe.h>
//#pragma warning( default : 4996 )
#pragma once

using namespace std;
using namespace DirectX;

class FrameWorkResourceManager
{
public:
	FrameWorkResourceManager(void);
	FrameWorkResourceManager(Framework* _frame);
	~FrameWorkResourceManager(void);
	void Shutdown(void);
	//
	//	void SetTexture(wstring name);
	//
	//	HRESULT LoadTextures(wstring filename);
	vector<float> LoadHeightMap(wstring filename, DWORD gridSize);
	ID2D1Bitmap* LoadBitmap(string Filename);


	/* the global Assimp scene object */
	const struct aiScene* scene = NULL;

	//int LoadAsset(const char* filename);
	//const aiScene* LoadAsset(const char* filename);
	aiScene* LoadAsset(const char* filename);
	//const aiScene* pScene;
	aiScene* pScene;
	//void GetMesh(void);
	void ProcessNode(aiNode * node, const aiScene * scene);

	vector<Mesh> GetMesh() { return meshes;	}

//	void ProcessNode(aiNode * node, const aiScene * scene);
	string determineTextureType(const aiScene * scene, aiMaterial * mat);
	vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName, const aiScene * scene);
	Mesh ProcessMesh(aiMesh * mesh, const aiScene * scene);
	int getTextureIndex(aiString * str);
	ID3D11ShaderResourceView* getTextureFromModel(const aiScene * scene, int textureindex);

	ID3D11DeviceContext *devcon;
	std::vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	HWND hwnd;

	IWICImagingFactory     *m_pIWICFactory;
	ID2D1Factory           *m_wicFactory;// m_pD2DFactory;
	ID2D1HwndRenderTarget  *m_pRT;
	ID2D1Bitmap            *m_Bitmap;// m_pD2DBitmap;
	IWICFormatConverter    *m_pConvertedSourceBitmap;

	DWORD GetNumberOfMaterials(void);

	ID3D11Device* _device;

	// The array of height values read from the height map
	vector<float> _heights;

	//Todo
	// UnzipResources();
	//

	private:
		Shader* shader;
};
