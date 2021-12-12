#include <iostream>
#include <DirectXMath.h>

#include "FbxLoader.h";

#pragma comment(lib,"libfbxsdk-md.lib")
#pragma comment(lib,"libxml2-md.lib")
#pragma comment(lib,"zlib-md.lib")

#include <vector>

FbxLoader::FbxLoader()
{
}

void FbxLoader::Init(const char* filePath)
{
	m_manager = FbxManager::Create();
	m_importer = FbxImporter::Create(m_manager, "");
	m_scene = FbxScene::Create(m_manager, "");

	m_importer->Initialize(filePath);
	m_importer->Import(m_scene);

	FbxNode* node = m_scene->GetRootNode();
	FbxGeometryConverter converter(m_manager);
	converter.Triangulate(m_scene, true);

	std::vector<FbxNode*> node_list;

	CollectMeshNode(node, node_list);

	for (auto a : node_list)
	{
		CreateMesh(a->GetMesh());
	}


	return;
}

void FbxLoader::Release()
{
	m_manager->Destroy();
	m_importer->Destroy();
	m_scene->Destroy();
}

void FbxLoader::CollectMeshNode(FbxNode* node, std::vector<FbxNode*>& list)
{
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	{
		FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);
		if (attribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
		{
			list.push_back(node);
			break;
		}
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		CollectMeshNode(node->GetChild(i), list);
	}
}

void FbxLoader::CreateMesh(FbxMesh* mesh)
{
	FbxVector4* vertices = mesh->GetControlPoints();

	int* indices = mesh->GetPolygonVertices();

	int numVertex = mesh->GetPolygonVertexCount();
	m_sml.numVertex += numVertex;

	for (int i = 0; i < numVertex; i++)
	{
		SML::SVertex vertex;
		int index = indices[i];

		vertex.pos.x = (float)-vertices[index][0];
		vertex.pos.y = (float)vertices[index][1];
		vertex.pos.z = (float)vertices[index][2];

		m_sml.Vertices.push_back(vertex);
	}

	FbxArray<FbxVector4> normals;

	mesh->GetPolygonVertexNormals(normals);
	auto c = normals.Size();

	for (int i = 0; i < normals.Size(); i++)
	{
		m_sml.Vertices[i].normal.x = (float)-normals[i][0];
		m_sml.Vertices[i].normal.y = (float)normals[i][1];
		m_sml.Vertices[i].normal.z = (float)normals[i][2];
	}

	int numPolygon = mesh->GetPolygonCount();

	for (int i = 0; i < numPolygon; i++)
	{
		m_sml.Indeces.push_back(i * 3 + 2);
		m_sml.Indeces.push_back(i * 3 + 1);
		m_sml.Indeces.push_back(i * 3);
	}

	FbxStringList uvset_name;

	mesh->GetUVSetNames(uvset_name);
	FbxArray<FbxVector2> uv;

	mesh->GetPolygonVertexUVs(uvset_name.GetStringAt(0), uv);

	for (int i = 0; i < numVertex; i++)
	{
		m_sml.Vertices[i].uv.x = uv[i][0];
		m_sml.Vertices[i].uv.y = uv[i][1];
	}

	auto manode = mesh->GetNode();
	auto numMaterial = manode->GetMaterialCount();
	for (int i = 0; i < numMaterial; i++)
	{
		CreateMaterial(manode->GetMaterial(i),i);
	}

}

void FbxLoader::CreateMaterial(FbxSurfaceMaterial* material, int index)
{
	if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
	{
		auto lambert = (FbxSurfaceLambert*)material;
		CreateLambert(lambert);
	}
	else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
	{
		auto phong = (FbxSurfacePhong*)material;
		CreatePhong(phong,index);
	}
}

void FbxLoader::CreateLambert(FbxSurfaceLambert* material)
{
	SML::MaterialLambert lambert;
	lambert.ambient.x = (float)material->Ambient.Get()[0];
	lambert.ambient.y = (float)material->Ambient.Get()[0];
	lambert.ambient.z = (float)material->Ambient.Get()[0];
	lambert.ambient.w = (float)material->AmbientFactor;

	lambert.diffuse.x = (float)material->Diffuse.Get()[0];
	lambert.diffuse.y = (float)material->Diffuse.Get()[1];
	lambert.diffuse.z = (float)material->Diffuse.Get()[2];
	lambert.diffuse.x = (float)material->DiffuseFactor;

	lambert.emissive.x = (float)material->Emissive.Get()[0];
	lambert.emissive.y = (float)material->Emissive.Get()[1];
	lambert.emissive.z = (float)material->Emissive.Get()[2];
	lambert.emissive.x = (float)material->EmissiveFactor;

	m_sml.lambert.push_back(lambert);
}

void FbxLoader::CreatePhong(FbxSurfacePhong* material, int index)
{
	m_sml.lambert[index].specular.x = (float)material->Specular.Get()[0];
	m_sml.lambert[index].specular.y = (float)material->Specular.Get()[1];
	m_sml.lambert[index].specular.z = (float)material->Specular.Get()[2];
	m_sml.lambert[index].specular.w = (float)material->SpecularFactor;
}
