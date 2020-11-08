/*-----------------------------------------------------------

	[Texture.h]
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include "Component.h"
#include "DirectX11.h"

// テクスチャを管理
class Texture
{
private:
	unsigned int m_ImageCount = -1;
	ID3D11ShaderResourceView* m_Texture;
public:
	Texture() {};
	~Texture() {};
	unsigned int Load(Wrapper::DirectX11& dx, std::string FileName); // ロード
	void Unload();
	ID3D11ShaderResourceView* SetTexture(); // セット
};

