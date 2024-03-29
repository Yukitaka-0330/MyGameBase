#pragma once
#include <d3d11.h>
#include <assert.h> //これはC言語のヘッダファイル
#include <vector>
//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //開放処理
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;} //開放処理
#define SAFE_DELETE_ARRAY(p)if(p != nullptr){ delete[] p; p = nullptr;} //配列の解放処理

enum SHADER_TYPE
{
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX,
};

namespace Direct3D
{
	extern ID3D11Device* pDevice_;
	extern ID3D11DeviceContext* pContext_;		//デバイスコンテキスト
	extern int scrWidth, scrHeight;

	//初期化
	//winW ウィンドウ幅 winH ウィンドウ高さ
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//シェーダー準備
	HRESULT InitShader();
	HRESULT InitShader2D();
	HRESULT InitShader3D();
	void SetShader(SHADER_TYPE type);

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();

};
