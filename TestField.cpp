#include "TestField.h"
#include "Texture.h"
#include "Shader.h"
#include "Object3D.h"

void TestField::Init()
{
	m_Object = new Object3D;
	m_Shader = new Shader("normalMappingVS.cso", "normalMappingPS.cso");
	for (int i = 0; i < 2; i++)
	{
		m_Texture[i] = new Texture;
	}
	auto& dx = Wrapper::DirectX11::Instance();
	m_TextureStorge[0] = m_Texture[0]->Load(dx, "Asset/Texture/field004.jpg");
	m_TextureStorge[1] = m_Texture[1]->Load(dx, "Asset/Texture/waffuru.tif");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void TestField::Uninit()
{
	for (int i = 0; i < 2; i++)
	{
		m_Texture[i]->Unload(m_TextureStorge[i]);
		delete m_Texture[i];
	}
	delete m_Shader;
	delete m_Object;
}

void TestField::Update()
{
}

void TestField::Draw()
{
	auto & dx = Wrapper::DirectX11::Instance();
	m_Shader->Draw();
	for (int i = 0; i < 2; i++)
	{
		m_Object->SetTexture(dx, i, m_Texture[i]->SetTexture(m_TextureStorge[i]));
	}
	m_Object->Draw(dx,m_Position,m_Rotation,m_Scale);
}
