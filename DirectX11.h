/*---------------------------------------------------------

	[DirectX11.h]
	DirectX11関連の処理
	Author : 出合翔太

----------------------------------------------------------*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h> // エラー処理
#include <iostream>

#pragma warning(push)
#pragma warning(disable:4005)

// DirectXのAPI
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
// 算術ライブラリ
#include <DirectXMath.h>
// シェーダーのコンパイラ
#include <d3dcompiler.h>

#pragma warning(pop)

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

// ランタイムエラーマクロ
#define STRINGFY(s)  #s
#define TO_STRING(x) STRINGFY(x)
#define FILE_PREFIX __FILE__ "(" TO_STRING(__LINE__) "): " 
#define ThrowIfFailed(hr, msg) Utility::CheckResultCode( hr, FILE_PREFIX msg)

namespace Utility
{
	class Exception : public std::runtime_error
	{
	public:
		Exception(const std::string& msg) : std::runtime_error(msg.c_str()) {}
	};

	inline void CheckResultCode(HRESULT hr, const std::string& errorMsg)
	{
		if (FAILED(hr))
		{
			throw Exception(errorMsg);
		}
	}
}

// DirectX11のラッパー
namespace Wrapper
{
	// 頂点構造体
	struct VERTEX_3D
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		D3DXVECTOR4 Diffuse;
		D3DXVECTOR2 TexCoord;
	};

	// マテリアル構造体
	struct MATERIAL
	{
		D3DXCOLOR	Ambient;
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Specular;
		D3DXCOLOR	Emission;
		float		Shininess;
		float		Dummy[3];//16byte境界用
	};

	// マテリアル構造体
	struct DX11_MODEL_MATERIAL
	{
		MATERIAL		Material;
		class Texture*	Texture;
	};

	// 描画サブセット構造体
	struct DX11_SUBSET
	{
		unsigned int	StartIndex;
		unsigned int	IndexNum;
		DX11_MODEL_MATERIAL	Material;
	};

	// ライト構造体
	struct LIGHT
	{
		BOOL		Enable;
		BOOL		Dummy[3];//16byte境界用
		D3DXVECTOR4	Direction;
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Ambient;
	};

	// DirectX11
	class DirectX11
	{
	private:
		ID3D11Device*				m_Device = NULL;
		ID3D11DeviceContext*		m_ImmediateContext = NULL;
		IDXGISwapChain*				m_SwapChain = NULL;
		ID3D11RenderTargetView*		m_RenderTargetView = NULL;
		ID3D11DepthStencilView*		m_DepthStencilView = NULL;
		ID3D11VertexShader*			m_VertexShader = NULL;
		ID3D11PixelShader*			m_PixelShader = NULL;
		ID3D11InputLayout*			m_VertexLayout = NULL;
		ID3D11Buffer*				m_WorldBuffer = NULL;
		ID3D11Buffer*				m_ViewBuffer = NULL;
		ID3D11Buffer*				m_ProjectionBuffer = NULL;
		ID3D11Buffer*				m_MaterialBuffer = NULL;
		ID3D11Buffer*				m_LightBuffer = NULL;
		ID3D11DepthStencilState*	m_DepthStateEnable = NULL;
		ID3D11DepthStencilState*	m_DepthStateDisable = NULL;

		// シェーダーの生成
		void CompileVertexShader();
		void CompilePixelShader();

		// privateコンストラクタ
		DirectX11() {}
		// コピーと代入を禁止
		DirectX11(const DirectX11&) = delete;
		void operator= (const DirectX11&) = delete;
	public:
		static DirectX11& Instance();
		void Init();
		void Uninit();
		void Begin();
		void End();
		void SetDepthEnable(bool Enable);
		void SetWorldViewProjection2D();
		void SetWorldMatrix(D3DXMATRIX * WorldMatrix);
		void SetViewMatrix(D3DXMATRIX * ViewMatrix);
		void SetProjectionMatrix(D3DXMATRIX * ProjectionMatrix);
		void SetMaterial(MATERIAL Material);
		void SetLight(LIGHT Light);

		ID3D11Device* GetDevice() { return m_Device; }
		ID3D11DeviceContext* GetDeviceContext() { return m_ImmediateContext; }
	};
}