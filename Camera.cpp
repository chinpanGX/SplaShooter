/*------------------------------------------------------------

	[Camera.cpp]
	Author : 出合翔太

-------------------------------------------------------------*/
#include "Camera.h"
#include "DirectX11.h"
#include "Application.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 3.0f, -5.0f);
	m_Target = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

void Camera::Update()
{
}

void Camera::Draw()
{
	auto& dx = Wrapper::DirectX11::Instance();
	auto& app = Application::Instance();
	float x = (float)app.GetWindowSize().cx;
	float y = (float)app.GetWindowSize().cy;
	D3DXMATRIX view, projection;
	
	// ビューマトリクス設定
	D3DXMatrixLookAtLH(&view, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	dx.SetViewMatrix(&view);
	
	// プロジェクション設定
	D3DXMatrixPerspectiveFovLH(&projection, 1.0f, x / y, 1.0f, 1000.0f);
	dx.SetProjectionMatrix(&projection);
	dx.SetCameraPosition(m_Position);
}
