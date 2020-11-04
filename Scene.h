/*--------------------------------------------------------------

	[Scene.h]
	シーン関連の処理を管理
	Author : 出合翔太

---------------------------------------------------------------*/
#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include <string>
#include "GameObject.h"

// レイヤーの列挙　-> 更新、描画の順番に宣言
enum layer : int
{
	LAYER_CAMERA,
	LAYER_3D,
	LAYER_2D_BG,		// 背景
	LAYER_2D_EFFECT,	// エフェクト（ビルボードなど）
	LAYER_2D_UI,		// UI
	LAYER_MAX
};

// 基底クラスSceneクラス
#pragma region Class_Scene
class Scene
{
protected:
	std::list<GameObject*> m_GameObject[LAYER_MAX];
public:
	Scene() {}
	virtual ~Scene() {}
	virtual void Init() = 0; // 初期化
	// 終了処理
	virtual void Uninit()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}
	// 更新処理
	virtual void Update()
	{
		for (GameObject* object : m_GameObject[LAYER_CAMERA])
		{
			object->Update();
		}
		for (GameObject* object : m_GameObject[LAYER_3D])
		{
			object->Update();
		}
		for (GameObject* object : m_GameObject[LAYER_2D_BG])
		{
			object->Update();
		}
		for (GameObject* object : m_GameObject[LAYER_2D_EFFECT])
		{
			object->Update();
		}
		for (GameObject* object : m_GameObject[LAYER_2D_UI])
		{
			object->Update();
		}
		for (int i = 0; i < LAYER_MAX; i++)
		{
			// ラムダ式（無名関数）
			m_GameObject[i].remove_if([](GameObject* object)
				{
					return object->Destroy();
				}
			);
		}
	}
	// 描画処理
	virtual void Draw()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	// 追加
	template <typename T>
	T* AddGameObject(int layer)
	{
		T* gameObject = new T();
		m_GameObject[layer].push_back(gameObject);
		gameObject->Init();
		return gameObject;
	}

	// ゲッター
	template<typename T>
	T* GetGameObject(int layer)
	{
		for (GameObject* object : m_GameObject[layer])
		{
			if (typeid(*object) == typeid(T))
				return (T*)object;
		}
		return NULL;
	}
	template<typename T>
	std::vector<T*>GetGameObjects(int layer)
	{
		std::vector<T*>objects;
		for (GameObject* object : m_GameObject[layer])
		{
			if (typeid(*object) == typeid(T))
				objects.push_back((T*)object);
		}
		return objects;
	}
};
#pragma endregion Sceneクラスの宣言

// namespace→GameScene
namespace GameScene
{
	// Titleクラス
#pragma region class_Title-public_Scene
	class Title : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
#pragma endregion Titleクラスの宣言

	// Gameクラス
#pragma region class_Game-public_Scene
	class Game : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
#pragma endregion Gameクラスの宣言
};

