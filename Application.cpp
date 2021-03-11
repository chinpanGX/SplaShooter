/*---------------------------------------------------------

	[Application.cpp]
	Author : �o���đ�

----------------------------------------------------------*/
#include "Application.h"
#include "InputDevice.h"
#include "Manager.h"
#include "Fps.h"
#include "Input.h"

// �E�B���h�E�T�C�Y
namespace
{
	const float s_WindowWidth = 1920;
	const float s_WindowHeight = 1080;
}

#pragma region Application_Func
// �E�B���h�E�v���V�[�W��
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
		// �E�B���h�E�̐������o�^
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.lpfnWndProc = (WNDPROC)WndProc; // �R�[���o�b�N�֐��̎w��
		windowClass.lpszClassName = "Dx11";			// �A�v���P�[�V������
		windowClass.hInstance = GetModuleHandle(0);	// �n���h���̎w��
		RegisterClassEx(&windowClass);				// �A�v���P�[�V�����N���X
		RECT wrc = { 0,0,s_WindowWidth, s_WindowHeight };
		AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
		// �E�B���h�E�I�u�W�F�N�g�̐���
		hwnd = CreateWindow(windowClass.lpszClassName,	// �N���X��
			"�Q�[���A�v��",								// �^�C�g���o�[
			WS_OVERLAPPEDWINDOW,						// �E�B���h�E�^�C�v
			CW_USEDEFAULT, CW_USEDEFAULT,				// �\��xy���W��OS�ɔC����
			wrc.right - wrc.left, wrc.bottom - wrc.top, // �E�B���h�E���ƍ���
			NULL, NULL, windowClass.hInstance, NULL);	// �E�B���h�E�n���h��, ���j���[�n���h��,�Ăяo���A�v���P�[�V�����n���h��, �ǉ��p�����[�^
	}
	else if (m_WindowMode == false)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		// �E�B���h�E�̐������o�^
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.lpfnWndProc = (WNDPROC)WndProc; // �R�[���o�b�N�֐��̎w��
		windowClass.lpszClassName = "Dx11";			// �A�v���P�[�V������
		windowClass.hInstance = GetModuleHandle(0);	// �n���h���̎w��
		RegisterClassEx(&windowClass);				// �A�v���P�[�V�����N���X
		RECT wrc = { 0,0,s_WindowWidth, s_WindowHeight };
		AdjustWindowRect(&wrc, WS_CAPTION, false);
		// �E�B���h�E�I�u�W�F�N�g�̐���
		hwnd = CreateWindow(windowClass.lpszClassName,	// �N���X��
			"�Q�[���A�v��",								// �^�C�g���o�[
			WS_VISIBLE | WS_POPUP,						// �E�B���h�E�^�C�v
			CW_USEDEFAULT, CW_USEDEFAULT,				// �\��xy���W��OS�ɔC����
			wrc.right - wrc.left, wrc.bottom - wrc.top, // �E�B���h�E���ƍ���
			NULL, NULL, windowClass.hInstance, NULL);	// �E�B���h�E�n���h��, ���j���[�n���h��,�Ăяo���A�v���P�[�V�����n���h��, �ǉ��p�����[�^
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
	CreateGameWindow(m_hwnd, m_WindowClass); // �Q�[���E�B���h�E
	InputDevice::Init(hInstance, m_hwnd);	 // �R���g���[���̏�����
	
}

void Application::AppRun()
{
	// �E�B���h�E�\��
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);
	
	// �t���[�����[�g�̏�����
	Fps& fps = Fps::Instance();
	fps.Init();
	Manager::Init();

	// ���b�Z�[�W���[�v
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) // PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
			{
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if(fps.Update())
			{
				InputDevice::Update(); // �R���g���[���̍X�V
				Manager::Update();
				// �`�揈��
				Manager::Draw();
			}
		}
	}

	
	Manager::Uninit();
	fps.Uninit();
	InputDevice::Uninit();  // �R���g���[���̏I������ 
	timeEndPeriod(1);		// ����\��߂�
	//DxLib_End();
	UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance); // �E�B���h�E�N���X�̓o�^������
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
#pragma endregion Application�N���X�̊֐�