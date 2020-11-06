/*-----------------------------------------------------------

	[Texture.h]
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include "DirectX11.h"

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
