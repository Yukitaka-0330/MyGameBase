#include "Dice.h"
#include "Camera.h"

Dice::Dice() :pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr)
{
}

Dice::~Dice()
{
	Release();
}

HRESULT Dice::Initialize()
{
	HRESULT hr;
	// 頂点情報
	VERTEX vertices[] =
	{

		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（左上）,テクスチャの座標(画鋲をイメージすればいいかも、ここに春よーみたいな感じ)0
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（右上）,テクスチャの座標 1
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },	// 四角形の頂点（右下）,テクスチャの座標 2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// 四角形の頂点（左下）,テクスチャの座標 3

		{XMVectorSet(1.0f ,1.0f ,2.0f ,0.0f),},//四角形の頂点（右奥上）,テクスチャの座標 4 z軸+で奥
		{XMVectorSet(1.0f ,-1.0f ,2.0f ,0.0f),},//四角形の頂点（右奥下）,テクスチャの座標 5 z軸+で奥
		{XMVectorSet(-1.0f ,1.0f ,2.0f ,0.0f),},//四角形の頂点（左奥上）,テクスチャの座標 6 z軸+で奥
		{XMVectorSet(-1.0f ,-1.0f ,2.0f ,0.0f),}//四角形の頂点（左奥下）,テクスチャの座標 7 z軸+で奥


	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);  //ByteWidthがバッファーのサイズ
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;	 //バッファーの読み取りと書き込み方法を特定
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//バッファーをパイプラインに結びつける
	bd_vertex.CPUAccessFlags = 0;	//CPUアクセスが必要ない場合は0
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;

	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
		//return E_FAIL;
	}


	//インデックス情報
	int index[] = { 0,2,3, 0,1,2, //前面
					1,5,2, 1,4,5, //右面
				    0,7,3, 0,6,7  //左面
					};

	//int index[] = { 0,2,3, 0,1,2, 0,4,1};



	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);

	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;

	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");

	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	//コンスタントバッファに渡す情報
	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列 //カメラから見ての拡張するためのもの  //XMVectorSetはカメラの上方向
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列 //遠近感をつける //第一引数　画角、視野角をラジアンで表現している
	//第二引数 アスペクト比 第三引数　ニアクリップ面　第四引数 ファークリップ面
	//カメラ内に収めるならx軸が -1から1 y軸が-1から1 z軸が-1から1
	//視野角を狭くするとズームすることになる　遠くのものと近くのものの差が変わらなくなる　遠近感がなくなる
	/*カメラの表示距離は近い時も遠い時も決めないといけない
	遠い時に設定しないとどこまでも見えてしまうため
	近い時はある程度カメラとの距離がないと距離を圧縮して表示できなくなるから*/
	//ニアクリップ面とファークリップ面の距離はなるべく短くする　なぜか距離のずれが生じる　物体が埋まっちゃ足りしてちらつくようになる　<- zファイティング

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	//cb.matWVP = XMMatrixTranspose(view * proj);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);


	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	//UINT stride = sizeof(XMVECTOR); //前使ってたやつ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	//Direct3D::pContext_->DrawIndexed(9, 0, 0);
	Direct3D::pContext_->DrawIndexed(18, 0, 0);
}

void Dice::Release()
{
	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
