/*---------------------------------------------------------

	[Application.h]
	ゲームアプリケーションの管理
	Author : 出合翔太

----------------------------------------------------------*/
#pragma once
#include <Windows.h>

// ゲームアプリを管理 ＊シングルトン
class Application
{
private:
	WNDCLASSEX	m_WindowClass;
	HWND m_hwnd;
	// ウィンドウモード true->WindowScrren false->FullScrren
	bool m_WindowMode = false; 

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
	void Init(HINSTANCE hinstance); // 初期化	
	void AppRun();
	SIZE GetWindowSize()const;
	HWND Gethwnd()const;
};

