#pragma once

//�C���N���[�h
#include <d3d11.h>
//�����J
#pragma comment(lib, "d3d11.lib")


namespace Direct3D

{
	//������

	//winW �E�B���h�E�� winH �E�B���h�E����
	void Initialize(int winW, int winH, HWND hWnd);



	//�`��J�n
	void BeginDraw();



	//�`��I��
	void EndDraw();



	//���
	void Release();

};
