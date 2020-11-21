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
	static void TestMap2(); // 2
};


namespace Test
{
	// テストの実行
	inline void Run()
	{
		ChangeScene::TestMap1();
		ChangeScene::TestMap2();
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

	class TestMap2 : public TestMap1
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
}

