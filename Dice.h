#if 0
#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matW;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Dice
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;
public:
	/// <summary>
	/// 四角形を表すクラスのコンストラクタ
	/// </summary>
	Dice();

	~Dice();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};
#endif


//#if 0
#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include <vector>
#include"Texture.h"

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //開放処理


using namespace DirectX;
using std::vector;
class Dice
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matW;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	HRESULT hr;

protected:
	UINT64  vertexNum_; //頂点数
	vector<VERTEX> vertices_; //頂点情報
	ID3D11Buffer* pVertexBuffer_; //頂点バッファ

	UINT64 indexNum_; //インデックス数
	vector<int> index_; //インデックス情報

	Texture* pTexture_; //テクスチャ

	//もとはないやつ
	ID3D11Buffer* pIndexBuffer_; //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

public:
	Dice();
	~Dice();

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

//#endif


