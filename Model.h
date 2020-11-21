/*----------------------------------------------

	[ModelManager.h]
	Author : 出合翔太

-----------------------------------------------*/
#pragma once

#include <map>
#include <vector>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"

#pragma comment (lib,"assimp.lib")

#include "DirectX11.h"

// スタティックメッシュ
namespace StaticMesh
{
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

	// モデル
	class Model
	{
	private:
		Wrapper::DirectX11& m_dx = Wrapper::DirectX11::Instance();
		Subset* m_SubsetArray;
		ID3D11Buffer* m_VertexBuffer;
		ID3D11Buffer* m_IndexBuffer;
		unsigned __int32 m_SubsetNum;

		void LoadObject(const char* FileName, Mesh* Mesh);
		void LoadMaterial(const char* FileName, Material** MaterialArray, unsigned __int32* MaterialNum);
	public:
		void Load(const char* FileName);
		void Unload();
		void Draw();
		D3DXCOLOR GetColor() { return m_SubsetArray->m_Material.m_Material.Diffuse; }
		void SetColor(D3DXCOLOR Color) { m_SubsetArray->m_Material.m_Material.Diffuse = Color; }
	};
}