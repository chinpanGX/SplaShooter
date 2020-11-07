#include "TestScene.h"
#include "Manager.h"
#include "InputDevice.h"
#include "TestPlayer.h"
#include "Camera.h"
#include "Effect.h"
#include "TestField.h"

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

TestField g_Field;
Camera g_Camera;

void Test::TestMap1::Init()
{
	//AddGameObject<Camera>(LAYER_CAMERA);
	//AddGameObject<TestPlayer>(LAYER_3D);
//ddGameObject<TestField>(LAYER_3D);
	g_Camera.Init();
	g_Field.Init();
}

void Test::TestMap1::Uninit()
{
	Scene::Uninit();
}

void Test::TestMap1::Update()
{
	//Scene::Update();
	ChangeScene::ReturnTitle();
}

void Test::TestMap1::Draw()
{
	//Scene::Draw();
	g_Camera.Draw();
	g_Field.Draw();
}
