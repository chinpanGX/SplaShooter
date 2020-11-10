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
	Engine::ObjectPool::SetInputLayout(dx, Prefabs::VertexShader::ID::DEFAULT);
	Engine::ObjectPool::SetVertexShader(dx, Prefabs::VertexShader::ID::DEFAULT);
	Engine::ObjectPool::SetPixelShader(dx, Prefabs::PixelShader::ID::DEFAULT);
}
