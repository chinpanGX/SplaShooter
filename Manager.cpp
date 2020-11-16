/*----------------------------------------------------------

	[Manager.cpp]
	Author : 出合翔太

-----------------------------------------------------------*/
#include "Manager.h"
#include <time.h>
#include "Bg.h"
#include "Scene.h"
#include "TestPlayer.h"
#include "TestScene.h"
#include "Engine.h"

// スタティック変数
Scene* Manager::m_Scene = NULL;
Fade Manager::m_Fade;
Wrapper::DirectX11& Manager::m_dx = Wrapper::DirectX11::Instance();

#pragma region Manager_Func
// 初期化
void Manager::Init()
{
	srand((unsigned int)time(NULL));
	m_dx.Init();
	Engine::ObjectPool::Init();
	m_Fade.Init();
	SetScene<GameScene::Title>();
	m_Fade.m_FadeState = m_Fade.FADE_IN;
	ChangeScene(m_Fade.m_NextScene);
}

// 終了処理
void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	Engine::ObjectPool::Uninit();
	m_dx.Uninit();
}

// 更新処理
void Manager::Update()
{
	m_Fade.Update();
	m_Scene->Update();
}

// 描画処理
void Manager::Draw()
{
	m_dx.Begin();
	
	//3D用ライト設定
	Wrapper::LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_dx.SetLight(light);
	
	m_Scene->Draw();
	m_Fade.Draw();

	light.Enable = false;
	m_dx.SetLight(light);

	m_dx.End();
}

// 画面遷移
void Manager::ChangeScene(Scene * scene)
{
	if (m_Scene)
	{
		m_Scene->Uninit();
		delete m_Scene;
	}
	m_Scene = scene;
	scene->Init();
}
#pragma endregion AppManagerの関数定義

