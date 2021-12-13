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
	void LoadMesh(FbxMesh*);
	void LoadMaterial(FbxSurfaceMaterial* ,int);
	void LoadLambert(FbxSurfaceLambert*);
	void LoadPhong(FbxSurfacePhong* , int);
	void LoadBorn(FbxMesh*);
	void LoadCluster(FbxCluster*,int);

	FbxManager*		m_manager;
	FbxImporter*	m_importer;
	FbxScene*		m_scene;

	SML m_sml;
};