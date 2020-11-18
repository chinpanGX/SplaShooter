#include "TestField.h"
#include "Polygon3D.h"
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
<<<<<<< HEAD
	
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Wrapper::VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	dx.GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
=======
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
>>>>>>> fb2c35c36d87e2c408284cf9a8be3192fd963e1a

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void TestField::Uninit()
{
	m_VertexBuffer->Release();
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

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	dx.SetWorldMatrix(&world);
	// 頂点バッファ設定
	UINT stride = sizeof(Wrapper::VERTEX_3D);
	UINT offset = 0;
	dx.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	// マテリアル設定
	Wrapper::MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	dx.SetMaterial(material);

	Engine::ObjectPool::SetTexture(dx, 0, Prefabs::Texture::ID::FIELD);
	Engine::ObjectPool::SetTexture(dx, 1, Prefabs::Texture::ID::WAFFURU);
	
	// プリミティブトポロジ設定
	dx.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	dx.GetDeviceContext()->Draw(4, 0);
}
