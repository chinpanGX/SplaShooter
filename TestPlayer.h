#pragma once
#include "GameObject.h"

class TestPlayer : public GameObject
{
private:
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

