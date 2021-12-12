// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include <iostream>
#include <stdio.h>
#include "Class/FBXLoader/FbxLoader.h"

using namespace std;

int main(void)
{
	//string filePath = "Model/syak/Shachiku_chan_Ver2.0.fbx";
	string filePath = "Model/mori_model_03.fbx";
	FbxLoader fbx;
	//cin >> filePath;
	fbx.Init(filePath.c_str());
	SML d = fbx.GetData();
	auto num = d.numVertex;
	FILE* a;
	auto hr = fopen_s(&a,"mori.sml", "wb");
	fwrite(&d.numVertex, 4, 1, a);

	for (auto i : d.Vertices)
	{
		fwrite(&i, sizeof(SML::SVertex),1, a);
	}

	fwrite(&d.numVertex, 4, 1, a);

	for(auto i : d.Indeces)
		fwrite(&i, 4, 1, a);


	return 0;
}


