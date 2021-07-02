cbuffer MatrixBuffer : register(b0)
{
	matrix wvp;
};

struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PixelInputType vs_main(VertexInputType input)
{
    PixelInputType output;
    input.position.w = 1.0f;
    output.position = mul(input.position, wvp);
    output.color = input.color;
    return output;
}

float4 ps_main(PixelInputType input) : SV_Target
{
    return input.color;
}