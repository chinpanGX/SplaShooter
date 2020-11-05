/*----------------------------------------------------------

	[TestScene.h]
	Author : 出合翔太

-----------------------------------------------------------*/
#pragma once
#include "Scene.h"

namespace Test
{
	// 指定のテストマップへシーンチェンジする関数をまとめる
	struct ChangeScene
	{
		static void TestMap1(); // １
	};

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

