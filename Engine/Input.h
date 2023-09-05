#pragma once
#include <dInput.h>
#include <DirectXMath.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

using namespace DirectX;

namespace Input
{
	void Initialize(HWND hWnd);
	void Update();
	bool IsKey(int keyCode); //押されている時
	bool IsKeyDown(int keyCode); //押された瞬間
	bool IsKeyUp(int keyCode); //離した瞬間
	//XMVECTOR GetMousePosition();
	//void SetMousePosition(int x, int y);
	void Release();

	bool IsMouseButton(int buttonCode);//マウスのボタンが押されているか調べる
	bool IsMouseButtonDown(int buttonCode);//マウスのボタンを今押したか調べる（押しっぱなしは無効）
	bool IsMouseButtonUp(int buttonCode);//マウスのボタンを今放したか調べる
	XMFLOAT3 F3GetMousePosition();//マウスカーソルの位置を取得
	void XSetMousePosition(int x, int y);//マウスカーソルの位置をセット
	XMFLOAT3 GetMouseMove();//そのフレームでのマウスの移動量を取得


};

