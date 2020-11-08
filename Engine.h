/*-----------------------------------------------------------

	[Engine.h]
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include "Prefabs.h"

// DirectXデバイス解放マクロ
#define SAFE_RELEASE(p) do {if(p){(p)->Release(); (p) = NULL;} } while(0)

namespace Engine
{
	// オブジェクトプール
	class ObjectPool
	{
	private:
		static Prefabs::PrefabsTexture* m_Texture;
	public:
		static void Init();
		static void Uninit();
		static void Update();
		static void Draw();
		static ID3D11ShaderResourceView* GetTexture(unsigned int Id);
	};
}
