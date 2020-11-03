/*----------------------------------------------------------

	[Manager.h]
	ゲームの管理
	Author : 出合翔太

-----------------------------------------------------------*/
#pragma once
#include<memory>
#include<vector>
#include<map>
#include "DirectX11.h"
#include "Bg.h"

class Manager
{
private:
	static class Scene* m_Scene;
	static class Fade m_Fade;
	static class Wrapper::DirectX11& m_dx;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static class Scene* GetScene() { return m_Scene; }
	static void ChangeScene(Scene* scene);	// 画面遷移
	// シーンのセット
	template <typename T>
	static void SetScene()
	{
		if (m_Fade.m_FadeState != Fade::FADE_NONE)
		{
			return;
		}
		m_Fade.m_FadeState = Fade::FADE_OUT;
		T* scene = new T;
		m_Fade.m_NextScene = scene;
	}
};

