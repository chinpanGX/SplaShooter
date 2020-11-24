/*----------------------------------------------

	[Model.h]
	Author : 出合翔太

-----------------------------------------------*/
#pragma once
#include "DirectX11.h"
#include "Loader.h"

namespace Loader
{
	// モデル
	class Model
	{
	private:
		// マテリアル
		struct Material
		{
			Wrapper::MATERIAL m_Material;
			ID3D11ShaderResourceView* m_Texture;
			char m_Name[256];
			char m_TextureName[256];
		};

		// 描画サブセット
		struct Subset
		{
			Material m_Material;
			unsigned __int32 m_StartIndex;
			unsigned __int32 m_IndexNum;
		};

		// メッシュ
		struct Mesh
		{
			Wrapper::VERTEX_3D* m_VertexArray;
			Subset* m_SubsetArray;
			unsigned __int32 m_VertexNum;
			unsigned __int32* m_IndexArray;
			unsigned __int32 m_IndexNum;
			unsigned __int32 m_SubsetNum;
		};
		Subset* m_SubsetArray;
		ID3D11Buffer* m_VertexBuffer;
		ID3D11Buffer* m_IndexBuffer;
		unsigned __int32 m_SubsetNum;

		void LoadObject(const char* FileName, Mesh* Mesh);
		void LoadMaterial(const char* FileName, Material** MaterialArray, unsigned __int32* MaterialNum);
	public:
		void Load(Wrapper::DirectX11& dx, const char* FileName);
		void Unload();
		void Draw(Wrapper::DirectX11& dx);
		D3DXCOLOR GetColor() { return m_SubsetArray->m_Material.m_Material.Diffuse; }
		void SetColor(D3DXCOLOR Color) { m_SubsetArray->m_Material.m_Material.Diffuse = Color; }
	};
}
