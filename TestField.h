/*----------------------------------------------------------

	[]


----------------------------------------------------------*/
#pragma once
#include "GameObject.h"

class TestField : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	void CreateVertex(Wrapper::VERTEX_3D Vertex[4]);
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

