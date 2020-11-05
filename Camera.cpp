/*------------------------------------------------------------

	[Camera.cpp]
	Author : �o���đ�

-------------------------------------------------------------*/
#include "Camera.h"
#include "DirectX11.h"
#include "Application.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 2.0f, -1.0f);
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
	// �r���[�}�g���N�X�ݒ�
	D3DXMatrixLookAtLH(&m_View, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	dx.SetViewMatrix(&m_View);
	// �v���W�F�N�V�����ݒ�
	D3DXMatrixPerspectiveFovLH(&m_Projection, 1.0f, x / y, 1.0f, 1000.0f);
	dx.SetProjectionMatrix(&m_Projection);
}