/*----------------------------------------------------------------

	[Fps.h]
	Author : 出合翔太

-----------------------------------------------------------------*/
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
