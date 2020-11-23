#pragma once
#include "Actor.h"

class TestPlayer : public Actor
{
private:
	class AnimationModel* m_Model;
public:
	TestPlayer() {}
	~TestPlayer() {}

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

