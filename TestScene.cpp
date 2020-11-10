#include "TestScene.h"
#include "Manager.h"
#include "InputDevice.h"
#include "TestPlayer.h"
#include "Camera.h"
#include "Effect.h"
#include "TestField.h"
#include "field.h"

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

void ChangeScene::TestMap2()
{
	if (KeyBoard::IsTrigger(DIK_2))
	{
		Manager::SetScene<Test::TestMap2>();
	}
}

CField* g_Field;

void Test::TestMap1::Init()
{
	AddGameObject<Camera>(LAYER_CAMERA);
	//AddGameObject<TestPlayer>(LAYER_3D);
	//ddGameObject<TestField>(LAYER_3D);
	//g_Camera.Init();
	g_Field = new CField;
	g_Field->Init();
}

void Test::TestMap1::Uninit()
{
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
	g_Field->Draw();
}

void Test::TestMap2::Init()
{
}

void Test::TestMap2::Uninit()
{
}

void Test::TestMap2::Update()
{
}

void Test::TestMap2::Draw()
{
}
