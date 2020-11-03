/*--------------------------------------------------------------

	[Scene.h]
	シーン関連の処理を管理
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Scene.h"
#include "Bg.h"
#include "InputDevice.h"
#include "Manager.h"

// ゲームシーン
#pragma region Game_Func
// ロード
void GameScene::Game::Load()
{

}

// アンロード
void GameScene::Game::Unload()
{
}

// 初期化
void GameScene::Game::Init()
{
	AddGameObject<DrawBg::Game>(LAYER_2D);
}

void GameScene::Game::Uninit()
{

}

// 更新
void GameScene::Game::Update()
{
	Scene::Update();
	if (KeyBoard::IsTrigger(DIK_T) || GamePad::IsTrigger(0, BTN_2))
	{
		Manager::SetScene<Title>();
	}
}

// 描画
void GameScene::Game::Draw()
{
	Scene::Draw();
}
#pragma endregion Gameクラスの関数定義

// タイトルシーン
#pragma region Title_Func
void GameScene::Title::Load()
{
}

void GameScene::Title::Unload()
{
}

void GameScene::Title::Init()
{
	AddGameObject<DrawBg::Title>(LAYER_2D);
}

void GameScene::Title::Uninit()
{

}

void GameScene::Title::Update()
{
	Scene::Update();
	if (KeyBoard::IsTrigger(DIK_T) || GamePad::IsTrigger(0, BTN_2))
	{
		Manager::SetScene<Game>();
	}
}

void GameScene::Title::Draw()
{
	Scene::Draw();
}
#pragma endregion Titleのクラスの関数定義
