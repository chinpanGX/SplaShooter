/*---------------------------------------------------------

	[Effect.cpp]
	Author : o‡ãÄ‘¾

----------------------------------------------------------*/
#include "Effect.h"
#include "Application.h"

void Effect::Water::Init()
{
	auto& app = Application::Instance();
	m_Parameter.m_Screen.x = app.GetWindowSize().cx;
	m_Parameter.m_Screen.y = app.GetWindowSize().cy;
	m_Parameter.m_Speed = 5.0f;
	m_Parameter.m_Distortion = 5.0f;
	
}

void Effect::Water::Uninit()
{
}

void Effect::Water::Render()
{
	auto& dx = Wrapper::DirectX11::Instance();
	// ‘S‰æ–Êƒ|ƒŠƒSƒ“‚Ì•`‰æ
	dx.GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}
