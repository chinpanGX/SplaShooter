/*-----------------------------------------------------------

	[Texture.cpp]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Texture.h"

#pragma region Texture_Func
Texture::Texture()
{
	m_Texture[32] = NULL;
}

// ロード
unsigned int Texture::Load(Wrapper::DirectX11& dx, const char * FileName)
{
	unsigned int texture = 0;
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(), FileName, NULL, NULL, &m_Texture[m_ImageCount++], NULL);
	texture = m_ImageCount - 1;
	return texture;
}

// アンロード
void Texture::Unload(unsigned int Texture)
{
	m_Texture[Texture]->Release();
}

// セット
ID3D11ShaderResourceView* Texture::SetTexture(unsigned int Texture)
{
	return m_Texture[Texture];
}
#pragma endregion Textureクラスの関数定義