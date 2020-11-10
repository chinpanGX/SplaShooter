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
		static Prefabs::Texture* m_Texture;
		static Prefabs::VertexShader* m_VertexShader;
		static Prefabs::PixelShader* m_PixelShader;
	public:
		static void Init();
		static void Uninit();
		static void Update();
		static void Draw();
		// テクスチャのGetter / Setter
		static ID3D11ShaderResourceView* GetTexture(unsigned int Id);
		static void SetTexture(Wrapper::DirectX11& dx, int slot, unsigned int Id); // slot = 設定するスロット、ID = 格納ID

		// シェーダーの設定
		static void SetVertexShader(Wrapper::DirectX11& dx, unsigned int Id);
		static void SetInputLayout(Wrapper::DirectX11& dx, unsigned int Id);
		static void SetPixelShader(Wrapper::DirectX11& dx, unsigned int Id);
	};
}
