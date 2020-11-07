/*-----------------------------------------------------------

	[Shader.h]
	シェーダーに必要なものをまとめる
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include "DirectX11.h"
#include "GameObject.h"

// シェーダー構造体
class Shader
{
private:	
	// シェーダー
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11InputLayout*	m_InputLayout = NULL;
	ID3D11PixelShader*	m_PixelShader = NULL;

	// シェーダー生成
	void CreateVertexShader(Wrapper::DirectX11& dx, ID3D11VertexShader** VertexShader, ID3D11InputLayout** InputLayout, const char* FileName);
	void CreatePixelShader(Wrapper::DirectX11& dx, ID3D11PixelShader** PixelShader, const char* FileName);
public:
	Shader() = delete; // 空のコンストラクタを呼ばないように
	Shader(const char* VertexShader_FileName, const char* PixelShader_FileName);
	~Shader();
	void Draw();
};
