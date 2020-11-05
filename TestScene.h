/*----------------------------------------------------------

	[TestScene.h]
	Author : 出合翔太

-----------------------------------------------------------*/
#pragma once
#include "Scene.h"

// 指定のテストマップへシーンチェンジする関数をまとめる
struct ChangeScene
{
	static void ReturnTitle(); // タイトルに戻る
	static void TestMap1(); // １
};


namespace Test
{
	// テストの実行
	inline void Run()
	{
		ChangeScene::TestMap1();
	}

	// テストシーン１
	class TestMap1 : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
}

