/*---------------------------------------------------------

	[main.cpp]
	Author : èoçá„ƒëæ

----------------------------------------------------------*/
#include <Windows.h>
#include "Application.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto& app = Application::Instance();
	app.Init(hInstance);
	app.AppRun();
	return 0;
}
