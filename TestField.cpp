#include "TestField.h"
#include "Object3D.h"
#include "Engine.h"

void TestField::CreateVertex(Wrapper::VERTEX_3D Vertex[4])
{
	Vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
	Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	
	Vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[1].TexCoord = D3DXVECTOR2(10.0f, 0.0f);
	
	Vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 10.0f);
	
	Vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[3].TexCoord = D3DXVECTOR2(10.0f, 10.0f);
}

void TestField::Init()
{
	auto& dx = Wrapper::DirectX11::Instance();
	Wrapper::VERTEX_3D vertex[4];
	CreateVertex(vertex);
	// ↓インスタンス生成
	m_Object = new Object3D(dx,vertex);
<<<<<<< HEAD
	// シェーダーの読み込み
	// ↓画面真っ暗の原因
	m_Shader = new Shader("MappingVS.cso", "MappingPS.cso");
	//m_Shader = new Shader("vertexShader.cso", "pixelShader.cso");

	// テクスチャの読み込み
	m_TextureStorge[1] = m_Texture[0].Load(dx, "Asset/Texture/field004.jpg");
	m_TextureStorge[1] = m_Texture[1].Load(dx, "Asset/Texture/waffuru.tif");
=======
>>>>>>> bcb5fd99f6e41fd5d46d781c1365f287cbbef2e8

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void TestField::Uninit()
{
	delete m_Object;
}

void TestField::Update()
{
}

void TestField::Draw()
{
	auto & dx = Wrapper::DirectX11::Instance();
	Engine::ObjectPool::SetInputLayout(dx, Prefabs::VertexShader::MAPPING);
	Engine::ObjectPool::SetVertexShader(dx, Prefabs::VertexShader::MAPPING);
	Engine::ObjectPool::SetPixelShader(dx, Prefabs::PixelShader::MAPPING);
	m_Object->Set(dx, m_Position, m_Rotation, m_Scale);
	Engine::ObjectPool::SetTexture(dx, 0, Prefabs::Texture::ID::FIELD);
	Engine::ObjectPool::SetTexture(dx, 1, Prefabs::Texture::ID::WAFFURU);
	m_Object->DrawPolygon(dx);
}
