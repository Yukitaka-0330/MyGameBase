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
	//XMVECTOR GetMousePosition();
	//void SetMousePosition(int x, int y);
	void Release();

	bool IsMouseButton(int buttonCode);//�}�E�X�̃{�^����������Ă��邩���ׂ�
	bool IsMouseButtonDown(int buttonCode);//�}�E�X�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	bool IsMouseButtonUp(int buttonCode);//�}�E�X�̃{�^�����������������ׂ�
	XMFLOAT3 F3GetMousePosition();//�}�E�X�J�[�\���̈ʒu���擾
	void XSetMousePosition(int x, int y);//�}�E�X�J�[�\���̈ʒu���Z�b�g
	XMFLOAT3 GetMouseMove();//���̃t���[���ł̃}�E�X�̈ړ��ʂ��擾


};

