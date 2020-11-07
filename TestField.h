/*----------------------------------------------------------




----------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include "Texture.h"

class TestField : public GameObject
{
private:
	class Object3D* m_Object = NULL;
	class Shader*   m_Shader = NULL;
	Texture  m_Texture[2];
	unsigned int m_TextureStorge[2];

	void CreateVertex(Wrapper::VERTEX_3D Vertex[4]);
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

