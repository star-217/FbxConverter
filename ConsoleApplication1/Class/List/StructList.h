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
	};

	int numVertex;

	std::vector<SVertex> Vertices;
	std::vector<int>	 Indeces;
};