/*---------------------------------------------------------

	[Effect.h]
	Author : èoçá„ƒëæ

----------------------------------------------------------*/
#pragma once
#include "DirectX11.h"

namespace Effect
{
	struct Float2
	{
		float x;
		float y;
	};
	class Water
	{
	private:
		struct Parameter
		{
			Float2 m_Screen;
			float m_Speed;		// ó¨ÇÍÇÈë¨ìx
			float m_Distortion;	// òcÇ›ÇÃã≠ìx
		};
		Parameter m_Parameter;
		ID3D11VertexShader* m_VertexShader = NULL;
		ID3D11PixelShader* m_PixelShader = NULL;
	public:
		void Init();
		void Uninit();
		void Render();
	};
};

