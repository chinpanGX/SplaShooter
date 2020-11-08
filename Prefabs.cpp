/*-----------------------------------------------------------

	[Prefabs.h]
	Author : o‡ãÄ‘¾

------------------------------------------------------------*/
#include "Prefabs.h"

#pragma region Prefabs_Texture
void Prefabs::PrefabsTexture::Create(int size)
{
	m_Id = size;
	for (int i = 0; i < size; i++)
	{
		m_Texture = new Texture[size];
	}
}

void Prefabs::PrefabsTexture::Destory()
{

}

void Prefabs::PrefabsTexture::Load()
{
	auto & dx = Wrapper::DirectX11::Instance();
	Create(3);
	m_Id = m_Texture[0].Load(dx, "Asset/Texture/black.png");
	m_Id = m_Texture[1].Load(dx, "Asset/Texture/Title.png");
	m_Id = m_Texture[2].Load(dx, "Asset/Texture/Game.png");
}

void Prefabs::PrefabsTexture::Unload()
{
	for (int i = m_Id -1; i >= 0; i--)
	{
		m_Texture[m_Id].Unload();
	}
	delete[] m_Texture;
}

ID3D11ShaderResourceView * Prefabs::PrefabsTexture::GetTexture(unsigned int Id)
{
	return m_Texture[Id].SetTexture();
}
#pragma endregion PrefabsTexture