/*-----------------------------------------------------------

	[Camera.h]
	Author : èoçá„ƒëæ

-------------------------------------------------------------*/
#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
private:
	D3DXVECTOR3 m_Target;
	D3DXMATRIX  m_View;
	D3DXMATRIX  m_Projection;
public:
	void Init()override;
	void Uninit()override {};
	void Update()override;
	void Draw()override;
	D3DXMATRIX GetView() { return m_View; }
};

