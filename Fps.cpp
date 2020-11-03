/*----------------------------------------------------------------

	[Fps.cpp]
	Author : o‡ãÄ‘¾

------------------------------------------------------------------*/
#include "Fps.h"
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
#pragma endregion FpsƒNƒ‰ƒX‚ÌŠÖ”