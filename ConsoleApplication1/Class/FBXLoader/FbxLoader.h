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

	void CollectMeshNode(FbxNode*, std::vector<FbxNode*>&);
	void CreateMesh(FbxMesh*);

	SML GetData() { return m_sml; }
private:

	FbxManager*		m_manager;
	FbxImporter*	m_importer;
	FbxScene*		m_scene;

	SML m_sml;
};