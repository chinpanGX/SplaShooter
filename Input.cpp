/*------------------------------------------------------------

	[Input.cpp]
	イベント駆動型を行うための仮cpp
	キーボードの値を読み取り、そこに対応したイベントをその場で実行する
	Author : 太田朋希

-------------------------------------------------------------*/
#include "DirectX11.h"
#include "Input.h"
#include "GameObject.h"

//キーボードの状態
enum KEYSTATE : int
{
	STATE_TRIGGER,
	STATE_PRESS,
	STATE_RELEASE,
	STATE_MAX
};

//キーボードの状態
enum KEY : int
{
	KEY_W = 'W',
	KEY_A = 'A',
	KEY_S = 'S',
	KEY_D = 'D',
	KEY_ENTER = VK_RETURN,
	KEY_SPACE = VK_SPACE,
	KEY_MAX = 6
};

template<typename T>
T& operator ++ (T& value)
{
	value = static_cast<T>(value + 1);
	return value;
}

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
	KEY key = KEY_W;

	//キーボードの状態取得
	memcpy(m_OldKeyState, m_KeyState, 256);
	GetKeyboardState(m_KeyState);

	//現在の使用するキーの状態を取得して配列に入れる
	for (int i = 0; i < KEY_MAX * 3; i += 3)
	{
		m_IsKey[i] = GetKeyTrigger(key);
		m_IsKey[i + 1] = GetKeyPress(key);
		m_IsKey[i + 2] = GetKeyRelease(key);
	}

	//現在のキーボードの状態から対応するキーイベント呼び出し
	for (GameObject* object : m_GameObject)
	{
		if(m_IsKey[0])
			object->OnTriggerW();
		if(m_IsKey[1])
			object->OnPressW();
		if(m_IsKey[2])
			object->OnReleaseW();

		if (m_IsKey[3])
			object->OnTriggerA();
		if (m_IsKey[4])
			object->OnPressA();
		if (m_IsKey[5])
			object->OnReleaseA();

		if (m_IsKey[6])
			object->OnTriggerS();
		if (m_IsKey[7])
			object->OnPressS();
		if (m_IsKey[8])
			object->OnReleaseS();

		if (m_IsKey[9])
			object->OnTriggerD();
		if (m_IsKey[10])
			object->OnPressD();
		if (m_IsKey[11])
			object->OnReleaseD();

		if (m_IsKey[12])
			object->OnTriggerSpace();
		if (m_IsKey[13])
			object->OnPressSpace();
		if (m_IsKey[14])
			object->OnReleaseSpace();

		if (m_IsKey[15])
			object->OnTriggerEnter();
		if (m_IsKey[16])
			object->OnPressEnter();
		if (m_IsKey[17])
			object->OnReleaseEnter();
	}
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