/*-----------------------------------------------------------

	[Engine.cpp]
	Author : o‡ãÄ‘¾

------------------------------------------------------------*/

#include "Engine.h"

Prefabs::Texture* Engine::ObjectPool::m_Texture;
Prefabs::VertexShader* Engine::ObjectPool::m_VertexShader;
Prefabs::PixelShader* Engine::ObjectPool::m_PixelShader;
Prefabs::StaticMesh* Engine::ObjectPool::m_StaticMesh;
Prefabs::SkeletalMesh* Engine::ObjectPool::m_SkeletalMesh;

void Engine::ObjectPool::Init()
{
	auto & dx = Wrapper::DirectX11::Instance();
	m_Texture = new Prefabs::Texture;
	m_Texture->Load(dx);
	m_VertexShader = new Prefabs::VertexShader();
	m_VertexShader->Load(dx);
	m_PixelShader = new Prefabs::PixelShader();
	m_PixelShader->Load(dx);
	m_StaticMesh = new Prefabs::StaticMesh();
	m_StaticMesh->Load(dx);
	m_SkeletalMesh = new Prefabs::SkeletalMesh();
	m_SkeletalMesh->Load(dx);
}

void Engine::ObjectPool::Uninit()
{
	m_SkeletalMesh->Unload();
	delete m_SkeletalMesh;
	m_StaticMesh->Unload();
	delete m_StaticMesh;
	m_PixelShader->Unload();
	delete m_PixelShader;
	m_VertexShader->Unload();
	delete m_VertexShader;
	m_Texture->Unload();
	delete m_Texture;
}

void Engine::ObjectPool::SkeletalMeshUpdate(Wrapper::DirectX11 & dx, unsigned __int32 Id, const char * AnimationName1, const char * AnimationName2, float BlendRate, int Frame)
{
	m_SkeletalMesh->GetModel(Id)->Update(dx, AnimationName1, AnimationName2, BlendRate, Frame);
}

void Engine::ObjectPool::SkeletalMeshDraw(Wrapper::DirectX11 & dx, unsigned __int32 Id)
{
	m_SkeletalMesh ->GetModel(Id)->Draw(dx);
}

ID3D11ShaderResourceView * Engine::ObjectPool::GetTexture(unsigned int Id)
{
	return m_Texture->GetTexture(Id);
}

void Engine::ObjectPool::SetTexture(Wrapper::DirectX11 & dx, int slot, unsigned int Id)
{
	ID3D11ShaderResourceView* t = m_Texture->GetTexture(Id);
	dx.GetDeviceContext()->PSSetShaderResources(slot, 1, &t);
}

void Engine::ObjectPool::SetVertexShader(Wrapper::DirectX11 & dx, unsigned int Id)
{
	dx.GetDeviceContext()->VSSetShader(m_VertexShader->GetVertexShader(Id), NULL, 0);
}

void Engine::ObjectPool::SetInputLayout(Wrapper::DirectX11 & dx, unsigned int Id)
{
	dx.GetDeviceContext()->IASetInputLayout(m_VertexShader->GetInputLayout(Id));
}

void Engine::ObjectPool::SetPixelShader(Wrapper::DirectX11 & dx, unsigned int Id)
{
	dx.GetDeviceContext()->PSSetShader(m_PixelShader->GetPixelShader(Id), NULL, 0);
}
