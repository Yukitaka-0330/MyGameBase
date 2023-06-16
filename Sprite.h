#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include <vector>
#include"Texture.h"

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //開放処理


using namespace DirectX;
class Sprite
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

protected:
	UINT64 vertexNum_; //頂点数
	std::vector<VERTEX> vertices_; //頂点情報
	ID3D11Buffer* pVertexBuffer_; //頂点バッファ

	UINT64 indexNum; //インデックス数
	std::vector<int> index_; //インデックス情報

	Texture* pTexture_; //テクスチャ

public:
	Sprite();
	~Sprite();

	//初期化(ポリゴンを表示するため各種情報を準備)
	//戻り値 成功/失敗
	HRESULT Initialize();

	//描画
	//引数:worldMatrix ワールド行列
	void Draw(XMMATRIX& worldMatrix);

	//開放
	void Release();

private:

	//Initializeから呼ばれる関数
	virtual void InitVertexData(); //頂点情報を準備
	HRESULT  CreateVertexBuffer(); //頂点バッファを作成

	virtual void InitIndexData(); //インデックス情報を準備
	HRESULT CreateIndexBuffer(); //インデックスバッファを作成

	HRESULT CreateConstantBuffer(); //コンスタントバッファを作成

	HRESULT LoadTexture(); //テクスチャをロード

	//Drawから呼ばれる関数
	void PassDataToCB(DirectX::XMMATRIX& worldMatrix); //コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline(); //各バッファをパイプラインにセット

};

