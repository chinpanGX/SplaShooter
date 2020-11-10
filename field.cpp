#include "DirectX11.h"
#include "field.h"


void CField::Init()
{
	auto &dx = Wrapper::DirectX11::Instance();
	Wrapper::VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3( -10.0f, 0.0f, 10.0f );
	vertex[0].Normal   = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	vertex[0].Diffuse  = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );
	vertex[0].TexCoord = D3DXVECTOR2( 0.0f, 0.0f );

	vertex[1].Position = D3DXVECTOR3( 10.0f, 0.0f, 10.0f );
	vertex[1].Normal   = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	vertex[1].Diffuse  = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );
	vertex[1].TexCoord = D3DXVECTOR2( 10.0f, 0.0f );

	vertex[2].Position = D3DXVECTOR3( -10.0f, 0.0f, -10.0f );
	vertex[2].Normal   = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	vertex[2].Diffuse  = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );
	vertex[2].TexCoord = D3DXVECTOR2( 0.0f, 10.0f );

	vertex[3].Position = D3DXVECTOR3( 10.0f, 0.0f, -10.0f );
	vertex[3].Normal   = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	vertex[3].Diffuse  = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );
	vertex[3].TexCoord = D3DXVECTOR2( 10.0f, 10.0f );


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( Wrapper::VERTEX_3D ) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.pSysMem = vertex;

	dx.GetDevice()->CreateBuffer( &bd, &sd, &m_VertexBuffer );


	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(),
											"Asset/Texture/field004.jpg",
											NULL,
											NULL,
											&m_Texture,
											NULL);
	assert( m_Texture );


	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(),
											"Asset/Texture/waffuru.tif",
											NULL,
											NULL,
											&m_TextureNormal,
											NULL);
	assert( m_TextureNormal );

	dx.CreateVertexShader(&m_VertexShader, &m_VertexLayout, "normalMappingVS.cso");
	dx.CreatePixelShader(&m_PixelShader, "normalMappingPS.cso");

	m_Position = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_Rotation = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_Scale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
}


void CField::Uninit()
{

	m_VertexBuffer->Release();
	m_Texture->Release();
	m_TextureNormal->Release();

	m_VertexLayout->Release();
	m_PixelShader->Release();
	m_VertexShader->Release();
}


void CField::Update()
{

}


void CField::Draw()
{
	auto & dx = Wrapper::DirectX11::Instance();

	//入力レイアウト設定
	dx.GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	dx.GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	dx.GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	dx.SetWorldMatrix(&world);
	
	// 頂点バッファ設定
	UINT stride = sizeof( Wrapper::VERTEX_3D );
	UINT offset = 0;
	dx.GetDeviceContext()->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );

	// マテリアル設定
	Wrapper::MATERIAL material;
	ZeroMemory( &material, sizeof(material) );
	material.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	dx.SetMaterial( material );

	// テクスチャ設定
	dx.GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	dx.GetDeviceContext()->PSSetShaderResources(1, 1, &m_TextureNormal);

	// プリミティブトポロジ設定
	dx.GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// ポリゴン描画
	dx.GetDeviceContext()->Draw( 4, 0 );
}