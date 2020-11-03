/*---------------------------------------------------------

	[Application.h]
	ゲームアプリケーションの管理
	Author : 出合翔太

----------------------------------------------------------*/
#pragma once
#include <Windows.h>

// フレームレートを管理 ＊シングルトン
class Fps
{
private:
	const float m_Framerate;
	DWORD m_dwExcLastTime;
	DWORD m_dwCurrentTime;
	DWORD m_dwOldCurrentTime;
	bool m_isReset;

	// privateコンストラクタ
	Fps() : m_Framerate(60), m_dwExcLastTime(0), m_dwCurrentTime(0), m_dwOldCurrentTime(0), m_isReset(false), m_deltaTime(0) { } 
	// コピー、代入は禁止
	Fps(const Fps&) = delete;
	void operator= (const Fps&) = delete;
public:
	float m_deltaTime;
	static Fps& Instance(); // インスタンス
	void Init();			// 初期化
	void Uninit();			// 終了
	bool Update();			// 更新
	void Reset();			// リセット
};

// ゲームアプリを管理 ＊シングルトン
class Application
{
private:
	WNDCLASSEX	m_WindowClass;
	HWND m_hwnd;
	const unsigned int m_Width = 1200;
	const unsigned int m_Height = 720;

	// ゲーム用ウィンドウ作成
	void CreateGameWindow(HWND& hwnd, WNDCLASSEX& windowclass); 
	// privateコンストラクタ
	Application() {}
	// コピー、代入は禁止
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;
public:
	~Application() {};
	static Application& Instance(); // インスタンス
	bool Init(HINSTANCE hinstance); // 初期化
	void AppRun();					
	SIZE GetWindowSize()const;
	HWND Gethwnd()const;
};

