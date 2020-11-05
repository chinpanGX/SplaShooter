/*---------------------------------------------------------

	[Effect.h]
	Author : 出合翔太

----------------------------------------------------------*/
#pragma once
#include "DirectX11.h"
#include "Shader.h"

namespace Effect
{
	// 2D座標
	struct Float2
	{
		float x;
		float y;
	};

	// 3D座標->一応作っただけ
	struct float3
	{
		float x;
		float y;
		float z;
	};

	// 水のエフェクト -> ポストエフェクトで表現
	class Water
	{
	private:
		Shader* m_Shader = NULL;
		// エフェクトのパラメータ
		struct Parameter
		{
			Float2 m_Screen;	// スクリーン座標
			float m_Speed;		// 流れる速度
			float m_Distortion;	// 歪みの強度
		};
		Parameter m_Parameter;
	public:
		void Init();
		void Uninit();
		void Render();	// レンダリング
	};
};

