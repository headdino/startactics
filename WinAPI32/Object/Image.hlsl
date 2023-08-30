cbuffer VS_Wvp : register(b0)
{
    matrix View;
    matrix Projection;
}

cbuffer VS_World : register(b1)
{
    matrix World;
}
cbuffer VS_FrameUv : register(b2)
{
    float4 FrameUv;
}

cbuffer PS_Color : register(b0)
{
    float4 Color;
}

struct VertexInput
{
    float4 Position : POSITION0;
    float2 UV : UV0;
};

struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 UV : UV0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.UV = input.UV;

    return output;
}
PixelInput VS2(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.UV = input.UV;

    if (output.UV.x == 0.0f)
    {
        output.UV.x = FrameUv.x;
    }
    if (output.UV.x == 1.0f)
    {
        output.UV.x = FrameUv.z;
    }
    if (output.UV.y == 0.0f)
    {
        output.UV.y = FrameUv.y;
    }
    if (output.UV.y == 1.0f)
    {
        output.UV.y = FrameUv.w;
    }
    
    return output;
}
//전역변수

//샘플러는 픽셀이 어떻게 표현되는지
SamplerState Sampler : register(s0);
//텍스쳐 자원
Texture2D Texture : register(t0);

//기본형
float4 PS(PixelInput input) : SV_TARGET
{
    float4 color = Texture.Sample(Sampler, input.UV);
    if (any(color))
    {
        //실수 연산은 곱하면 곱할수록 어두워 진다
        color *= Color;
        //어두워 지는 연산의 반대값 계산 곱할수록 밝아짐
        //color.r = (1.0f - ((1.0f - color.r) * (1.0f - Color.r)));
        //color.g = (1.0f - ((1.0f - color.g) * (1.0f - Color.g)));
        //color.b = (1.0f - ((1.0f - color.b) * (1.0f - Color.b)));
        //color.a *= Color.a;
    }
    return color;
}
//배경지우기
float4 PS2(PixelInput input) : SV_TARGET
{
    float4 color = Texture.Sample(Sampler, input.UV);
    
    if (color.r >= 0.8f && color.g == 0.0f && color.b >= 0.8f)
    {
        color = 0.0f;
    }
    if (any(color))
    {
        //실수 연산은 곱하면 곱할수록 어두워 진다
        color *= Color;
        //어두워 지는 연산의 반대값 계산 곱할수록 밝아짐
        //color.r = (1.0f - ((1.0f - color.r) * (1.0f - Color.r)));
        //color.g = (1.0f - ((1.0f - color.g) * (1.0f - Color.g)));
        //color.b = (1.0f - ((1.0f - color.b) * (1.0f - Color.b)));
        //color.a *= Color.a;
    }
    return color;

}
//그림자용
float4 PS3(PixelInput input) : SV_TARGET
{
    float4 color = Texture.Sample(Sampler, input.UV);
    
    if (color.r == 1.0f && color.g == 0.0f && color.b == 1.0f)
    {
        color = 0.0f;
    }
    
    if (any(color))
    {
        color.r = 0.0f;
        color.g = 0.0f;
        color.b = 0.0f;
    }

    return color;

}
//검은색 스타배경 지우기용도
float4 PS4(PixelInput input) : SV_TARGET
{
    float4 color = Texture.Sample(Sampler, input.UV);
    
    //if (color.r <= 0.1f && color.g <= 0.1f && color.b <= 0.1f)
    //{
    //    color = 0.0f;
    //    //color.a = 0.0f;
    //}
    if (color.r == 0.0f && color.g == 0.0f && color.b == 0.0f)
    {
        color = 0.0f;
        //color.a = 0.0f;
    }
    if (any(color))
    {
        //실수 연산은 곱하면 곱할수록 어두워 진다
        color *= Color;
        //어두워 지는 연산의 반대값 계산 곱할수록 밝아짐
        //color.r = (1.0f - ((1.0f - color.r) * (1.0f - Color.r)));
        //color.g = (1.0f - ((1.0f - color.g) * (1.0f - Color.g)));
        //color.b = (1.0f - ((1.0f - color.b) * (1.0f - Color.b)));
        //color.a *= Color.a;
    }
    return color;

}