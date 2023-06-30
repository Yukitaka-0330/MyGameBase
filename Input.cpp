#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr; //キーボードのを動かすための変数。
	BYTE keyState[256] = { 0 };

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr); 
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr); //デバイスオブジェクトを作成
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard); //デバイスの種類を設定
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);//強調レベルの設定をしている
	}

	void Update()
	{
		pKeyDevice->Acquire();//これは必ず書かないとダメ！
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState); //キーの状態がわかる
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 128)
		{
			return true;
		}
		return false;
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
		SAFE_RELEASE(pKeyDevice);
	}
}

