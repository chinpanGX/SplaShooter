/*-----------------------------------------------------------

	[Prefabs.h]
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include "Loader.h"
#include "Model.h"
#include "AnimationModel.h"

#pragma region BaseClass_PrefabsBase
class PrefabsBase
{
protected:
	__int32 m_Size; // プレハブの数

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
	public:
		enum ID : unsigned __int32
		{
			FADE,
			TATILE_BG,
			GAME_BG,
			FIELD,
			WAFFURU,
			MAX
		};
		Texture() { m_Size = ID::MAX; }
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11ShaderResourceView* GetTexture(unsigned __int32 Id);
	};

	// 頂点シェーダー
	class VertexShader : public PrefabsBase
	{
	private:
		Loader::VertexShader* m_VertexShader;
	public:
		enum ID : unsigned __int32
		{
			DEFAULT,
			MAPPING,
			MAX
		};
		VertexShader() { m_Size = ID::MAX; }
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11VertexShader* GetVertexShader(unsigned __int32 Id);
		ID3D11InputLayout* GetInputLayout(unsigned __int32 Id);
	};

	// ピクセルシェーダー
	class PixelShader : public PrefabsBase
	{
	private:
		Loader::PixelShader* m_PixelShader;
	public:
		enum ID : unsigned __int32
		{
			DEFAULT,
			MAPPING,
			MAX
		};
		PixelShader() { m_Size = ID::MAX; }
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11PixelShader* GetPixelShader(unsigned __int32 Id);
	};

	// スケルタルメッシュ
	class Model : public PrefabsBase
	{
	private:
		AnimationModel* m_Model;
	public:
		enum ID : unsigned __int32
		{
			Akai,
			//Unitychan,
			MAX
		};
		Model() { m_Size = ID::MAX; }
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		AnimationModel* GetModel(unsigned __int32 Id);
	};
}
#pragma endregion Prefabsをまとめたもの
