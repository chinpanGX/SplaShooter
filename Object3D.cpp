/*-----------------------------------------------------------

	[Object3D.cpp]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Object3D.h"

Object3D::Object3D()
{
	auto& instance = Wrapper::DirectX11::Instance();
	Wrapper::VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

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

	instance.GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

Object3D::~Object3D()
{
	m_VertexBuffer->Release();
	m_VertexBuffer = NULL;
}

void Object3D::SetTexture(Wrapper::DirectX11 & instance, int Slot, ID3D11ShaderResourceView * Texture)
{
	// テクスチャ設定
	instance.GetDeviceContext()->PSSetShaderResources(Slot, 1, &Texture);
}

void Object3D::Draw(Wrapper::DirectX11 & instance, D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale)
{
	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	instance.SetWorldMatrix(&world);

	// 頂点バッファ設定
	UINT stride = sizeof(Wrapper::VERTEX_3D);
	UINT offset = 0;
	instance.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	Wrapper::MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	instance.SetMaterial(material);

	// プリミティブトポロジ設定
	instance.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	instance.GetDeviceContext()->Draw(4, 0);
}