/*---------------------------------------------------------

	[Application.cpp]
	Author : 出合翔太

----------------------------------------------------------*/
#include "Application.h"
#include "InputDevice.h"
#include "Manager.h"
#include "Fps.h"
#include "Input.h"

// ウィンドウサイズ
namespace
{
	const float s_WindowWidth = 1920;
	const float s_WindowHeight = 1080;
}

#pragma region Application_Func
// ウィンドウプロシージャ
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Application::CreateGameWindow(HWND & hwnd, WNDCLASSEX & windowClass)
{
	if (m_WindowMode == true)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		// ウィンドウの生成＆登録
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.lpfnWndProc = (WNDPROC)WndProc; // コールバック関数の指定
		windowClass.lpszClassName = "Dx11";			// アプリケーション名
		windowClass.hInstance = GetModuleHandle(0);	// ハンドルの指定
		RegisterClassEx(&windowClass);				// アプリケーションクラス
		RECT wrc = { 0,0,s_WindowWidth, s_WindowHeight };
		AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
		// ウィンドウオブジェクトの生成
		hwnd = CreateWindow(windowClass.lpszClassName,	// クラス名
			"ゲームアプリ",								// タイトルバー
			WS_OVERLAPPEDWINDOW,						// ウィンドウタイプ
			CW_USEDEFAULT, CW_USEDEFAULT,				// 表示xy座標はOSに任せる
			wrc.right - wrc.left, wrc.bottom - wrc.top, // ウィンドウ幅と高さ
			NULL, NULL, windowClass.hInstance, NULL);	// ウィンドウハンドル, メニューハンドル,呼び出しアプリケーションハンドル, 追加パラメータ
	}
	else if (m_WindowMode == false)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		// ウィンドウの生成＆登録
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.lpfnWndProc = (WNDPROC)WndProc; // コールバック関数の指定
		windowClass.lpszClassName = "Dx11";			// アプリケーション名
		windowClass.hInstance = GetModuleHandle(0);	// ハンドルの指定
		RegisterClassEx(&windowClass);				// アプリケーションクラス
		RECT wrc = { 0,0,s_WindowWidth, s_WindowHeight };
		AdjustWindowRect(&wrc, WS_CAPTION, false);
		// ウィンドウオブジェクトの生成
		hwnd = CreateWindow(windowClass.lpszClassName,	// クラス名
			"ゲームアプリ",								// タイトルバー
			WS_VISIBLE | WS_POPUP,						// ウィンドウタイプ
			CW_USEDEFAULT, CW_USEDEFAULT,				// 表示xy座標はOSに任せる
			wrc.right - wrc.left, wrc.bottom - wrc.top, // ウィンドウ幅と高さ
			NULL, NULL, windowClass.hInstance, NULL);	// ウィンドウハンドル, メニューハンドル,呼び出しアプリケーションハンドル, 追加パラメータ
	}
}

Application & Application::Instance()
{
	static Application instance;
	return instance;
}

void Application::Init(HINSTANCE hInstance)
{
	auto result = CoInitializeEx(0, COINITBASE_MULTITHREADED);
	//DxLib_Init();
	CreateGameWindow(m_hwnd, m_WindowClass); // ゲームウィンドウ
	InputDevice::Init(hInstance, m_hwnd);	 // コントローラの初期化
	
}

void Application::AppRun()
{
	// ウィンドウ表示
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);
	
	// フレームレートの初期化
	Fps& fps = Fps::Instance();
	fps.Init();
	Manager::Init();

	// メッセージループ
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) // PostQuitMessage()が呼ばれたらループ終了
			{
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if(fps.Update())
			{
				InputDevice::Update(); // コントローラの更新
				Manager::Update();
				// 描画処理
				Manager::Draw();
			}
		}
	}

	
	Manager::Uninit();
	fps.Uninit();
	InputDevice::Uninit();  // コントローラの終了処理 
	timeEndPeriod(1);		// 分解能を戻す
	//DxLib_End();
	UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance); // ウィンドウクラスの登録を解除
}

SIZE Application::GetWindowSize() const
{
	SIZE ret;
	ret.cx = s_WindowWidth;
	ret.cy = s_WindowHeight;
	return ret;
}

HWND Application::Gethwnd() const
{
	return m_hwnd;
}
#pragma endregion Applicationクラスの関数