/*----------------------------------------------------------

	[Loader.h]
	読み込みに関するラッパー
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include "DirectX11.h"

class Loader
{
protected:
	unsigned int m_Count = -1;
};

namespace Loader
{
	// テクスチャを管理
	class Texture : public Loader
	{
	private:
		ID3D11ShaderResourceView* m_Texture = NULL;
	public:
		unsigned int Load(Wrapper::DirectX11& dx, std::string FileName); // ロード
		void Unload();
		ID3D11ShaderResourceView* GetTexture()const; // セット
	};

	// 頂点シェーダー
	class VertexShader : public Loader
	{
	private:
		ID3D11VertexShader* m_VertexShader = NULL;
		ID3D11InputLayout*	m_InputLayout = NULL;
		// 生成
		void CreateVertexShader(Wrapper::DirectX11 & dx, ID3D11VertexShader ** VertexShader, ID3D11InputLayout ** InputLayout, std::string FileName);
	public:
		unsigned int Load(Wrapper::DirectX11 & dx, std::string VertexShader_FileName);
		void Unload();
		ID3D11VertexShader* GetVertexShader()const;
		ID3D11InputLayout* GetInputLayout()const;
	};

	// ピクセルシェーダー
	class pixelShader : public Loader
	{
	private:
		ID3D11PixelShader*	m_PixelShader = NULL;
		// 生成
		void CreatePixelShader(Wrapper::DirectX11& dx, ID3D11PixelShader** PixelShader, std::string FileName);
	public:
		unsigned int Load(Wrapper::DirectX11 & dx, std::string PixelShader_FileName);
		void Unload();
		ID3D11PixelShader* GetPixelShader()const;
	};
}
