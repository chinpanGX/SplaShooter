/*-----------------------------------------------------------

	[Engine.cpp]
	Author : o‡ãÄ‘¾

------------------------------------------------------------*/
#include "Engine.h"

Prefabs::PrefabsTexture* Engine::ObjectPool::m_Texture;

void Engine::ObjectPool::Init()
{
	m_Texture = new Prefabs::PrefabsTexture;
	m_Texture->Load();
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
