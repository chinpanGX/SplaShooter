/*--------------------------------------------------------------

	[Bg.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Bg.h"
#include "Manager.h"
#include "Application.h"
#include "Fps.h"
#include "Engine.h"

// スクリーンサイズのゲッター
D3DXVECTOR2 Bg::GetScrren()
{
	auto &app = Application::Instance();
	m_Scrren.x = (float)app.GetWindowSize().cx;
	m_Scrren.y = (float)app.GetWindowSize().cy;
	return m_Scrren;
}

// フェードの処理
#pragma region FuncName_of_classFade
Scene* Fade::m_NextScene = NULL; // スタティック変数

void Fade::Init()
{
	m_Sprite.Init();
	m_FadeTime = 0.5f;
}

void Fade::Uninit()
{
	
}

void Fade::Update()
{
	switch (m_FadeState)
	{
	case FADE_OUT:
		m_Alpha += m_Fps.m_deltaTime / m_FadeTime;
		if (m_Alpha > 1.0f)
		{
			Manager::ChangeScene(m_NextScene);
			m_FadeState = FADE_IN;
		}
		break;
	case FADE_IN:
		m_Alpha -= m_Fps.m_deltaTime / m_FadeTime;
		if (m_Alpha < 0.0f)
		{
			m_FadeState = FADE_NONE;
		}
		break;
	}
}

void Fade::Draw()
{
	m_Sprite.Draw(Engine::ObjectPool::GetTexture(Prefabs::TextureID::FADE) ,Bg::GetScrren() * 0.5f, Bg::GetScrren(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha));
}
#pragma endregion Fadeの関数定義

#pragma region Title_Func
void DrawBg::Title::Init()
{
	auto & dx = Wrapper::DirectX11::Instance();
	m_Sprite.Init();
}

void DrawBg::Title::Uninit()
{
	//m_Sprite.Unload();
	m_Sprite.Uninit();
}

void DrawBg::Title::Update()
{

}

void DrawBg::Title::Draw()
{
	m_Sprite.Draw(Engine::ObjectPool::GetTexture(Prefabs::TATILE_BG), Bg::GetScrren() * 0.5f, Bg::GetScrren(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}
#pragma endregion Titleの背景描画

#pragma region Game_Func
void DrawBg::Game::Init()
{
	m_Sprite.Init();
}

void DrawBg::Game::Uninit()
{
	m_Sprite.Uninit();
}

void DrawBg::Game::Update()
{

}

void DrawBg::Game::Draw()
{
	m_Sprite.Draw(Engine::ObjectPool::GetTexture(Prefabs::TextureID::GAME_BG), Bg::GetScrren() * 0.5f, Bg::GetScrren(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}
#pragma endregion Gameの背景描画
