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
	static const unsigned __int32 m_Maxid = 256; // 配列の要素数
	unsigned __int32 m_Id[m_Maxid];	// IDの格納
	__int32 m_Size; // プレハブの数

	//　生成
	virtual void Create(unsigned __int32 size) {}; // size = 作るプレハブの数
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
		void Create(unsigned __int32 size)override;
		void Destory()override;
	public:
		enum ID : unsigned __int32
		{
			FADE,
			TATILE_BG,
			GAME_BG,
			FIELD,
			WAFFURU,
		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11ShaderResourceView* GetTexture(unsigned __int32 Id);
	};

	// 頂点シェーダー
	class VertexShader : public PrefabsBase
	{
	private:
		Loader::VertexShader* m_VertexShader;
		void Create(unsigned __int32 size)override;
		void Destory()override;
	public:
		enum ID : unsigned __int32
		{
			DEFAULT,
			MAPPING,
		};
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
		void Create(unsigned __int32 size)override;
		void Destory();
	public:
		enum ID : unsigned __int32
		{
			DEFAULT,
			MAPPING,
		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11PixelShader* GetPixelShader(unsigned __int32 Id);
	};

	// スタティックメッシュ
	class StaticMesh : public PrefabsBase
	{
	private:
		Loader::Model* m_StaticMesh;
		void Create(unsigned __int32 size)override;
		void Destory();
	public:
		enum ID : unsigned __int32
		{

		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		Loader::Model* GetModel(unsigned __int32 Id);
	};

	// スケルタルメッシュ
	class SkeletalMesh : public PrefabsBase
	{
	private:
		AnimationModel* m_SkeletalMesh;
		void Create(unsigned __int32 size)override;
		void Destory()override;
	public:
		enum ModelID : unsigned __int32
		{
			Akai,
		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		AnimationModel* GetModel(unsigned __int32 Id);
	};
}
#pragma endregion Prefabsをまとめたもの
