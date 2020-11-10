/*----------------------------------------------------------

	[]


----------------------------------------------------------*/
#pragma once
#include "GameObject.h"

class TestField : public GameObject
{
private:
	class Object3D* m_Object;
	void CreateVertex(Wrapper::VERTEX_3D Vertex[4]);
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

