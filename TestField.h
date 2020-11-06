/*----------------------------------------------------------




----------------------------------------------------------*/
#pragma once
#include "GameObject.h"

class TestField : public GameObject
{
private:
	class Object3D* m_Object;
	class Shader*   m_Shader;
	class Texture*  m_Texture[2];
	unsigned int m_TextureStorge[2];
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

