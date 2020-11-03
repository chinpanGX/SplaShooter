/*---------------------------------------------------------

	[Application.cpp]
	Author : 出合翔太

----------------------------------------------------------*/
#include "Application.h"
#include "InputDevice.h"

#pragma region Fps_Func
Fps & Fps::Instance()
{
	static Fps instance;
	return instance;
}

void Fps::Init()
{
	timeBeginPeriod(1);
	m_dwExcLastTime = timeGetTime();
}

void Fps::Uninit()
{
	timeEndPeriod(1);
}

bool Fps::Update()
{
	m_dwOldCurrentTime = m_dwCurrentTime;
	m_dwCurrentTime = timeGetTime();
	if (m_dwCurrentTime - m_dwExcLastTime >= (1000 / m_Framerate))
	{
		m_deltaTime = (m_dwCurrentTime - m_dwExcLastTime) / 1000.0f;
		if (m_deltaTime >= 1 / m_Framerate)
		{
			m_deltaTime = 1 / m_Framerate;
		}
		if (m_isReset == true)
		{
			m_deltaTime = 0;
			m_isReset = false;
		}
		m_dwExcLastTime = m_dwCurrentTime;
		return true;
	}
	else
	{
		return false;
	}
}

void Fps::Reset()
{
	m_isReset = true;
}
#pragma endregion Fpsクラスの関数

#pragma region Application_Func
// コールバック関数
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

void Application::CreateGameWindow(HWND & hwnd, WNDCLASSEX & windowclass)
{
	HINSTANCE hinstance = GetModuleHandle(NULL);
	// ウィンドウの生成＆登録
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.lpfnWndProc = (WNDPROC)WndProc; // コールバック関数の指定
	windowclass.lpszClassName = "SplaShooter";  // アプリケーション名
	windowclass.hInstance = GetModuleHandle(0); // ハンドルの指定
	RECT wrc = { 0.0f, 0.0f, m_Width, m_Height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	// ウィンドウオブジェクトの生成
	hwnd = CreateWindow(windowclass.lpszClassName,	// クラス名
		"ゲームアプリ",								// タイトルバー　 
		WS_OVERLAPPEDWINDOW,						// ウィンドウタイプ
		CW_USEDEFAULT, CW_USEDEFAULT,				// 表示xy座標はOSに任せる
		wrc.right - wrc.left, wrc.bottom - wrc.top, // ウィンドウ幅と高さ
		NULL, NULL, windowclass.hInstance, NULL);	// ウィンドウハンドル、メニューハンドル、呼び出しアプリケーションハンドル、追加パラメータ
}

Application & Application::Instance()
{
	static Application instance;
	return instance;
}

bool Application::Init(HINSTANCE hinstance)
{
	auto result = CoInitializeEx(0, COINITBASE_MULTITHREADED);
	CreateGameWindow(m_hwnd, m_WindowClass);
	InputDevice::Init(hinstance, m_hwnd);
	return true;
}

void Application::AppRun()
{
	// ウィンドウ表示
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	// Fpsの初期化
	Fps& fps = Fps::Instance();
	fps.Init();

	// メッセージループ
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message = WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (fps.Update())
			{
				InputDevice::Update;
			}
		}			   	
	}
	fps.Uninit();
	InputDevice::Uninit();
	UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance); // ウィンドウクラスの登録を解除
}

SIZE Application::GetWindowSize() const
{
	SIZE ret;
	ret.cx = m_Width;
	ret.cy = m_Height;
	return ret;
}

HWND Application::Gethwnd() const
{
	return m_hwnd;
}
#pragma endregion Applicationクラスの関数