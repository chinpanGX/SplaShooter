/*------------------------------------------------------------

	[Input.cpp]
	イベント駆動型を行うための仮cpp
	キーボードの値を読み取り、そこに対応したイベントをその場で実行する
	Author : 太田朋希

-------------------------------------------------------------*/
#pragma once
#include <list>

#define KEY_LIMIT 6

class GameObject;

class Input
{
private:
	std::list<GameObject*> m_GameObject;
	bool m_IsKey[KEY_LIMIT * 3];

	BYTE m_OldKeyState[256];
	BYTE m_KeyState[256];

	static Input instance;

public:
	void Init();
	void Uninit();
	void Update();

	bool GetKeyPress(BYTE KeyCode);
	bool GetKeyTrigger(BYTE KeyCode);
	bool GetKeyRelease(BYTE KeyCode);

	static Input& GetInstance() { return instance; }
};
