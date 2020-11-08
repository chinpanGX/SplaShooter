/*----------------------------------------------------------




----------------------------------------------------------*/
#pragma once
#include "GameObject.h"


class TestField : public GameObject
{
private:
	// シェーダー
	//ID3D11VertexShader* m_VertexShader = NULL;
	//ID3D11InputLayout*	m_InputLayout = NULL;
	//ID3D11PixelShader*	m_PixelShader = NULL;

	class Object3D* m_Object = NULL;
	unsigned int m_TextureStorge[2];

	void CreateVertex(Wrapper::VERTEX_3D Vertex[4]);
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

