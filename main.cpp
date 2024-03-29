//インクルード
#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/RootJob.h"
#include "Engine/Model.h"

#include "resource.h"
#include "Stage.h"

#pragma comment(lib, "winmm.lib")

using std::string;
using std::to_string;
using std::cout;
using std::cin;
using std::endl;


//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

RootJob* pRootJob = nullptr;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);



//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//XMVECTOR beginP = XMVectorSet(1, 5, 1, 0);
	//XMVECTOR dirvec = XMVectorSet(0, -1, 0, 0);
	//XMVECTOR P1 = XMVectorSet(0, 0, 0, 0);
	//XMVECTOR P2 = XMVectorSet(0, 0, 3, 0);
	//XMVECTOR P3 = XMVectorSet(3, 0, 0, 0);
	//float dist; //距離
	//bool result = TriangleTests::Intersects(beginP, dirvec, P1, P2, P3, dist);
	//int a;

	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		"サンプルゲーム",     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,               //ウィンドウ幅
		winH,               //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	//Direct3D初期化
	HRESULT hr;
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		PostQuitMessage(0); //エラー起きたら強制終了
	}
	////////////// RayCast テストコード //////////////
	//Fbx* pFbx = new Fbx;
	//pFbx->Load("Assets/BoxDefault.fbx");
	//RayCastData ray{};
	//ray.start = { 0,10,0,0 };
	////ray.start = XMFLOAT4(0, 10, 0, 0);
	//ray.dir = { 0,-1,0,0 };
	//pFbx->RayCast(ray);
	/////////////////////////////////////////////////

	//カメラの初期化
	Camera::Initialize();

	//DirectInputの初期化
	Input::Initialize(hWnd);

	pRootJob = new RootJob(nullptr);
	pRootJob->Initialize();


	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DialogProc);



	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			timeBeginPeriod(1);

			static DWORD countFps = 0;
			static DWORD startTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;


			if (nowTime - startTime >= 1000) //if文は処理が遅い　重くなる
			{
				char str[16];
				wsprintf(str, "%u", countFps);
				SetWindowText(hWnd, str);

				countFps = 0;
				startTime = nowTime;
			}

			if ((nowTime - lastUpdateTime) * 60 <= 1000) //理屈的には誤差は少なくなる。 1000 /60 だと割り切れないよね
			{
				continue;
			}
			lastUpdateTime = nowTime;
			countFps++;

			

			timeEndPeriod(1);

			//▼ゲームの処理
			//カメラの更新
			Camera::Update();

			//入力の処理
			Input::Update();
			pRootJob->UpdateSub();

			//▼描画
			Direct3D::BeginDraw();

			//ルートジョブから、すべてのオブジェクトのドローを呼ぶ
			pRootJob->DrawSub();
			Direct3D::EndDraw();
		}
	}
	
	Model::Release();
	pRootJob->ReleaseSub();
	Input::Release();
	Direct3D::Release();

	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//ウィンドウを閉じた
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;

		//マウスが動いた
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_COMMAND:
		switch ((wParam))
		{
		case ID_MENU_NEW:
			OutputDebugString("New File");
			break;

		case ID_MENU_OPEN:
			((Stage*)pRootJob->FindObject("Stage"))->Load();
			break;

		case ID_MENU_SAVE:
			((Stage*)pRootJob->FindObject("Stage"))->Save();
			//ファイル保存ダイアログで名前を決める
			//決めたファイル名でセーブを実行
			return 0;
		}
	
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//本物のダイアログプロシージャ
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Stage* pStage = (Stage*)pRootJob->FindObject("Stage");
	return pStage->DialogProc(hDlg, msg, wParam, lParam);
	//((Stage*)pRootJob->FindObject("Stage"))->DialogProc(hDlg, msg, wParam, lParam); //1行var
}