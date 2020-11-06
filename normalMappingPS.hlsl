
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormal : register(t1);
SamplerState g_SampleState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse = g_Texture.Sample(g_SampleState, In.TexCoord);

    //法線マッピング
    float4 normalMap = g_TextureNormal.Sample(g_SampleState,In.TexCoord);
    normalMap = (normalMap * 2.0) - 1.0;
    //normalMap = (-normalMap * inTangent) + (-normalMap.y * inBinormal) + (no)
    
    
    //床に貼るための措置
    float4 normal;
    normal.x = -normalMap.x;
    normal.y =  normalMap.z;
    normal.z =  normalMap.y;
    normal.w =  0.0;
    
    normal = normalize(normal);

    //以下ランバートの式など
    
    //ランバート拡散照明
    float light = -dot(normal.xyz, Light.Direction.xyz);
    light = saturate(light);

    outDiffuse = g_Texture.Sample(g_SampleState, In.TexCoord);
    outDiffuse.rgb *= In.Diffuse.rgb * light;
    outDiffuse.a *= In.Diffuse.a;
    
    //スペキュラ(フォン)
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    refv = normalize(refv);
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 30);

    outDiffuse.rgb += specular;
}
