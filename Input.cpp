#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr; //�L�[�{�[�h�̂𓮂������߂̕ϐ��B
	BYTE keyState[256] = { 0 };

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr); 
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr); //�f�o�C�X�I�u�W�F�N�g���쐬
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard); //�f�o�C�X�̎�ނ�ݒ�
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);//�������x���̐ݒ�����Ă���
	}

	void Update()
	{
		pKeyDevice->Acquire();//����͕K�������Ȃ��ƃ_���I
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState); //�L�[�̏�Ԃ��킩��
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

