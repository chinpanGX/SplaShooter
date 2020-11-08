/*----------------------------------------------------------

	[SettingShader.h]
	Author : 出合翔太

-----------------------------------------------------------*/
#pragma once
#include "GameObject.h"

// ゲームシーン以外でシェーダーをセットするとき
class SettingShader : public GameObject
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
