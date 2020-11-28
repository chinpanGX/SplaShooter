/*-----------------------------------------------------------

	[Prefabs.h]
	Author : 出合翔太

------------------------------------------------------------*/

#include "GameObject.h"
#include "Prefabs.h"

#pragma region Prefabs_Texture_Func
void Prefabs::Texture::Load(Wrapper::DirectX11& dx)
{
	m_Texture = new Loader::Texture[m_Size];
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
	delete[] m_Texture;
}

ID3D11ShaderResourceView * Prefabs::Texture::GetTexture(unsigned __int32 Id)
{
	return m_Texture[Id].GetTexture();
}
#pragma endregion Prefabs_Textureクラスの関数定義

#pragma region Prefabs_VertexShader_Func
void Prefabs::VertexShader::Load(Wrapper::DirectX11& dx)
{
	m_VertexShader = new Loader::VertexShader[m_Size];
	m_VertexShader[0].Load(dx, "Asset/Shader/vertexShader.cso");
	m_VertexShader[1].Load(dx, "Asset/Shader/MappingVS.cso");
}

void Prefabs::VertexShader::Unload()
{
	for (int i = m_Size -1; i >= 0; i--)
	{
		m_VertexShader[i].Unload();
	}
	delete[] m_VertexShader;
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
void Prefabs::PixelShader::Load(Wrapper::DirectX11 & dx)
{
	m_PixelShader = new Loader::PixelShader[m_Size];
	m_PixelShader[0].Load(dx, "Asset/Shader/pixelShader.cso");
	m_PixelShader[1].Load(dx, "Asset/Shader/MappingPS.cso");
}

void Prefabs::PixelShader::Unload()
{
	for (int i = m_Size -1; i >= 0; i--)
	{
		m_PixelShader[i].Unload();
	}
	delete[] m_PixelShader;
}

ID3D11PixelShader * Prefabs::PixelShader::GetPixelShader(unsigned __int32 Id)
{
	return m_PixelShader[Id].GetPixelShader();
}
#pragma endregion Prefabs_PixelShaderクラスの関数定義

#pragma region Prefabs_Model_Func
void Prefabs::Model::Load(Wrapper::DirectX11 & dx)
{
	m_Model = new AnimationModel[m_Size];
	m_Model[0].Load(dx, "asset\\model\\Akai_Idle.fbx");
	m_Model[0].LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	m_Model[0].LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");
	//m_Model[1].Load(dx, "asset\\model\\unitychan.fbx");
	//m_Model[1].LoadAnimation("asset\\model\\unitychan_WAIT00.fbx","Idle");
	//m_Model[1].LoadAnimation("asset\\model\\unitychan_RUN00_F.fbx", "Run");
}

void Prefabs::Model::Unload()
{
	__int32 count  = m_Size - 1;
	for (count; count >= 0; count--)
	{
		m_Model[count].Unload();
	}
	delete[] m_Model;
}

AnimationModel * Prefabs::Model::GetModel(unsigned __int32 Id)
{
	return &m_Model[Id];
}
#pragma endregion Prefabs_Modelクラスの関数定義