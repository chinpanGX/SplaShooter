/*------------------------------------------------------------

	[Input.cpp]
	イベント駆動型を行うための仮cpp
	キーボードの値を読み取り、そこに対応したイベントをその場で実行する
	Author : 太田朋希

-------------------------------------------------------------*/
#include "DirectX11.h"
#include "Input.h"
#include <list>


enum E_KEY : int
{
	T = 'T',
	SPACE = VK_SPACE,
	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
};

void Input::Init()
{
	memset(m_OldKeyState, 0, 256);
	memset(m_KeyState, 0, 256);
}

void Input::Uninit()
{

}

void Input::Update()
{
	memcpy(m_OldKeyState, m_KeyState, 256);

	GetKeyboardState(m_KeyState);
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

bool Input::GetKeyRelease(BYTE KeyCode)
{
	return (!(m_KeyState[KeyCode] & 0x80) && (m_OldKeyState[KeyCode] & 0x80));
}