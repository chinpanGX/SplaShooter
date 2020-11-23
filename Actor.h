/*-----------------------------------------------

	[Actor.h]
	Author : �o���đ�

------------------------------------------------*/
#pragma once
#include "GameObject.h"

class Actor : public GameObject
{
protected:
	// �A�j���[�V�����ɕK�v�ȕϐ�
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
