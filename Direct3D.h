#pragma once

//インクルード
#include <d3d11.h>
//リンカ
#pragma comment(lib, "d3d11.lib")


namespace Direct3D

{
	//初期化

	//winW ウィンドウ幅 winH ウィンドウ高さ
	void Initialize(int winW, int winH, HWND hWnd);



	//描画開始
	void BeginDraw();



	//描画終了
	void EndDraw();



	//解放
	void Release();

};
