#include "TestScene.h"
#include "Manager.h"
#include "InputDevice.h"
#include "TestPlayer.h"

void Test::ChangeScene::TestMap1()
{
	if (KeyBoard::IsTrigger(DIK_1))
	{
		Manager::SetScene<Test::TestMap1>();
	}
}

void Test::TestMap1::Init()
{
	AddGameObject<TestPlayer>(LAYER_3D);
}

void Test::TestMap1::Uninit()
{
	Scene::Uninit();
}

void Test::TestMap1::Update()
{
	Scene::Update();
}

void Test::TestMap1::Draw()
{
	Scene::Draw();
}
