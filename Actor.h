/*-----------------------------------------------

	[Actor.h]
	Author : 出合翔太

------------------------------------------------*/
#pragma once
#include "GameObject.h"

class Actor : public GameObject
{
protected:
	// アニメーションに必要な変数
	__int32 m_AnimFrame = 0;
	float m_BlendRate = 0;
public:
	Actor() {}
	virtual ~Actor(){}
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
