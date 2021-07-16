// External texture-related data
SamplerState Sampler	: register(s0);
Texture2D Texture		: register(t0);

struct VertexOutputType
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMALWS;
	float3 tangent		: TANGENTWS;
	float3 worldPos		: POSITIONWS;
	float2 coord		: TEXCOORD;
};

struct PixelOutputType
{
	float4 Normal				: SV_Target0;			//Normal map
	float4 Diffuse				: SV_Target1;			//Color
	float4 Position				: SV_Target2;
};

PixelOutputType main(VertexOutputType input)
{
	PixelOutputType output;

	input.normal = normalize(input.normal);
	input.tangent = normalize(input.tangent);

	// Read and unpack normal from map
	float3 normalFromMap = float3(1.0f, 1.0f, 1.0f);//NormalMap.Sample(Sampler, input.uv).xyz * 2 - 1;

	// Transform from tangent to world space
	float3 N = input.normal;
	float3 T = normalize(input.tangent - N * dot(input.tangent, N));
	float3 B = cross(T, N);

	float3x3 TBN = float3x3(T, B, N);
	input.normal = normalize(mul(normalFromMap, TBN));

	// Sample the texture
	float4 textureColor = Texture.Sample(Sampler, input.coord);

	output.Normal = float4(input.normal, 1.0f);
	output.Diffuse = textureColor;
	output.Position = float4( input.worldPos, 1.0f);


	return output;
}