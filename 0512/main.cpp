//=================================================
//
//	main.cpp
// 
// Author:近田尚也
//
//=================================================

#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "manager.h"
#include <crtdbg.h>

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//グローバル変数宣言
bool g_isFullscreen = false;				//	ウィンドウを切り替えるためのフラグ
RECT g_windowRect;
int g_nCountFPS = 0;

//===========================
//メイン関数
//===========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//追加する(SAL:ソースコード注釈言語)
{
	// メモリリーク検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//メモリリーク検知

#if 0
	// メモリリークの場所検知
	_CrtSetBreakAlloc(187);
#endif

	DWORD dwCurrentTime;
	DWORD dwExeclastTime;
	DWORD dwFrameCount;	//フレームカウント
	DWORD dwFPSLastTime;	//最後にFPSを計測した時刻
	CManager* pManager = NULL;
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;//ウィンドウハンドル(識別子)
	MSG msg;//メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);
	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//ウィンドウ生成
	hWnd = CreateWindowEx(0,//拡張ウィンドウスタイル
		CLASS_NAME,//ウィンドウクラスの名前
		WINDOW_NAME,//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,//ウィンドウスタイル
		CW_USEDEFAULT,//ウィンドウの左上X座標
		CW_USEDEFAULT,//ウィンドウの左上Y座標
		(rect.right - rect.left),//ウィンドウの幅
		(rect.bottom - rect.top),//ウィンドウの高さ
		NULL,//親ウィンドウのハンドル
		NULL,//メニューハンドルまたは子ウィンドウID
		hInstance,//インスタンスハンドル
		NULL);//ウィンドウ作成データ

	pManager = new CManager;

	//====================
	//初期化処理
	//====================
	if (FAILED(pManager->Init(hInstance,hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return - 1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExeclastTime = timeGetTime();
	
	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//FPSを計測した時刻を表保存
				dwFrameCount = 0;	//フレームカウントをクリア
			}
			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))
			{
				dwExeclastTime = dwCurrentTime;

				//====================
				//レンダラー更新処理
				//====================
				pManager->Update();

				//====================
				//レンダラー描画処理
				//====================
				pManager->Draw();

				dwFrameCount++;		//フレームカウントを加算
			}
		}
	}

	//破棄の処理
	

	//破棄の処理
	if (pManager != NULL)
	{
		//====================
		//レンダラー終了処理
		//====================
		pManager->Uninit();

		delete pManager;
		pManager = NULL;
	}
	
	timeEndPeriod(1);
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}
//************************************************
// ウィンドウをフルスクリーンに変える処理
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	//==================================
	//	現在のウィンドウスタイルを取得
	//==================================
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	if (g_isFullscreen)
	{
		//=============================
		//	ウィンドウモードに切り替え
		//=============================
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		//==================================
		//	フルスクリーンモードに切り替え
		//==================================
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}
	g_isFullscreen = !g_isFullscreen;
}

//=================================
//ウィンドウプロシージャ
//=================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
			//ウィンドウを破棄する
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
			//ウィンドウを拡大
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	case WM_CREATE:
		//タイマーの設定
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//既定の処理を返す
}

// FPSのカウントを取得
int GetFPS(void)
{
	return g_nCountFPS;
}