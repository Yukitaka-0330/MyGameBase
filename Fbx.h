#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

//#pragma commentÇÃÇ∆Ç±ÇÎ MT -> MDÇ©MdÇÃÇ«Ç¡ÇøÇ©Ç…íºÇ∑ Ç«Ç¡ÇøÇ≈Ç‡Ç¢Ç¢Ç¡Ç€Ç¢

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMFLOAT3 position;
	};

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

	int vertexCount_;	//í∏ì_êî
	int polygonCount_;	//É|ÉäÉSÉìêî

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
};



