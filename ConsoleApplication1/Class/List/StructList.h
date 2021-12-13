#include <iostream>
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

struct SML
{
	struct SVertex
	{
		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 uv = XMFLOAT2(0,0);
		float weight[4] = {};
	};


	struct MaterialLambert
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 emissive;
		XMFLOAT4 specular;
	};

	struct MaterialEtc
	{
		XMFLOAT3 bump;
		float transparency;
		float shininess;
		float reflect;
	};

	int numVertex;

	std::vector<SVertex> Vertices;
	std::vector<int>	 Indeces;
	std::vector<MaterialLambert> lambert;
	std::vector<MaterialEtc> materialetc;
	std::vector<const char*> textureName;
};