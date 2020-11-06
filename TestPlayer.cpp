#include "TestPlayer.h"
#include "Shader.h"

void TestPlayer::Init()
{
	m_Shader = new Shader("vertexShader.cso","pixelShader.cso");
}

void TestPlayer::Uninit()
{
	delete m_Shader;
}

void TestPlayer::Update()
{
}

void TestPlayer::Draw()
{
	m_Shader->Draw();
}
