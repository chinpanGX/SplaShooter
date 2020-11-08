/*----------------------------------------------------------
	
	[SettingShader.cpp]
	Author : èoçá„ƒëæ

-----------------------------------------------------------*/
#include "SettingShader.h"
#include "Engine.h"

void SettingShader::Init()
{
	
}

void SettingShader::Uninit()
{

}

void SettingShader::Update()
{
}

void SettingShader::Draw()
{
	auto &dx = Wrapper::DirectX11::Instance();
	Engine::ObjectPool::SetInputLayout(dx, 0);
	Engine::ObjectPool::SetVertexShader(dx, 0);
	Engine::ObjectPool::SetPixelShader(dx, 0);
}
