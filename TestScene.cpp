#include "TestScene.h"
#include "Manager.h"
#include "InputDevice.h"
#include "TestPlayer.h"
#include "Camera.h"
#include "Effect.h"

void ChangeScene::ReturnTitle()
{
	if (KeyBoard::IsTrigger(DIK_R))
	{
		Manager::SetScene<GameScene::Title>();
	}
}

void ChangeScene::TestMap1()
{
	if (KeyBoard::IsTrigger(DIK_1))
	{
		Manager::SetScene<Test::TestMap1>();
	}
}

Effect::Water m_water;

void Test::TestMap1::Init()
{
	AddGameObject<Camera>(LAYER_CAMERA);
	AddGameObject<TestPlayer>(LAYER_3D);
	m_water.Init();
}

void Test::TestMap1::Uninit()
{
	m_water.Uninit();
	Scene::Uninit();
}

void Test::TestMap1::Update()
{
	Scene::Update();
	ChangeScene::ReturnTitle();
}

void Test::TestMap1::Draw()
{
	Scene::Draw();
	m_water.Render();
}
