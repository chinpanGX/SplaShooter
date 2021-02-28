/*--------------------------------------------------------------

	[Scene.h]
	�V�[���֘A�̏������Ǘ�
	Author : �o���đ�

---------------------------------------------------------------*/
#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include <string>
#include "GameObject.h"

// ���C���[�̗񋓁@-> �X�V�A�`��̏��Ԃɐ錾
enum layer : int
{
	LAYER_CAMERA,
	LAYER_3D,
	LAYER_2D_BG,		// �w�i
	LAYER_2D_EFFECT,	// �G�t�F�N�g�i�r���{�[�h�Ȃǁj
	LAYER_2D_UI,		// UI
	LAYER_MAX
};

// ���N���XScene�N���X
#pragma region Class_Scene
class Scene
{
protected:
	std::list<GameObject*> m_GameObject[LAYER_MAX];
public:
	Scene() {}
	virtual ~Scene() {}
	virtual void Init() = 0; // ������
	// �I������
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
	// �X�V����
	virtual void Update()
	{
		for (int i = 0; i < 5; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();
			}
		}
		for (int i = 0; i < LAYER_MAX; i++)
		{
			// �����_���i�����֐��j
			m_GameObject[i].remove_if([](GameObject* object)
				{
					return object->Destroy();
				}
			);
		}
	}
	// �`�揈��
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

	// �ǉ�
	template <typename T>
	T* AddGameObject(int layer)
	{
		T* gameObject = new T();
		m_GameObject[layer].push_back(gameObject);
		gameObject->Init();
		return gameObject;
	}

	// �Q�b�^�[
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
#pragma endregion Scene�N���X�̐錾

// namespace��GameScene
namespace GameScene
{
	// Title�N���X
#pragma region class_Title-public_Scene
	class Title : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
#pragma endregion Title�N���X�̐錾

	// Game�N���X
#pragma region class_Game-public_Scene
	class Game : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
#pragma endregion Game�N���X�̐錾
};

