/*-----------------------------------------------------------

	[Prefabs.h]
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include "Loader.h"

#pragma region BaseClass_PrefabsBase
class PrefabsBase
{
protected:
	static const unsigned int m_Maxid = 256; // 配列の要素数
	unsigned int m_Id[m_Maxid];	// IDの格納
	int m_Size; // プレハブの数

	//　生成
	virtual void Create(int size) {}; // size = 作るプレハブの数
	//　破棄
	virtual void Destory() {};
public:
	virtual void Load(Wrapper::DirectX11& dx) = 0;
	virtual void Unload() = 0;
};
#pragma endregion Prefabsの基底クラス

#pragma region Prefabs_Wrapper
namespace Prefabs
{
	// Textureのプレハブ
	class Texture : public PrefabsBase
	{
	private:
		Loader::Texture* m_Texture;
		void Create(int size)override; 
		void Destory()override;
	public:
		enum ID : int
		{
			FADE,
			TATILE_BG,
			GAME_BG
		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11ShaderResourceView* GetTexture(unsigned int Id);
	};

	// 頂点シェーダー
	class VertexShader : public PrefabsBase
	{
	private:
		Loader::VertexShader* m_VertexShader;
		void Create(int size)override;
		void Destory()override;
	public:
		enum ID : int
		{
			DEFAULT,
		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11VertexShader* GetVertexShader(unsigned int Id);
		ID3D11InputLayout* GetInputLayout(unsigned int Id);
	};

	// ピクセルシェーダー
	class PixelShader : public PrefabsBase
	{
	private:
		Loader::PixelShader* m_PixelShader;
		void Create(int size)override;
		void Destory();
	public:
		enum ID : int 
		{
			DEFAULT,
		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11PixelShader* GetPixelShader(unsigned int Id);
	};
}
#pragma endregion Prefabsをまとめたもの
