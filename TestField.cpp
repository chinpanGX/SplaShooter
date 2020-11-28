#include "TestField.h"
#include "Polygon3D.h"
#include "Engine.h"

namespace
{
	auto& s_dx = Wrapper::DirectX11::Instance();
}

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
	Wrapper::VERTEX_3D vertex[4];
	CreateVertex(vertex);

	// ↓インスタンス生成
	m_Polygon = new Polygon3D(s_dx,vertex);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void TestField::Uninit()
{
	delete m_Polygon;
}

void TestField::Update()
{
}

void TestField::Draw()
{
	Engine::ObjectPool::SetInputLayout(s_dx, Prefabs::VertexShader::MAPPING);
	Engine::ObjectPool::SetVertexShader(s_dx, Prefabs::VertexShader::MAPPING);
	Engine::ObjectPool::SetPixelShader(s_dx, Prefabs::PixelShader::MAPPING);

	Engine::ObjectPool::SetTexture(s_dx, 0, Prefabs::Texture::ID::FIELD);
	Engine::ObjectPool::SetTexture(s_dx, 1, Prefabs::Texture::ID::WAFFURU);
	
	m_Polygon->DrawPolygon(s_dx, m_Position, m_Rotation, m_Scale);
}

void TestFiled2::Init()
{
}

void TestFiled2::Uninit()
{
}

void TestFiled2::Update()
{
}

void TestFiled2::Draw()
{
	//Engine::ObjectPool::StaticMeshDraw(s_dx, Prefabs::StaticMesh::ID::STAGE);
}
