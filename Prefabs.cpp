/*-----------------------------------------------------------

	[Prefabs.h]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Prefabs.h"
#include "Loader.h"

#pragma region Prefabs_Texture_Func
void Prefabs::Texture::Create(int size)
{
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
	Create(3);
	m_Id[0] = m_Texture[0].Load(dx, "Asset/Texture/black.png");
	m_Id[1] = m_Texture[1].Load(dx, "Asset/Texture/Title.png");
	m_Id[2] = m_Texture[2].Load(dx, "Asset/Texture/Game.png");
}

void Prefabs::Texture::Unload()
{
	for (int i = m_Id.size() -1; i >= 0; i--)
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
	Create(1);
	m_Id[0] = m_VertexShader[0].Load(dx, "Asset/Shader/vertexShader.cso");
}

void Prefabs::VertexShader::Unload()
{
	for (int i = m_Id.size() -1; i >= 0; i--)
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
	return m_VertexShader[Id], GetInputLayout();
}
#pragma endregion Prefabs_VertexShaderクラスの関数定義