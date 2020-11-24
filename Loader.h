/*----------------------------------------------------------

	[Loader.h]
	�ǂݍ��݂Ɋւ��郉�b�p�[
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once
#include "DirectX11.h"

namespace Loader
{
	// �e�N�X�`�����Ǘ�
	class Texture
	{
	private:
		ID3D11ShaderResourceView* m_Texture = NULL;
	public:
		void Load(Wrapper::DirectX11& dx, std::string FileName); // ���[�h
		void Unload();
		ID3D11ShaderResourceView* GetTexture()const; // �Z�b�g
	};

	// ���_�V�F�[�_�[
	class VertexShader
	{
	private:
		ID3D11VertexShader* m_VertexShader = nullptr;
		ID3D11InputLayout*	m_InputLayout = nullptr;
		// ����
		void CreateVertexShader(Wrapper::DirectX11 & dx, ID3D11VertexShader ** VertexShader, ID3D11InputLayout ** InputLayout, std::string FileName);
	public:
		void Load(Wrapper::DirectX11 & dx, std::string VertexShader_FileName);
		void Unload();
		ID3D11VertexShader* GetVertexShader()const;
		ID3D11InputLayout* GetInputLayout()const;
	};

	// �s�N�Z���V�F�[�_�[
	class PixelShader
	{
	private:
		ID3D11PixelShader*	m_PixelShader = NULL;
		// ����
		void CreatePixelShader(Wrapper::DirectX11& dx, ID3D11PixelShader** PixelShader, std::string FileName);
	public:
		void Load(Wrapper::DirectX11 & dx, std::string PixelShader_FileName);
		void Unload();
		ID3D11PixelShader* GetPixelShader()const;
	};
}
