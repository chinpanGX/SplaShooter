#pragma once
#include "GameObject.h"

class TestPlayer : public GameObject
{
private:
	class Shader* m_Shader;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

