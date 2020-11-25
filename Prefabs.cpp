/*-----------------------------------------------------------

	[Prefabs.h]
	Author : 出合翔太

------------------------------------------------------------*/

#include "GameObject.h"
#include "Prefabs.h"

const unsigned int PrefabsBase::m_Maxid;

#pragma region Prefabs_Texture_Func
void Prefabs::Texture::Create(unsigned __int32 size)
{
	m_Size = size;
	m_Texture = new Loader::Texture[m_Size];
}

void Prefabs::Texture::Destory()
{
	delete[] m_Texture;
}

void Prefabs::Texture::Load(Wrapper::DirectX11& dx)
{
	Create(5);
	m_Texture[0].Load(dx, "Asset/Texture/black.png");
	m_Texture[1].Load(dx, "Asset/Texture/Title.png");
	m_Texture[2].Load(dx, "Asset/Texture/Game.png");
	m_Texture[3].Load(dx, "Asset/Texture/field004.jpg");
	m_Texture[4].Load(dx, "Asset/Texture/waffuru.tif");
}

void Prefabs::Texture::Unload()
{
	for (int i = m_Size -1; i >= 0; i--)
	{
		m_Texture[i].Unload();
	}
	Destory();
}

ID3D11ShaderResourceView * Prefabs::Texture::GetTexture(unsigned __int32 Id)
{
	return m_Texture[Id].GetTexture();
}
#pragma endregion Prefabs_Textureクラスの関数定義

#pragma region Prefabs_VertexShader_Func
void Prefabs::VertexShader::Create(unsigned __int32 size)
{
	m_Size = size;
	m_VertexShader = new Loader::VertexShader[m_Size];
}

void Prefabs::VertexShader::Destory()
{
	delete[] m_VertexShader;
}

void Prefabs::VertexShader::Load(Wrapper::DirectX11& dx)
{
	Create(2);
	m_VertexShader[0].Load(dx, "Asset/Shader/vertexShader.cso");
	m_VertexShader[1].Load(dx, "Asset/Shader/MappingVS.cso");
}

void Prefabs::VertexShader::Unload()
{
	for (int i = m_Size -1; i >= 0; i--)
	{
		m_VertexShader[i].Unload();
	}
	Destory();
}

ID3D11VertexShader * Prefabs::VertexShader::GetVertexShader(unsigned __int32 Id)
{
	return m_VertexShader[Id].GetVertexShader();
}

ID3D11InputLayout * Prefabs::VertexShader::GetInputLayout(unsigned __int32 Id)
{
	return m_VertexShader[Id].GetInputLayout();
}
#pragma endregion Prefabs_VertexShaderクラスの関数定義

#pragma region Prefabs_PixelShader_Func
void Prefabs::PixelShader::Create(unsigned __int32 size)
{
	m_Size = size;
	m_PixelShader = new Loader::PixelShader[m_Size];
}

void Prefabs::PixelShader::Destory()
{
	delete[] m_PixelShader;
}

void Prefabs::PixelShader::Load(Wrapper::DirectX11 & dx)
{
	Create(2);
	m_PixelShader[0].Load(dx, "Asset/Shader/pixelShader.cso");
	m_PixelShader[1].Load(dx, "Asset/Shader/MappingPS.cso");
}

void Prefabs::PixelShader::Unload()
{
	for (int i = m_Size -1; i >= 0; i--)
	{
		m_PixelShader[i].Unload();
	}
	Destory();
}

ID3D11PixelShader * Prefabs::PixelShader::GetPixelShader(unsigned __int32 Id)
{
	return m_PixelShader[Id].GetPixelShader();
}
#pragma endregion Prefabs_PixelShaderクラスの関数定義

#pragma region Prefabs_StaticMesh_Func
void Prefabs::StaticMesh::Create(unsigned __int32 size)
{
	m_Size = size;
	m_StaticMesh = new Loader::Model[m_Size];
}

void Prefabs::StaticMesh::Destory()
{
	delete[] m_StaticMesh;
}

void Prefabs::StaticMesh::Load(Wrapper::DirectX11 & dx)
{
	//Create(要素数);
	
}

void Prefabs::StaticMesh::Unload()
{
	__int32 count = m_Size - 1;
	for (count; count >= 0; count--)
	{
		m_StaticMesh[count].Unload();
	}
	Destory();
}

Loader::Model * Prefabs::StaticMesh::GetModel(unsigned __int32 Id)
{
	return &m_StaticMesh[Id];
}
#pragma endregion Prefabs_StaticMeshクラスの関数定義

void Prefabs::SkeletalMesh::Create(unsigned __int32 size)
{
	m_Size = size;
	m_SkeletalMesh = new AnimationModel[m_Size];
}

void Prefabs::SkeletalMesh::Destory()
{
	delete[] m_SkeletalMesh;
}

void Prefabs::SkeletalMesh::Load(Wrapper::DirectX11 & dx)
{
	Create(1);
	m_SkeletalMesh[0].Load(dx, "asset\\model\\Akai_Idle.fbx");
	m_SkeletalMesh[0].LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	m_SkeletalMesh[0].LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");
}

void Prefabs::SkeletalMesh::Unload()
{
	__int32 count  = m_Size - 1;
	for (count; count >= 0; count--)
	{
		m_SkeletalMesh[count].Unload();
	}
	Destory();
}

AnimationModel * Prefabs::SkeletalMesh::GetModel(unsigned __int32 Id)
{
	return &m_SkeletalMesh[Id];
}
