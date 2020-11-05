/*----------------------------------------------------------

	[SettingShader.h]
	Author : 出合翔太

-----------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include "Shader.h"

// ゲームシーン以外でシェーダーをセットするとき
class SettingShader : public GameObject
{
private:
	Shader* m_Shader = NULL;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
