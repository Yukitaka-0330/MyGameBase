#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"


#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

//#pragma commentのところ MT -> MDかMdのどっちかに直す どっちでもいいっぽい
//ヘッダーでヘッダーをインクルードするのはあんまりよろしくない

class Texture; //前方宣言　cppでヘッダーをインクルードすればよい

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};
	struct VERTEX
	{
		XMVECTOR position;
	};
	struct MATERIAL //マテリアル
	{
		Texture* pTexture;
	};

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();

	//Drawから呼ばれる関数
	void PassDataToCB(Transform transform);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();

	void InitMaterial(fbxsdk::FbxNode* pNode);

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

	
};



