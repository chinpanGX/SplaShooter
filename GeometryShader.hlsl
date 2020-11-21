struct GSOutput
{
	float4 pos : SV_POSITION;
    float4 color : COLOR0;
};
static const float4 trianglePos[3] =
{
    float4(0.0f, 0.5f, 0.0f, 0.0f),
    float4(-0.5f, -0.5f, 0.0f, 0.0f),
    float4(-0.5f, -0.5f, 0.0f, 0.0f),
};

[maxvertexcount(3)]
void main(
	triangle float4 input[1] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{
	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
        element.pos = input[0] + trianglePos[i];
        element.color = float4(1.0f, 1.0f, 0.3f, 1.0f);
		output.Append(element);
	}
    output.RestartStrip();
}