#include "TestField.h"
#include "Shader.h"
#include "Object3D.h"

void TestField::Init()
{
	auto& dx = Wrapper::DirectX11::Instance();
	// ↓インスタンス生成
	m_Object = new Object3D;
	// シェーダーの読み込み
	//m_Shader = new Shader("normalMappingVS.cso", "normalMappingPS.cso");
	// テクスチャの読み込み
	m_TextureStorge[1] = m_Texture[0].Load(dx, "Asset/Texture/field004.jpg");
	m_TextureStorge[1] = m_Texture[1].Load(dx, "Asset/Texture/waffuru.tif");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void TestField::Uninit()
{
	for (int i = 0; i < 2; i++)
	{
		m_Texture[i].Unload(m_TextureStorge[i]);
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
	// シェーダーの描画
	m_Shader->Draw();
	// テクスチャを設定
	for (int i = 0; i < 2; i++)
	{
		m_Object->SetTexture(dx, i, m_Texture[i].SetTexture(m_TextureStorge[i]));
	}
	// 描画
	m_Object->Draw(dx,m_Position,m_Position,m_Scale);
}
