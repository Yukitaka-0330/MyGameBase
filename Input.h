#pragma once
#include <dInput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND hWnd);
	void Update();
	bool IsKey(int keyCode); //������Ă��鎞
	bool IsKeyDown(int keyCode); //�����ꂽ�u��
	bool IsKeyUp(int keyCode); //�������u��
	void Release();
};

