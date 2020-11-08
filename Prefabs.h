/*-----------------------------------------------------------

	[Prefabs.h]
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include <vector>
#include <string>
#include "Texture.h"
#include "GameObject.h"
#include <memory>

#pragma region Prefabs_Wrapper
namespace Prefabs
{
#pragma region BaseClass_PrefabsBase
	class PrefabsBase
	{
	protected:
		unsigned int m_Id;
		virtual void Create(int size) {};
		virtual void Destory() {};
	public:
		virtual void Load() = 0;
		virtual void Unload() = 0;
	};
#pragma endregion Prefabsの基底クラス

	// Textureのプレハブ
	class PrefabsTexture : public PrefabsBase
	{
	private:
		Texture* m_Texture;
		void Create(int size)override;
		virtual void Destory();
	public:
		void Load()override;
		void Unload()override;
		ID3D11ShaderResourceView* GetTexture(unsigned int Id);
	};
}
#pragma endregion Prefabsをまとめたもの
