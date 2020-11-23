#include "Engine.h"
#include "Polygon3D.h"
#include "Test.h"

void Test_Chinapan::Field::CreateVertex(Wrapper::VERTEX_3D Vertex[4])
{
	Vertex[0].Position = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
	Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	Vertex[1].Position = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[1].TexCoord = D3DXVECTOR2(10.0f, 0.0f);

	Vertex[2].Position = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
	Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 10.0f);

	Vertex[3].Position = D3DXVECTOR3(10.0f, -10.0f, 0.0f);
	Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[3].TexCoord = D3DXVECTOR2(10.0f, 10.0f);
}

void Test_Chinapan::Field::Init()
{

	auto& dx = Wrapper::DirectX11::Instance();
	Wrapper::VERTEX_3D vertex[4];
	CreateVertex(vertex);
	
	m_Polygon = new Polygon3D(dx,vertex);
	m_Position = D3DXVECTOR3(0.0f, -5.0f, 10.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void Test_Chinapan::Field::Uninit()
{
	delete m_Polygon;
}

void Test_Chinapan::Field::Update()
{
	//m_Rotation.y += 0.05f;
}

void Test_Chinapan::Field::Draw()
{
	auto & dx = Wrapper::DirectX11::Instance();
	Engine::ObjectPool::SetInputLayout(dx, Prefabs::VertexShader::MAPPING);
	Engine::ObjectPool::SetVertexShader(dx, Prefabs::VertexShader::MAPPING);
	Engine::ObjectPool::SetPixelShader(dx, Prefabs::PixelShader::MAPPING);

	Engine::ObjectPool::SetTexture(dx, 0, Prefabs::Texture::ID::FIELD);
	Engine::ObjectPool::SetTexture(dx, 1, Prefabs::Texture::ID::WAFFURU);
	//m_Polygon->Draw(dx, m_Position, m_Rotation, m_Scale);
}
