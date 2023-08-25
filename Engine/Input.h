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
	bool IsKey(int keyCode); //������Ă��鎞
	bool IsKeyDown(int keyCode); //�����ꂽ�u��
	bool IsKeyUp(int keyCode); //�������u��
	XMVECTOR GetMousePosition();
	void SetMousePosition(int x, int y);
	void Release();
};
