/*-----------------------------------------------------------

	[Engine.cpp]
	Author : o‡ãÄ‘¾

------------------------------------------------------------*/
#include "Engine.h"

Prefabs::Texture* Engine::ObjectPool::m_Texture;

void Engine::ObjectPool::Init()
{
	auto & dx = Wrapper::DirectX11::Instance();
	m_Texture = new Prefabs::Texture;
	m_Texture->Load(dx);
}

void Engine::ObjectPool::Uninit()
{
	m_Texture->Unload();
	delete m_Texture;
}

void Engine::ObjectPool::Update()
{
}

void Engine::ObjectPool::Draw()
{
}

ID3D11ShaderResourceView * Engine::ObjectPool::GetTexture(unsigned int Id)
{
	return m_Texture->GetTexture(Id);
}
