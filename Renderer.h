/*--------------------------------------------------------

	[Renderer.h]
	2D描画用のクラスをまとめる : Texture,Sprite,SpriteRenderer
	Author : 出合翔太

---------------------------------------------------------*/
#pragma once
#include "DirectX11.h"

namespace Sprite2D
{
	// テクスチャを管理
	class Texture
	{
	private:
		unsigned int m_ImageCount = 0;
		ID3D11ShaderResourceView* m_Texture[32];
	public:
		Texture();
		~Texture() {};
		unsigned int Load(Wrapper::DirectX11& dx, const char* FileName); // ロード
		void Unload(unsigned int Texture);
		ID3D11ShaderResourceView* SetTexture(unsigned int Texture); // セット
	};
	
	// バッファや描画の処理を管理
	class Sprite
	{
	private:
		ID3D11Buffer* m_VtxBuffer = NULL;
		float m_Alpha = 1.0f;
	public:
		void Init(Wrapper::DirectX11& dx);
		void Uninit();
		// DrawPosition : 実際に描画する画像の中心座標、DrawSize : 実際に描画するが画像サイズ、TexUpLeft,TexDownRight : 描画する元画像の大きさ,MAX1.0f
		void Draw(Wrapper::DirectX11& dx, ID3D11ShaderResourceView* texture, D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft,
			D3DXVECTOR2 texDownRight, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		void SetAlpha(float alpha) { m_Alpha = alpha; }
	};
}

#pragma region Class_SpriteRenderer
// 2D用スプライトレンダラー…テクスチャ、スプライトをまとめたクラス
class SpriteRenderer
{
private:
	unsigned int m_Storage;
	Wrapper::DirectX11& m_dx;
	Sprite2D::Texture m_Texture;
	Sprite2D::Sprite m_Sprite;
public:
	SpriteRenderer() : m_dx(Wrapper::DirectX11::Instance()) {};
	void Load(const char* Filename);
	void Unload();
	void Draw(D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft, D3DXVECTOR2 texDownRight, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	void SetAlpha(float alpha);
};
#pragma endregion 2D用スプライトレンダラー
