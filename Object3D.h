/*-----------------------------------------------------------

	[Object3D.h]

	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
//#include "DirectX11.h"

class Object3D
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
public:
	Object3D() = delete; // 空のコンストラクタを呼ばないように
	Object3D(Wrapper::DirectX11& dx, Wrapper::VERTEX_3D Vertex[4]);
	~Object3D();
	void Set(Wrapper::DirectX11& instance, D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale);
	void DrawPolygon(Wrapper::DirectX11 & instance);
};

