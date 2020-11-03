/*----------------------------------------------------------

	[Bg.h]
	背景に関するクラスをまとめる
	Author : 出合翔太

-----------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "DirectX11.h"
#include "Fps.h"

// 背景描画用に基底クラス
class Bg : public GameObject
{
protected:
	D3DXVECTOR2 m_Scrren;
	SpriteRenderer m_Sprite;
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	D3DXVECTOR2 GetScrren(); // スクリーンサイズのゲッター
};

// フェード
class Fade : public Bg
{
private:
	float m_Alpha = 1.0f;	// a値
	float m_FadeTime;
	Fps& m_Fps;
public:
	enum FadeState : int
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT
	};
	FadeState m_FadeState = FADE_NONE;
	static class Scene* m_NextScene;
	
	Fade() : m_Fps(Fps::Instance()) {};
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

// 背景の描画
namespace DrawBg
{
	// タイトル背景
	class Title : public Bg
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
	// ゲーム背景
	class Game : public Bg
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
}