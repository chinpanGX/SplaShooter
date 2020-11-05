/*----------------------------------------------------------
	
	[SettingShader.cpp]
	Author : o‡ãÄ‘¾

-----------------------------------------------------------*/
#include "SettingShader.h"

void SettingShader::Init()
{
	m_Shader = new Shader("vertexShader.cso", "pixelShader.cso");
}

void SettingShader::Uninit()
{
	delete m_Shader;
}

void SettingShader::Update()
{
}

void SettingShader::Draw()
{
	m_Shader->Render();
}
