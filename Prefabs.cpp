/*-----------------------------------------------------------

	[Prefabs.h]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Prefabs.h"

const unsigned int PrefabsBase::m_Maxid;

#pragma region Prefabs_Texture_Func
void Prefabs::Texture::Create(int size)
{
	m_Size = size;
	for (int i = 0; i < size; i++)
	{
		m_Texture = new Loader::Texture[size];
	}
}

void Prefabs::Texture::Destory()
{
	delete[] m_Texture;
}

void Prefabs::Texture::Load(Wrapper::DirectX11& dx)
{
	Create(5);
	m_Id[0] = m_Texture[0].Load(dx, "Asset/Texture/black.png");
	m_Id[1] = m_Texture[1].Load(dx, "Asset/Texture/Title.png");
	m_Id[2] = m_Texture[2].Load(dx, "Asset/Texture/Game.png");
	m_Id[3] = m_Texture[3].Load(dx, "Asset/Texture/field004.jpg");
	m_Id[4] = m_Texture[4].Load(dx, "Asset/Texture/waffuru.tif");
}

void Prefabs::Texture::Unload()
{
	for (int i = m_Size -1; i >= 0; i--)
	{
		m_Texture[i].Unload();
	}
	Destory();
}

ID3D11ShaderResourceView * Prefabs::Texture::GetTexture(unsigned int Id)
{
	return m_Texture[Id].GetTexture();
}
#pragma endregion Prefabs_Textureクラスの関数定義

#pragma region Prefabs_VertexShader_Func
void Prefabs::VertexShader::Create(int size)
{
	m_Size = size;
	for (int i = 0; i < size; i++)
	{
		m_VertexShader = new Loader::VertexShader[size];
	}
}

void Prefabs::VertexShader::Destory()
{
	delete[] m_VertexShader;
}

void Prefabs::VertexShader::Load(Wrapper::DirectX11& dx)
{
	Create(2);
	m_Id[0] = m_VertexShader[0].Load(dx, "Asset/Shader/vertexShader.cso");
	m_Id[1] = m_VertexShader[1].Load(dx, "Asset/Shader/MappingVS.cso");
}

void Prefabs::VertexShader::Unload()
{
	for (int i = m_Size -1; i >= 0; i--)
	{
		m_VertexShader[i].Unload();
	}
	Destory();
}

ID3D11VertexShader * Prefabs::VertexShader::GetVertexShader(unsigned int Id)
{
	return m_VertexShader[Id].GetVertexShader();
}

ID3D11InputLayout * Prefabs::VertexShader::GetInputLayout(unsigned int Id)
{
	return m_VertexShader[Id].GetInputLayout();
}
#pragma endregion Prefabs_VertexShaderクラスの関数定義

void Prefabs::PixelShader::Create(int size)
{
	m_Size = size;
	for (int i = 0; i < size; i++)
	{
		m_PixelShader = new Loader::PixelShader[size];
	}
}

void Prefabs::PixelShader::Destory()
{
	delete[] m_PixelShader;
}

void Prefabs::PixelShader::Load(Wrapper::DirectX11 & dx)
{
	Create(2);
	m_Id[0] = m_PixelShader[0].Load(dx, "Asset/Shader/pixelShader.cso");
	m_Id[1] = m_PixelShader[1].Load(dx, "Asset/Shader/MappingPS.cso");
}

void Prefabs::PixelShader::Unload()
{
	for (int i = m_Size -1; i >= 0; i--)
	{
		m_PixelShader[i].Unload();
	}
	Destory();
}

ID3D11PixelShader * Prefabs::PixelShader::GetPixelShader(unsigned int Id)
{
	return m_PixelShader[Id].GetPixelShader();
}
