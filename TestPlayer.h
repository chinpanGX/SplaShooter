#pragma once
#include "GameObject.h"

class TestPlayer : public GameObject
{
private:
	class AnimationModel* m_Model;

	int m_Frame;
	float m_BlendRate;

public:
	TestPlayer() {}
	~TestPlayer() {}

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

