/*------------------------------------------------------------

	[Input.cpp]
	イベント駆動型を行うための仮cpp
	キーボードの値を読み取り、そこに対応したイベントをその場で実行する
	Author : 太田朋希

-------------------------------------------------------------*/
#pragma once

class Input
{
private:
	//std::list<int*> m_CodeList;

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
