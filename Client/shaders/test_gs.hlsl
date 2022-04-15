
struct VertexOutputType
{
    float4 position		: SV_POSITION;
    float4 color		: COLOR;
};

struct g2f
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

float2 FromClipSpace(float4 clipPos)
{
    return clipPos.xy / clipPos.w;
}

float4 ToClipSpace(float2 screenPos, float originalClipPosW)
{
    return float4(screenPos.xy * originalClipPosW, 0, originalClipPosW);
}

[maxvertexcount(1)]
void main(point VertexOutputType input[1], inout PointStream<VertexOutputType> OutputStream)
{
    OutputStream.Append(input[0]);
    //g2f gsout;
    //gsout.color = float4(1.f, 1.f, 1.f, 1.f);
    //gsout.pos = input[0].position;
    //OutputStream.Append(gsout);
    //gsout.pos = input[0].position;
    //OutputStream.Append(gsout);
    //gsout.pos = input[0].position;
    //OutputStream.Append(gsout);
    //v.position = ToClipSpace(screenPos + float2(s, -s), clipPosW);
    //v.color = float4(0, 1, 0, 1);
    //triStream.Append(v);

    //v.position = ToClipSpace(screenPos + float2(-s, -s), clipPosW);
    //v.color = float4(1, 0, 0, 1);
    //triStream.Append(v);

    //v.position = ToClipSpace(screenPos + float2(s, s), clipPosW);
    //v.color = float4(0, 0, 1, 1);
    //triStream.Append(v);
}