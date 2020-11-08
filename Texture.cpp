/*-----------------------------------------------------------

	[Texture.cpp]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Texture.h"
#include "Engine.h"

#pragma region Texture_Func
// ロード
unsigned int Texture::Load(Wrapper::DirectX11& dx, std::string FileName)
{
	m_ImageCount++;
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(), FileName.c_str(), NULL, NULL, &m_Texture, NULL);
	return m_ImageCount;
}

// アンロード
void Texture::Unload()
{
	SAFE_RELEASE(m_Texture);
}

// セット
ID3D11ShaderResourceView* Texture::SetTexture()
{
	return m_Texture;
}
#pragma endregion Textureクラスの関数定義
