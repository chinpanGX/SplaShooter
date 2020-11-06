/*-----------------------------------------------------------

	[Shader.cpp]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Shader.h"
#include <io.h>

#pragma region Shader_Func
// 頂点シェーダー生成
void Shader::CreateVertexShader(Wrapper::DirectX11& dx, ID3D11VertexShader ** VertexShader, ID3D11InputLayout ** VertexLayout, const char * FileName)
{
	FILE* file;
	long int fsize;
	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);
	dx.GetDevice()->CreateVertexShader(buffer, fsize, NULL, VertexShader);

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	dx.GetDevice()->CreateInputLayout(layout, numElements, buffer, fsize, VertexLayout);
	delete[] buffer;
}

// ピクセルシェーダー生成
void Shader::CreatePixelShader(Wrapper::DirectX11& dx, ID3D11PixelShader ** PixelShader, const char * FileName)
{
	FILE* file;
	long int fsize;
	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);
	dx.GetDevice()->CreatePixelShader(buffer, fsize, NULL, PixelShader);
	delete[] buffer;
}

// コンストラクタ
Shader::Shader(const char * VertexShader_FileName, const char * PixelShader_FileName)
{
	auto& dx = Wrapper::DirectX11::Instance();
	CreateVertexShader(dx, &m_VertexShader, &m_InputLayout, VertexShader_FileName);
	CreatePixelShader(dx, &m_PixelShader, PixelShader_FileName);
}

// デストラクタ
Shader::~Shader()
{
	m_InputLayout->Release();
	m_InputLayout = NULL;
	m_VertexShader->Release();
	m_VertexShader = NULL;
	m_PixelShader->Release();
	m_PixelShader = NULL;
}

// 描画
void Shader::Draw()
{
	auto& dx = Wrapper::DirectX11::Instance();
	dx.GetDeviceContext()->IASetInputLayout(m_InputLayout);
	dx.GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	dx.GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
}
#pragma endregion Shaderクラスの関数定義 
