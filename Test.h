/*-------------------------------------------------------------

	[Test.h]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#pragma once
#include "GameObject.h"

namespace Test_Chinapan
{
	class Field : public GameObject
	{
	private:
		//ID3D11Buffer* m_VertexBuffer = NULL;
		class Polygon3D* m_Polygon;
		void CreateVertex(Wrapper::VERTEX_3D Vertex[4]);
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
}