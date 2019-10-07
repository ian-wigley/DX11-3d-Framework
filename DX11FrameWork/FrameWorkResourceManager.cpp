//-----------------------------------------------------------------------------
// File: FrameWorkResourceManager.cpp
// Description : This Class managers the Resources

//-----------------------------------------------------------------------------

#include "FrameWorkResourceManager.h"


#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

//#include "ModelLoader.h"
//
//ModelLoader *ourModel;

//-----------------------------------------------------------------------------
// Name: FrameWorkResourceManager()
// Desc: Load the Texture into memory if it doesnt already exist
//-----------------------------------------------------------------------------
FrameWorkResourceManager::FrameWorkResourceManager(Framework* _frame)
{
	_device = _frame->GetDirectDevice();//GetDirect3dDevice();


	shader = new Shader(_frame);
	shader->InitialiseShader();

	//LoadAsset("../../../../test/models-nonbsd/X/dwarf.x");
	//LoadAsset("Tiger.x");

}

//-----------------------------------------------------------------------------
// Name: ~FrameWorkResourceManager()
// Desc: Load the Texture into memory if it doesnt already exist
//-----------------------------------------------------------------------------
FrameWorkResourceManager::~FrameWorkResourceManager(void)
{
	Shutdown();
}

//-----------------------------------------------------------------------------
// Name: Shutdown()
// Desc: Releases all memory
//-----------------------------------------------------------------------------
void FrameWorkResourceManager::Shutdown(void)
{
	/*
	if(_texture)
	{
		SAFE_RELEASE(_texture);
	}
	if(_mesh)
	{
		SAFE_RELEASE(_mesh);
	}
	if(_pd3dDevice)
	{
		SAFE_RELEASE(_pd3dDevice);
	}
	_meshes.clear();
	_materials.clear();
	_textures.clear();
	_heights.clear();
//	SAFE_DELETE(_meshMaterials);
*/
}

/*
//-----------------------------------------------------------------------------
// Name: SetTexture()
// Desc: Load the Texture into memory if it doesnt already exist
//-----------------------------------------------------------------------------
LPD3DXMESH FrameWorkResourceManager::GetMesh(wstring name , bool loadTextures)
{
	// Convert wstring to LPCWSTR
	LPCWSTR filename = name.c_str();

	// If the name not found load the mesh, texture and material
	if (_meshes.count(name) == 0 && name.length() > 0 )
	{
		// Load the mesh from the specified file
		D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM,
			_pd3dDevice, NULL,
			&_materialBuffer,NULL, &_numMaterials,
			&_mesh );

		// Insert the mesh & it's name into MAP, KEY container
		_meshes.insert(pair<wstring, LPD3DXMESH>(filename, _mesh));

		// Extract the information stored in the mesh (.x)
		d3dxMaterials = (D3DXMATERIAL*)_materialBuffer->GetBufferPointer();

		_meshMaterials = &d3dxMaterials->MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		_meshMaterials->Ambient = _meshMaterials->Diffuse;

		_materials.insert(pair<wstring, D3DMATERIAL9*>(filename, _meshMaterials));
	}

	if (!loadTextures)
	{
		size_t len = 0;
		len = (int)strlen(d3dxMaterials->pTextureFilename) + 1;
		if (len > 0)
		{
			wchar_t *unicodeString = new wchar_t[len];
			mbstowcs_s(&len, unicodeString, len, d3dxMaterials->pTextureFilename, len);

			D3DXCreateTextureFromFile(_pd3dDevice, unicodeString, &_texture);

			// Insert the texture into MAP container
			_textures.insert(pair<wstring, LPDIRECT3DTEXTURE9>(filename, _texture));
		}
	}
	else
	{
		SetTexture(name);
	}
	return _mesh;
}
*/

//-----------------------------------------------------------------------------
// Name: SetTexture()
// Desc: Load the Texture into memory if it doesnt already exist
//-----------------------------------------------------------------------------
//void FrameWorkResourceManager::SetTexture(wstring name)
//{
////	_textureIterator = _textures.find(name);
//
////	if (_textureIterator == _textures.end())
//	{
//		// Convert wstring to LPCWSTR
//		LPCWSTR filename = name.c_str();
//
//
//
//
//		//D3DX11CreateShaderResourceViewFromFile(_device, filename, NULL,NULL, &_texture, NULL);
//
////		D3DXCreateTextureFromFile(_pd3dDevice, filename, &_texture);
////		_textures.insert(pair<wstring, ID3D11ShaderResourceView>(filename, _texture));
//	}
//}


//-----------------------------------------------------------------------------
// Name: GetTexture()
// Desc: Returns the Texture
//-----------------------------------------------------------------------------
//ID3D11ShaderResourceView* FrameWorkResourceManager::GetTexture(wstring name)
//{
//	// Search the container for the name
////	_textureIterator = _textures.find(name);
//
////	if (_textureIterator != _textures.end())
//	{
//		return _texture;
//	}
////	else
////	{
////		return 0;
////	}
//}

/*
//-----------------------------------------------------------------------------
// Name: GetMaterial()
// Desc: Returns the Material
//-----------------------------------------------------------------------------
D3DMATERIAL9* FrameWorkResourceManager::GetMaterial(wstring name)
{
	// Search the container for the name
	_materialsIterator = _materials.find(name);

	if (_materialsIterator != _materials.end())
	{
		return _meshMaterials;
	}
	else
	{
		return 0;
	}
}
*/
//-----------------------------------------------------------------------------
// Name: GetNumberOfMatrials()
// Desc: Returns the Number Of Materials
//-----------------------------------------------------------------------------
DWORD FrameWorkResourceManager::GetNumberOfMaterials(void)
{
	return 0;//_numMaterials;
}

/*
//-----------------------------------------------------------------------------
// Name: GetDefaultMaterial()
// Desc: Returns the default materiel
//-----------------------------------------------------------------------------
D3DMATERIAL9 FrameWorkResourceManager::GetDefaultMaterial(void)
{
	// Setup the material properties
	_material.Ambient.r = 0.5f;
	_material.Ambient.g = 0.5f;
	_material.Ambient.b = 0.5f;
	_material.Ambient.a = 1.0f;

	_material.Diffuse.r = 1.0f;
	_material.Diffuse.g = 1.0f;
	_material.Diffuse.b = 1.0f;
	_material.Diffuse.a = 1.0f;

	_material.Specular.r = 1.0f;
	_material.Specular.g = 1.0f;
	_material.Specular.b = 1.0f;
	_material.Specular.a = 1.0f;

	_material.Emissive.r = 0.0f;
	_material.Emissive.g = 0.0f;
	_material.Emissive.b = 0.0f;
	_material.Emissive.a = 1.0f;

	_material.Power = 100.0f;

	return _material;
}

//-----------------------------------------------------------------------------
// Name: GetDefaultMaterial()
// Desc: Returns the default black materiel
//-----------------------------------------------------------------------------
D3DMATERIAL9 FrameWorkResourceManager::GetDefaultBlackMaterial(void)
{
	// Setup the material properties
	_material.Ambient.r = 0.0f;
	_material.Ambient.g = 0.0f;
	_material.Ambient.b = 0.0f;
	_material.Ambient.a = 0.0f;

	_material.Diffuse.r = 0.0f;
	_material.Diffuse.g = 0.0f;
	_material.Diffuse.b = 0.0f;
	_material.Diffuse.a = 0.0f;

	_material.Specular.r = 1.0f;
	_material.Specular.g = 1.0f;
	_material.Specular.b = 1.0f;
	_material.Specular.a = 1.0f;

	_material.Emissive.r = 0.0f;
	_material.Emissive.g = 0.0f;
	_material.Emissive.b = 0.0f;
	_material.Emissive.a = 1.0f;

	_material.Power = 100.0f;

	return 	_material;
}
*/

//-----------------------------------------------------------------------------
// Name: LoadHeightMap()
// Desc: Load the LoadHeightMap into memory 
//-----------------------------------------------------------------------------
vector<float> FrameWorkResourceManager::LoadHeightMap(wstring filename, DWORD gridSize)
{ 
	vector<BYTE> in(gridSize * gridSize); 

	std::ifstream inFile(filename.c_str(), std::ios_base::binary); 
	if (!inFile)// == (std::ifstream)NULL)
	{
		return _heights; 
	}

	inFile.read((char*)&in[0], in.size());
	inFile.close(); 

	// Normalise BYTE values to the range 0.0f - 1.0f;
	_heights.resize(in.size()); 
	for(unsigned int i = 0; i < in.size(); i++) 
	{
		_heights[i] = (float)in[i] / 255; 
	}
	return _heights; 
} 

//int FrameWorkResourceManager::LoadAsset(const char* filename)
//const aiScene* FrameWorkResourceManager::LoadAsset(const char* filename)
aiScene* FrameWorkResourceManager::LoadAsset(const char* filename)
{
	/* we are taking one of the postprocessing presets to avoid
	spelling out 20+ single postprocessing flags here. */
	//scene = aiImportFile(filename, aiProcessPreset_TargetRealtime_MaxQuality);

	//https://github.com/assimp/assimp/blob/master/samples/SimpleTexturedDirectx11/SimpleTexturedDirectx11/ModelLoader.cpp
	Assimp::Importer importer;

	//const aiScene* pScene = importer.ReadFile(filename,	aiProcess_Triangulate |	aiProcess_ConvertToLeftHanded);
	pScene = (aiScene*) (importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded));


	//for (UINT i = 0; i < pScene->mRootNode->mNumMeshes; i++)
	//{
	//	aiMesh* mesh = pScene->mMeshes[pScene->mRootNode->mMeshes[i]];
	//	meshes.push_back(this->processMesh(mesh, pScene));
	//}
	//for (UINT i = 0; i < node->mNumChildren; i++)
	//{
	//	this->ProcessNode(node->mChildren[i], scene);
	//}

	this->ProcessNode(pScene->mRootNode, pScene);

	//return importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	return NULL;// pScene;
}

//https://github.com/assimp/assimp/tree/master/samples/SimpleTexturedDirectx11/SimpleTexturedDirectx11

string textype;



void FrameWorkResourceManager::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(this->ProcessMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

Mesh FrameWorkResourceManager::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	// Data to fill
	vector<VERTEX1> vertices;
	vector<UINT> indices;
	vector<Texture> textures;

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

		if (textype.empty()) textype = determineTextureType(scene, mat);
	}

	// Walk through each of the mesh's vertices
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		VERTEX1 vertex;

		vertex.X = mesh->mVertices[i].x;
		vertex.Y = mesh->mVertices[i].y;
		vertex.Z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.texcoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.texcoord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	}

	return Mesh(_device, vertices, indices, textures);
}

vector<Texture> FrameWorkResourceManager::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName, const aiScene * scene)
{
	vector<Texture> textures;
	for (UINT i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (UINT j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			HRESULT hr;
			Texture texture;
			if (textype == "embedded compressed texture")
			{
				int textureindex = getTextureIndex(&str);
				texture.texture = getTextureFromModel(scene, textureindex);
			}
			else
			{
				string filename = string(str.C_Str());
				filename = directory + '/' + filename;
				wstring filenamews = wstring(filename.begin(), filename.end());
				hr = CreateWICTextureFromFile(_device, devcon, filenamews.c_str(), nullptr, &texture.texture);
				if (FAILED(hr))
					MessageBox(hwnd, L"Texture couldn't be loaded", L"Error!", MB_ICONERROR | MB_OK);
			}
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

//void FrameWorkResourceManager::Close()
//{
//	for (int i = 0; i < meshes.size(); i++)
//	{
//		meshes[i].Close();
//	}
//
//	dev->Release();
//}

//void FrameWorkResourceManager::processNode(aiNode * node, const aiScene * scene)
//{
//	for (UINT i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		meshes.push_back(this->processMesh(mesh, scene));
//	}
//
//	for (UINT i = 0; i < node->mNumChildren; i++)
//	{
//		this->processNode(node->mChildren[i], scene);
//	}
//}

string FrameWorkResourceManager::determineTextureType(const aiScene * scene, aiMaterial * mat)
{
	aiString textypeStr;
	mat->GetTexture(aiTextureType_DIFFUSE, 0, &textypeStr);
	string textypeteststr = textypeStr.C_Str();
	if (textypeteststr == "*0" || textypeteststr == "*1" || textypeteststr == "*2" || textypeteststr == "*3" || textypeteststr == "*4" || textypeteststr == "*5")
	{
		if (scene->mTextures[0]->mHeight == 0)
		{
			return "embedded compressed texture";
		}
		else
		{
			return "embedded non-compressed texture";
		}
	}
	if (textypeteststr.find('.') != string::npos)
	{
		return "textures are on disk";
	}
}


int FrameWorkResourceManager::getTextureIndex(aiString * str)
{
	string tistr;
	tistr = str->C_Str();
	tistr = tistr.substr(1);
	return stoi(tistr);
}

ID3D11ShaderResourceView * FrameWorkResourceManager::getTextureFromModel(const aiScene * scene, int textureindex)
{
	HRESULT hr;
	ID3D11ShaderResourceView *texture;

	int* size = reinterpret_cast<int*>(&scene->mTextures[textureindex]->mWidth);

	hr = CreateWICTextureFromMemory(_device, devcon, reinterpret_cast<unsigned char*>(scene->mTextures[textureindex]->pcData), *size, nullptr, &texture);
	if (FAILED(hr))
		MessageBox(hwnd, L"Texture couldn't be created from memory!", L"Error!", MB_ICONERROR | MB_OK);

	return texture;
}