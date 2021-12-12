#pragma once

#include "../List/StructList.h"
#include <fbxsdk.h>

using namespace DirectX;

class FbxLoader
{
public:
	FbxLoader();
	~FbxLoader() {};

	void Init(const char* filePath);
	void Release();

	SML GetData() { return m_sml; }
private:

	void CollectMeshNode(FbxNode*, std::vector<FbxNode*>&);
	void CreateMesh(FbxMesh*);
	void CreateMaterial(FbxSurfaceMaterial* ,int);
	void CreateLambert(FbxSurfaceLambert*);
	void CreatePhong(FbxSurfacePhong* , int);


	FbxManager*		m_manager;
	FbxImporter*	m_importer;
	FbxScene*		m_scene;

	SML m_sml;
};