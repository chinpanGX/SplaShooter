/*-----------------------------------------------------------

	[Renderer.cpp]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Renderer.h"

#pragma region Define_Sprite_Func
void Sprite2D::Sprite::Init(Wrapper::DirectX11& dx)
{
	Wrapper::VERTEX_3D vertex[4];
	{
		vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(10.0f, 0.0f);

		vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 10.0f);

		vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(10.0f, 10.0f);
	}

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Wrapper::VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	dx.GetDevice()->CreateBuffer(&bd, &sd, &m_VtxBuffer);
}

void Sprite2D::Sprite::Uninit()
{
	m_VtxBuffer->Release();
}

void Sprite2D::Sprite::Draw(Wrapper::DirectX11& dx, ID3D11ShaderResourceView * texture, D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft, D3DXVECTOR2 texDownRight, D3DXCOLOR color)
{
	using namespace Wrapper;
	//ライト無効
	LIGHT light;
	light.Enable = false;
	dx.SetLight(light);

	D3D11_MAPPED_SUBRESOURCE msr;
	dx.GetDeviceContext()->Map(m_VtxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(drawPosition.x - drawSize.x * 0.5f, drawPosition.y - drawSize.y * 0.5f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = texUpLeft;

	vertex[1].Position = D3DXVECTOR3(drawPosition.x + drawSize.x * 0.5f, drawPosition.y - drawSize.y * 0.5f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(texDownRight.x, texUpLeft.y);

	vertex[2].Position = D3DXVECTOR3(drawPosition.x - drawSize.x * 0.5f, drawPosition.y + drawSize.y * 0.5f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(texUpLeft.x, texDownRight.y);

	vertex[3].Position = D3DXVECTOR3(drawPosition.x + drawSize.x * 0.5f, drawPosition.y + drawSize.y * 0.5f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = texDownRight;

	dx.GetDeviceContext()->Unmap(m_VtxBuffer, 0);

	//マトリクス設定
	dx.SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	dx.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VtxBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = color;
	dx.SetMaterial(material);

	//テクスチャ設定
	dx.GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	//プリミティブトポロジ設定
	dx.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	dx.GetDeviceContext()->Draw(4, 0);

	//変更後は戻しておく
	m_Alpha = 1.0f;
}
#pragma endregion Spriteクラスの関数定義

#pragma region Spriterenderer_Func
// ロード
void Sprite2D::Renderer::Load(const char * Filename)
{
	m_Sprite.Init(m_dx);
	m_Storage = m_Texture.Load(m_dx, Filename);
}

// アンロード
void Sprite2D::Renderer::Unload()
{
	m_Sprite.Uninit();
	m_Texture.Unload(m_Storage);
}

// 描画
void Sprite2D::Renderer::Draw(D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft, D3DXVECTOR2 texDownRight, D3DXCOLOR color)
{
	m_Sprite.Draw(m_dx, m_Texture.SetTexture(m_Storage), drawPosition, drawSize, texUpLeft, texDownRight, color);
}

// α値のセット
void Sprite2D::Renderer::SetAlpha(float alpha)
{
	m_Sprite.SetAlpha(alpha);
}
#pragma endregion SpriteRendererクラスの関数定義
